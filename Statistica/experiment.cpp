#include "pch.h"
#include "experiment.h"


Texperiment::Texperiment()
{
}

void Texperiment::removeCharsFromString(std::string &str, const char* charsToRemove) {
	for (unsigned int i = 0; i < strlen(charsToRemove); ++i) {
		str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
	}
}

void Texperiment::setX() {
	this->file.open("TABLE.txt");
	std::vector<std::string> vecstr;
	std::string str{ "" }, supstr{ "" };
	int i{ 0 }, j{ 0 };
	X.resize(3, 6);
	while (std::getline(this->file, str)) {
		if (str.front() != 'X') continue;
		removeCharsFromString(str, "X=[ ]");
		str.erase(0, 1);
		int temp = j;
		for (int k = 0; k < str.size(); ++k) {
			if (str[k] != ',' && k != str.size() - 1) {
				supstr.push_back(str[k]);
			}else{
				X(i, j - temp) = std::stod(supstr);
				supstr.clear();
				++j;
			}
		}
		++i;
	}
	print(X);
	std::cout << X.rowsCount() << "x" << X.colsCount() << std::endl;
	file.close();
}

void Texperiment::setY() {
	this->file.open("TABLE.txt");
	std::vector<std::string> vecstr;
	std::string str{ "" }, supstr{ "" };
	int i{ 0 }, j{ 0 };
	Y.resize(5, 6);
	while (std::getline(this->file, str)) {
		if (str.front() != 'Y') continue;
		removeCharsFromString(str, "Y=[ ]");
		str.erase(0, 1);
		int temp = j;
		for (int k = 0; k < str.size(); ++k) {
			if (str[k] != ',' && k != str.size() - 1) {
				supstr.push_back(str[k]);
			}
			else {
				Y(i, j - temp) = std::stod(supstr);
				supstr.clear();
				++j;
			}
		}
		++i;
	}
	print(Y);
	std::cout << Y.rowsCount() << "x" << Y.colsCount() << std::endl;
	file.close();
}

Texperiment::~Texperiment()
{
	this->file.close();
}
