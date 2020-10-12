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

std::default_random_engine rng(std::random_device{}());
std::uniform_real_distribution<double> dist(0, 1);

int main()
{
	int* neurons = new int[5]{ 1, 2, 3, 2, 1 };

	Network network(neurons, 5);

	Matrix mat(1, 1);
	mat[0][0] = .5;

	Matrix res(1, 1);
	mat[0][0] = 1;
	
	double temp;
	for (int i = 0; i < 10000; i++)
	{
		temp = dist(rng);

		mat[0][0] = temp;

		if (temp > .5)
			res[0][0] = 1;
		else
			res[0][0] = 0;

		network.train(mat, res);
	}

	double choice = 0;
	while (choice != -1)
	{
		std::cin >> choice;
		mat[0][0] = choice;
		print(network.forward(mat));
		std::cout << std::endl;
	}
}