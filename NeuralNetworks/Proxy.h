#pragma once
#include <stdexcept>

class Proxy
{
	private:	
		double* data;
		int limit;

	public:
		Proxy(double* _data, int _limit);
		double& operator[](int index);
};