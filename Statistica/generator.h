#pragma once
#include <random>
#include <iostream>
#include <string>
#include <chrono>
#include <math.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

class generator
{
public:
	generator(long double m, long double d);
	~generator();
	long double m, d;
	long double nu;
	long double white_noise_generator();
	long double nu_0 = 0;
};

