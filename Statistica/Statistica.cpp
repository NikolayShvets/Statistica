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
Tvector getYstar(std::vector<Tvector> vec) {
	Tvector yStar(vec.size());
	int counter{0};
	int i{0};
	for (auto v : vec) {
		double yIAverage{0.0};
		for (i = 0; i < v.size(); ++i) {
			yIAverage += v[i];
		}
		yStar[counter] = yIAverage/i;
		i = 0;
		++counter;
	}
	return yStar;
}
int main()
{
	std::cout << "\tGIVEN\n\n";
	//векторы входных переменных
	Tvector x1(6), x2(6), x3(6);
	x1[0] = 2.0; x1[1] = 2.0; x1[2] = 2.0; x1[3] = 2.0; x1[4] = 4.0; x1[5] = 2.0;
	x2[0] = 1.2; x2[1] = 1.2; x2[2] = 1.5; x2[3] = 1.0; x2[4] = 1.6; x2[5] = 1.6;
	x3[0] = 1.6; x3[1] = 2.0; x3[2] = 2.4; x3[3] = 1.6; x3[4] = 1.0; x3[5] = 2.4;
	std::vector<Tvector> variables;
	variables.push_back(x1); variables.push_back(x2); variables.push_back(x3);
	//вектора измерений
	Tvector y1(6), y2(6), y3(6), y4(6), y5(6);
	y1[0] = 27.52; y1[1] = 29.74; y1[2] = 37.26; y1[3] = 24.84; y1[4] = 42.69; y1[5] = 37.92;
	y2[0] = 26.09; y2[1] = 30.33; y2[2] = 37.30; y2[3] = 24.79; y2[4] = 44.09; y2[5] = 40.47;
	y3[0] = 26.28; y3[1] = 30.23; y3[2] = 37.31; y3[3] = 24.50; y3[4] = 44.44; y3[5] = 39.65;
	y4[0] = 27.26; y4[1] = 30.23; y4[2] = 38.18; y4[3] = 25.32; y4[4] = 43.60; y4[5] = 38.06;
	y5[0] = 25.60; y5[1] = 30.64; y5[2] = 37.32; y5[3] = 23.97; y5[4] = 44.61; y5[5] = 38.11;
	std::vector<Tvector> measures;
	measures.push_back(y1); measures.push_back(y2); measures.push_back(y3); measures.push_back(y4); measures.push_back(y5);
	std::cout << "****averages Yi****\n";
	Tvector yStar(getYstar(measures));
	print(yStar);
	//вектор оцениваемых параметров, кол-во элементов не меньше чем кол-во измерений y
	//требуется оценить
	Tvector a(4), aStar(4);
	for (int i = 0; i < a.size(); ++i) {
		a[i] = 1.0;
		aStar[i] = 0.0;
	}

	Tmatrix F(5, 4);
	Tvector points(variables.size());
	for (int i = 0; i < measures.size(); ++i) {
		for (int j = 0; j < variables.size(); ++j) {
			points[j] = variables[j][i];
		}
		F(i, 0) = X1(points);
		F(i, 1) = X1X2(points);
		F(i, 2) = X1X3(points);
		F(i, 3) = X22(points);
	}
	std::cout << "F: " << std::endl;
	print(F);
	std::cout << "Ft: " << std::endl;
	print(F.T());
	std::cout << "Ft*F: " << std::endl;
	print(F.T()*F);
	std::cout << "(Ft*F)^-1: " << std::endl;
	print(!(F.T()*F));
	std::cout << "C: " << std::endl;
	Tmatrix C(!(F.T()*F));
	print(C);
	std::cout << "a*: " << aStar.size() << " x 1" << " Ft: " << F.T().rowsCount() << " x " << F.T().colsCount() << " C: " << C.rowsCount() << " x " << C.colsCount() << " y*: " << yStar.size() << " x 1" << std::endl;
	aStar =  C * F.T() * yStar;
	print(aStar);
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
