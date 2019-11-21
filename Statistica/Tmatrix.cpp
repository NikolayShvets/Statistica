#include "pch.h"
#include "matrix.h"


Tmatrix::Tmatrix(){
	this->resize(0, 0);
}

Tmatrix::Tmatrix(int rows, int columns){
	this->resize(rows, columns);
}

Tmatrix::Tmatrix(const Tmatrix & rMatrix){
	this->data.assign(rMatrix.data.begin(), rMatrix.data.end());
}

void Tmatrix::resize(int rows, int columns){
	this->data.resize(rows);
	for (int i = 0; i < this->rowsCount(); ++i) {
		this->data.at(i).resize(columns);
	}
}

int Tmatrix::rowsCount() const{
	return this->data.size();
}

int Tmatrix::colsCount() const{
	return this->data.front().size();
}

double Tmatrix::det()
{
	//int i, j;
	const double EPS = 1E-9;
	assert(this->rowsCount() == this->colsCount());
	double det = 1;
	for (int i = 0; i < this->rowsCount(); ++i) {
		int k = i;
		for (int j = i + 1; j < this->rowsCount(); ++j)
			if (abs(this->operator()(i,j) > abs(this->operator()(k, i))))
				k = j;
		if (abs(this->operator()(k, i)) < EPS) {
			det = 0;
			break;
		}
		this->swapRows(i, k);
		if (i != k)
			det = -det;
		det *= this->operator()(i, i);
		for (int j = i + 1; j < this->rowsCount(); ++j)
			this->operator()(i, j) /= this->operator()(i, i);
		for (int j = 0; j < this->rowsCount(); ++j)
			if (j != i && abs(this->operator()(j, i)) > EPS)
				for (int k = i + 1; k < this->rowsCount(); ++k)
					this->operator()(j, k) -= this->operator()(i, k) * this->operator()(j, i);
	}

	return det;
}

Tmatrix & Tmatrix::operator = (const Tmatrix & rMatrix)
{
	this->data.assign(rMatrix.data.begin(), rMatrix.data.end());
	return *this;
}

Tmatrix Tmatrix::operator + (const Tmatrix & rMatrix) const
{
	assert( ( rowsCount() == rMatrix.rowsCount()) && (colsCount() == rMatrix.colsCount()));
	Tmatrix resMatrix;
	for (int i = 0; i < this->rowsCount(); ++i) {
		for (int j = 0; j < this->colsCount(); ++j) {
			resMatrix(i, j) = this->operator() (i, j) + rMatrix(i, j);
		}
	}
	return resMatrix;
}

Tmatrix Tmatrix::operator-(const Tmatrix & rMatrix) const
{
	assert( (rowsCount() == rMatrix.rowsCount()) && (colsCount() == rMatrix.colsCount()) );
	Tmatrix resMatrix;
	for (int i = 0; i < this->rowsCount(); ++i) {
		for (int j = 0; j < this->colsCount(); ++j) {
			resMatrix(i, j) = this->operator() (i, j) + rMatrix(i, j);
		}
	}
	return resMatrix;
}

Tmatrix Tmatrix::operator*(const Tmatrix & rMatrix) const
{
	assert(this->colsCount() == rMatrix.rowsCount());
	Tmatrix resMatrix(this->rowsCount(), rMatrix.colsCount());
	for (int i = 0; i < resMatrix.rowsCount(); i++)
	{
		for (int j = 0; j < resMatrix.colsCount(); j++)
		{
			resMatrix(i, j) = 0;
			for (int k = 0; k < this->colsCount(); k++)
			{
				resMatrix(i, j) += this->operator()(i, k) * rMatrix(k, j);
			}
		}
	}
	return resMatrix;
}

Tmatrix Tmatrix::operator*(double rValue) const
{
	Tmatrix resMatrix(this->rowsCount(), this->colsCount());
	for (int i = 0; i < this->rowsCount(); ++i) {
		for (int j = 0; j < this->colsCount(); ++j) {
			resMatrix(i, j) = this->operator()(i, j) * rValue;
		}
	}
	return resMatrix;
}

Tmatrix Tmatrix::operator!()
{
	Tmatrix R(this->rowsCount(), this->rowsCount()); //эту матрицу будем возвращать из метода, чтобы не ломать исходную
	Tmatrix M;//в эту матрицу скопируем исходную матрицу
	M = *this;//чтобы так же не ломать исходную
	Tmatrix I(this->rowsCount(), this->rowsCount());
	I = I.I(this->rowsCount());
	long double element = 0;
	for (int i = 0; i < this->rowsCount(); i++) {
		element = this->operator()(i, i);
		if (element == 0) {//если на главной диагонали нулевой элемент, меняем строки местами
			bool swapFlag = false;
			for (int s = i; s < this->rowsCount(); s++) {
				if (this->operator()(s, i) != 0) {
					swapFlag = true;
					M.swapRows(i, s);
					I.swapRows(i, s);
				}
			}
			if (swapFlag == false)
				break;
		}//далее все по алгоритму. впринципе работает корректно
		element = this->operator()(i, i);
		for (int k = 0; k < this->rowsCount(); k++) {
			this->operator()(i, k) = this->operator()(i, k) / element;
			I(i, k) = I(i, k) / element;
		}
		double c = 0;
		for (int k = 0; k < this->rowsCount(); k++) {
			if (k == i) continue;
			c = this->operator()(k, i);
			for (int p = 0; p < this->rowsCount(); p++) {
				this->operator()(k, p) = this->operator()(k, p) - c * this->operator()(i, p);
				I(k, p) = I(k, p) - c * I(i, p);
				R(k, p) = I(k, p);
			}
		}
	}
	for (int i = 0; i < this->rowsCount(); i++) {
		for (int j = 0; j < this->rowsCount(); j++) {
			R(i, j) = I(i, j);
		}
	}
	return R;
}

Tmatrix & Tmatrix::T()
{
	assert(this->rowsCount() == this->colsCount());
	for (int i = 0; i < this->rowsCount() - 1; i++)
		for (int j = i + 1; j < this->rowsCount(); j++)
			std::swap(this->operator()(i, j), this->operator()(j, i));
	return *this;
}

Tmatrix & Tmatrix::swapRows(int pos, int newPos)
{
	long double tmp_cell;
	for (int k = 0; k < this->rowsCount(); k++)
	{
		tmp_cell = this->operator()(pos, k);
		this->operator()(pos, k) = this->operator()(newPos, k);
		this->operator()(newPos, k) = tmp_cell;
	}
	return *this;
}

Tmatrix Tmatrix::I(int rows)
{
	Tmatrix I(this->rowsCount(), this->rowsCount());
	for (int i = 0; i < this->rowsCount(); i++) {
		I(i, i) = 1;
		for (int j = i + 1; j < this->rowsCount(); j++)
		{
			I(i, j) = I(j, i) = 0;
		}
	}
	return I;
}

Tvector Tmatrix::operator*(const Tvector & rVector) const
{
	assert(rVector.size() == this->rowsCount());
	Tvector V(this->rowsCount());
	for (int i = 0; i < this->rowsCount(); i++)
	{
		V[i] = 0;
		for (int j = 0; j < this->colsCount(); j++)
			V[i] += this->operator()(i, j) * rVector[j];
	}
	return V;
}


Tmatrix::~Tmatrix()
{
}
