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
	Tvector(); //����������� �� ���������
	Tvector(int size);//����������� �� �������
	Tvector(const Tvector & rVector);//����������� �����������
	void resize(int size);
	int size() const;
	void print() const;
	friend void print(const Tvector & printVector)
	{
		std::cout << "["; std::copy(printVector.data.begin(), printVector.data.end(), std::ostream_iterator<double>(std::cout, " ")); std::cout << "]"<< std::endl;
	}
	double operator [] (int place) const { return this->data.at(place); }//�������� ������ ��������
	double & operator [] (int place) { return this->data.at(place); }//�������� ������� � ��������� ��������
	Tvector & operator = (const Tvector & rVector);//����������� �������
	Tvector operator + (const Tvector & rVector) const;
	Tvector operator - (const Tvector & rVector) const;
	Tvector operator ^ (const Tvector & rVector) const; //��������� ��������� ��������
	Tvector operator * (double rValue) const; //���������� ������� �� �����
	double operator * (const Tvector & rVector) const; //��������� ��������� ��������

	~Tvector();
};

