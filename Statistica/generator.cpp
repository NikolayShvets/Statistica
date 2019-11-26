#include "pch.h"
#include "generator.h"
using namespace std;
generator::generator(long double m, long double d)
{
	this->m = m;
	this->d = d;
}

long double generator::white_noise_generator()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	normal_distribution<long double> distribution(m, d);
	nu_0 = distribution(generator);
	return nu_0;
}
generator::~generator()
{

}
