#pragma once
#include <stdexcept>

class Proxy
{
	private:	
		double* data;
		size_t limit;

	public:
		Proxy(double* _data, size_t _limit);
		double& operator[](size_t index);
};