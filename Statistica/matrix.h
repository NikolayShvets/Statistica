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
	Tmatrix();//����������� �� ���������
	Tmatrix(int rows, int columns);//����������� �� �������
	Tmatrix(const Tmatrix & rMatrix);//����������� �����������
	void resize(int rows, int columns);
	int rowsCount() const;
	int colsCount() const;
	double det(); //������������ �������
	double operator () (int row, int col) const { return this->data.at(row).at(col); }//������ ��������
	double & operator () (int row, int col) { return this->data.at(row).at(col); }
	int getHighRow() { return this->rowsCount() - 1; }
	int getHighCol() { return this->colsCount() - 1; }
	Tmatrix & operator = (const Tmatrix & rMatrix);//����������� �������
	Tmatrix operator + (const Tmatrix & rMatrix) const;
	Tmatrix operator - (const Tmatrix & rMatrix) const;
	Tmatrix operator * (const Tmatrix & rMatrix) const;
	Tmatrix operator * (double rValue) const;
	Tmatrix operator ! ();//�������������� �������
	Tmatrix & T();//���������������� �������
	Tmatrix& swapRows(int pos, int newPos);
	Tmatrix I(int rows);//��������� ��������� �������
	Tvector operator * (const Tvector& rVector) const; //��������� ������� �� ������
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

