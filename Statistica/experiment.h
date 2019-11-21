#pragma once
#include "matrix.h"
#include "vector.h"
#include <string>
#include <fstream>

class Texperiment
{
private:
	Tmatrix X, Y; //вход выход
	std::ifstream file;
public:
	Texperiment();
	void setX();
	void setY();
	void seModel();
	void removeCharsFromString(std::string &str, const char* charsToRemove);
	Tmatrix getF();
	Tvector getSigma();

	~Texperiment();
};

