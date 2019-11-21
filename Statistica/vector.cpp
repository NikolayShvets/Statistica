#include "pch.h"
#include "vector.h"


Tvector::Tvector(){
	this->resize(0);
}

Tvector::Tvector(int size){
	this->resize(size);
}

Tvector::Tvector(const Tvector & rVector) {
	this->data.assign(rVector.data.begin(), rVector.data.end());
}

void Tvector::resize(int size) {
	assert(size >= 0);
	this->data.resize(size);
}

int Tvector::size() const {
	return this->data.size();
}

void Tvector::print() const {
	std::cout << "["; std::copy(this->data.begin(), this->data.end(), std::ostream_iterator<double>(std::cout, " ")); std::cout << "]" << std::endl;
}

Tvector & Tvector::operator = (const Tvector & rVector)
{
	this->data = rVector.data;
	return *this;
}
Tvector Tvector::operator + (const Tvector & rVector) const
{
	Tvector resVector;
	std::transform(this->data.begin(), this->data.end(),
		rVector.data.begin(), std::back_inserter(resVector.data),
		std::plus<long double>());
	return resVector;
}
Tvector Tvector::operator - (const Tvector & rVector) const
{
	Tvector resVector;
	std::transform(this->data.begin(), this->data.end(),
		rVector.data.begin(), std::back_inserter(resVector.data),
		std::minus<long double>());
	return resVector;
}

Tvector Tvector::operator^(const Tvector & rVector) const {
	assert(rVector.size() == 3);
	Tvector resVector(3);
	resVector[0] = this->operator[](1) * rVector[2] - rVector[1] * this->operator[](2);
	resVector[1] = this->operator[](2) * rVector[0] - rVector[2] * this->operator[](0);
	resVector[2] = this->operator[](0) * rVector[1] - rVector[0] * this->operator[](1);
	return resVector;
}

double Tvector::operator*(const Tvector & rVector) const {
	assert(rVector.size() == size());
	long double res = 0;
	for (int i = 0; i < rVector.size(); i++)
	{
		res += this->operator[](i) * rVector[i];
	}
	return res;
}

Tvector Tvector::operator * (double rValue) const {
	Tvector resVector(this->size());
	std::vector<double>::const_iterator it;
	it = this->data.begin();
	int i{0};
	while (it != this->data.end()) {
		resVector[i] = *it * rValue;
		++i;
		++it;
	}
	return resVector;
}


Tvector::~Tvector(){
}
