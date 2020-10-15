#include <iostream>
#include "Network.h"

void print(Matrix matrix)
{
	for (size_t i = 0; i < matrix.rows; i++)
	{
		for (size_t j = 0; j < matrix.cols; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

double dxor(double a, double b)
{
	if ((a < .5 && b < .5) || (a > .5 && b > .5))
		return 0.1;

	return 1.0;
}

std::default_random_engine rng(std::random_device{}());
std::uniform_real_distribution<double> dist(0, 1);

int main()
{
	int* neurons = new int[5]{ 2, 3, 3, 2, 1 };

	Network network(neurons, 5);

	Matrix mat(2, 1);
	Matrix res(1, 1);

	double temp1;
	double temp2;
	for (int i = 0; i < 1000; i++)
	{
		temp1 = dist(rng);
		temp2 = dist(rng);

		mat[0][0] = temp1;
		mat[1][0] = temp2;

		res[0][0] = dxor(mat[0][0], mat[1][0]);

		network.train(mat, res);
	}

	std::cout << "Trained!" << std::endl;

	double value;
	for (int i = 0; i < 3; i++)
	{
		std::cin >> value;
		mat[0][0] = value;
		std::cin >> value;
		mat[1][0] = value;
		print(network.forward(mat));
		std::cout << std::endl;
	}
}