#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <iostream>
#include "vector.h"

class Tmatrix
{
private:
	std::vector<std::vector<double>> data;
	int rows, cols;
public:
	Tmatrix();//конструктор по умолчанию
	Tmatrix(int rows, int columns);//конструктор по размеру
	Tmatrix(const Tmatrix & rMatrix);//коснтруктор копирования
	void resize(int rows, int columns);
	int rowsCount() const;
	int colsCount() const;
	double det(); //определитель матрицы
	double operator () (int row, int col) const { return this->data.at(row).at(col); }//чтение элемента
	double & operator () (int row, int col) { return this->data.at(row).at(col); }
	int getHighRow() { return this->rowsCount() - 1; }
	int getHighCol() { return this->colsCount() - 1; }
	Tmatrix & operator = (const Tmatrix & rMatrix);//копирование матрциы
	Tmatrix operator + (const Tmatrix & rMatrix) const;
	Tmatrix operator - (const Tmatrix & rMatrix) const;
	Tmatrix operator * (const Tmatrix & rMatrix) const;
	Tmatrix operator * (double rValue) const;
	Tmatrix operator ! ();//инвертирование матрицы
	Tmatrix & T();//транспонирование матрицы
	Tmatrix& swapRows(int pos, int newPos);
	Tmatrix I(int rows);//получение единичной матрицы
	Tvector operator * (const Tvector& rVector) const; //умножение матрицы на вектор
	friend void print(const Tmatrix & printMatrix)
	{
		std::cout << "[ "; 
		for (int i = 0; i < printMatrix.rowsCount(); ++i) {
			if (i != 0) std::cout << "  ";
			std::copy(printMatrix.data.at(i).begin(), printMatrix.data.at(i).end(), std::ostream_iterator<double>(std::cout, " "));
			if(i != printMatrix.rowsCount() - 1) std::cout << std::endl;
		} 
		std::cout << "]" << std::endl;
	}
	~Tmatrix();
};

