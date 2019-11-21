#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <iostream>

class Tvector
{
private:
	std::vector<double> data;
public:
	Tvector(); //конструктор по умолчанию
	Tvector(int size);//конструктор по размеру
	Tvector(const Tvector & rVector);//конструктор копирования
	void resize(int size);
	int size() const;
	void print() const;
	friend void print(const Tvector & printVector)
	{
		std::cout << "["; std::copy(printVector.data.begin(), printVector.data.end(), std::ostream_iterator<double>(std::cout, " ")); std::cout << "]"<< std::endl;
	}
	double operator [] (int place) const { return this->data.at(place); }//оператор чтения элемента
	double & operator [] (int place) { return this->data.at(place); }//оператор доступа и изменения элемента
	Tvector & operator = (const Tvector & rVector);//копирование вектора
	Tvector operator + (const Tvector & rVector) const;
	Tvector operator - (const Tvector & rVector) const;
	Tvector operator ^ (const Tvector & rVector) const; //векторное умножение векторов
	Tvector operator * (double rValue) const; //умноежение вектора на число
	double operator * (const Tvector & rVector) const; //скалярное умножение векторов

	~Tvector();
};

