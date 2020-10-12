#pragma once
#include "Matrix.h"
#include <math.h>
class Network
{
	friend class Matrix;
	int layers;
	double learningRate = 0.1;
	double gamma = 0.7;

	Matrix *weights, *biases, *values, *LWC, *LBC;

	public:
		Network(int* neurons, int _layers);
		static double sigmoid(double value);
		static double dsigmoid(double value);
		Matrix forward(Matrix input);
		void backPropagate(Matrix error);
		void train(Matrix input, Matrix output);
};