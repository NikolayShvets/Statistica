// Statistica.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "vector.h"
#include "matrix.h"

//функции полинома модели y = a0*X1+a1*X2X2+a2*X1X3+a3*X2^2
double X1(Tvector x) {
	return x[0];
}
double X1X2(Tvector x){
	return x[0] * x[1];
}
double X1X3(Tvector x) {
	return x[0] * x[2];
}
double X22(Tvector x) {
	return x[1] * x[1];
}
//вычисление средних значений выхода
Tvector getYstar(std::vector<Tvector> vec) {
	Tvector yStar(vec.front().size());
	double sum{0.0};
	for (int i = 0; i < vec.front().size(); ++i) {
		for (int j = 0; j < vec.size(); ++j) {
			sum += vec[j][i];
		}
		yStar[i] = sum / vec.size();
		sum = 0;
	}
	return yStar;
}
int main()
{
	int pCount = 4; //количество оцениваемых параметров
	std::cout << "\n\tGIVEN\n\n";
	std::cout << "\n****input variables vectors****\n";
	Tvector x1(6), x2(6), x3(6);
	x1[0] = 2.0; x1[1] = 2.0; x1[2] = 2.0; x1[3] = 2.0; x1[4] = 4.0; x1[5] = 2.0;
	x2[0] = 1.2; x2[1] = 1.2; x2[2] = 1.5; x2[3] = 1.0; x2[4] = 1.6; x2[5] = 1.6;
	x3[0] = 1.6; x3[1] = 2.0; x3[2] = 2.4; x3[3] = 1.6; x3[4] = 1.0; x3[5] = 2.4;
	std::vector<Tvector> variables;
	variables.push_back(x1); variables.push_back(x2); variables.push_back(x3);
	for (auto v : variables) {
		print(v);
	}
	std::cout << std::endl;

	std::cout << "\n****outputs vectors****\n";
	Tvector y1(6), y2(6), y3(6), y4(6), y5(6);
	y1[0] = 27.52; y1[1] = 29.74; y1[2] = 37.26; y1[3] = 24.84; y1[4] = 42.69; y1[5] = 37.92;
	y2[0] = 26.09; y2[1] = 30.33; y2[2] = 37.30; y2[3] = 24.79; y2[4] = 44.09; y2[5] = 40.47;
	y3[0] = 26.28; y3[1] = 30.23; y3[2] = 37.31; y3[3] = 24.50; y3[4] = 44.44; y3[5] = 39.65;
	y4[0] = 27.26; y4[1] = 30.23; y4[2] = 38.18; y4[3] = 25.32; y4[4] = 43.60; y4[5] = 38.06;
	y5[0] = 25.60; y5[1] = 30.64; y5[2] = 37.32; y5[3] = 23.97; y5[4] = 44.61; y5[5] = 38.11;
	std::vector<Tvector> measures; //контейнер векторов выхода
	measures.push_back(y1); measures.push_back(y2); measures.push_back(y3); measures.push_back(y4); measures.push_back(y5);
	for (auto m : measures) {
		print(m);
	}
	std::cout << std::endl;

	std::cout << "\n****averages Yi****\n";
	Tvector yStar(getYstar(measures));
	print(yStar);
	std::cout << std::endl;

	//вектор оцениваемых параметров, кол-во элементов не меньше чем кол-во измерений y
	Tvector a(pCount), aStar(pCount);
	for (int i = 0; i < a.size(); ++i) {
		a[i] = 1.0;
		aStar[i] = 0.0;
	}

	Tmatrix F(measures.front().size(), pCount);
	Tvector point(variables.size()); //вектор точек, подаваемых на вход (x1i, x2i, x3i)
	std::vector<Tvector> f_x; //вектор базисных функций
	for (int i = 0; i < variables.front().size(); ++i) {
		for (int j = 0; j < variables.size(); ++j) {
			point[j] = variables[j][i];
		}
		//собираем матрицу F
		Tvector temp(pCount);
		F(i, 0) = temp[0] = X1(point);
		F(i, 1) = temp[1] = X1X2(point);
		F(i, 2) = temp[2] = X1X3(point);
		F(i, 3) = temp[3] = X22(point);
		f_x.push_back(temp);
	}
	//выисление матрицы С
	std::cout << "\n****matrix F****" << std::endl;
	print(F);
	std::cout << "\n****matrix F.T****" << std::endl;
	print(F.T());
	std::cout << "\n****matrix C'****" << std::endl;
	print(F.T()*F);
	std::cout << "\n****det(C')****" << std::endl;
	std::cout << (F.T()*F).det() << std::endl;
	std::cout << "\n****matrix C****\n" << std::endl;
	Tmatrix C(!(F.T()*F));
	print(C);
	std::cout << "\n**** C * F.T ****\n" << std::endl;
	print(C*F.T());
	/*std::cout << "a*: " << aStar.size() << " x 1" << " C: " << C.rowsCount() << " x " << C.colsCount()<<
		" Ft: " << F.T().rowsCount() << " x " << F.T().colsCount()
		 << " y*: " << yStar.size() << " x 1" << std::endl;*/

	//Вычисление оценок компонент вектора параметров а
	aStar = ( C * F.T() )* yStar;
	std::cout << "\n****vector a* ****\n";
	print(aStar);

	//немного магии (костылей)
	Tmatrix aStarT(1, aStar.size());
	for (int i = 0; i < aStar.size(); ++i) {
		aStarT(0, i) = aStar[i];
	}

	std::vector<Tvector> y_(measures.front().size()); //оценки измерений
	for (int i = 0; i < y_.size(); ++i) {
		std::cout << "\n****vector f"<<i<<"(x)****\n";
		print(f_x[i]);
		y_[i] = aStarT * f_x[i];
		std::cout << "\n****evaluation y"<<i<<"****\n";
		print(y_[i]);
	}
	double sigma2{0.0};//оценка дисперсрсий ошибок измерений (в каждой точке одно измерение)
	double sumN{0.0};
	//вычисление этой дисперсии
	for (int i = 0; i < measures.front().size(); ++i) {
		sumN += pow(yStar[i] - y_[i][0] , 2.);
	}
	sigma2 = sumN / (measures.front().size() - pCount);

	sumN = 0.0;
	std::cout << "\n****sigma_1^2****\n";
	std::cout << sigma2 << std::endl;

	Tvector sigma2_i(pCount); //дисперсия оценок коэффициентов (параметров)
	for (int i = 0; i < pCount; ++i) {
		sigma2_i[i] = C(i, i)*sigma2;
	}
	std::cout << "\n****sigma_i^2****\n";
	print(sigma2_i);

	double sigma2_{0.0};//оценка дисперсрсий ошибок измерений (по всей совокупности измерений)
	double sumM{0.0};
	for (int i = 0; i < measures.front().size(); ++i) {
		sumN += sumM;
		for (int j = 0; j < measures.size(); ++j) {
			sumM += pow(measures[j][i] - yStar[i], 2.);
		}
	}
	sigma2_ = sumN / (measures.front().size()*(measures.size() - 1));

	std::cout << "\n****sigma_2^2****\n";
	std::cout << sigma2_ << std::endl;
	//проверка адеватности модели тестом Фишера
	double Fisher = sigma2*measures.size() / sigma2_;
	std::cout << "\n****F - test****\n";
	std::cout << Fisher << std::endl;

	double left, right; //левая, правая границы доверительных интервалов
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < aStar.size(); ++j) {
			if (i == 0) {
				if(j == 0)
					std::cout << "\n****Confidence interval for Z distribution****\n";
				left = -0.3289*pow(C(j, j), 0.5)*sigma2 + aStar[j];
				right = +0.3289*pow(C(j, j), 0.5)*sigma2 + aStar[j];
				std::cout << left << " <= a[" << j << "] <= " << right << " | a*[" << j << "] = " << aStar[j];
				if ( (aStar[j] <= right) && (aStar[j] >= left) ) std::cout << " TRUE\n"; else std::cout << " FALSE\n";
			}
			if (i == 1) {
				if(j == 0)
					std::cout << "\n****Confidence interval for Chi^2 distribution****\n";
				left = -0.10259*pow(C(j, j), 0.5)*sigma2 + aStar[j];
				right = +0.10259*pow(C(j, j), 0.5)*sigma2 + aStar[j];
				std::cout << left << " <= a[" << j << "] <= " << right << " | a*[" << j << "] = " << aStar[j];
				if ( (aStar[j] <= right) && (aStar[j] >= left) ) std::cout << " TRUE\n"; else std::cout << " FALSE\n";
			}
			if (i == 2) {
				if(j == 0)
					std::cout << "\n****Confidence interval for t distribution****\n";
				left = -1.710882*pow(C(j, j), 0.5)*sigma2_ + aStar[j];
				right = +1.710882*pow(C(j, j), 0.5)*sigma2_ + aStar[j];
				std::cout << left << " <= a[" << j << "] <= " << right << " | a*[" << j << "] = " << aStar[j];
				if ((aStar[j] <= right) && (aStar[j] >= left)) std::cout << " TRUE\n"; else std::cout << " FALSE\n";
			}
		}
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
