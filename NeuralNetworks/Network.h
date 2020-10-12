#pragma once
#include "Matrix.h"
#include <math.h>
class Network
{
	//friend class Matrix;
	size_t layers;
	double learningRate = 0.1;
	double gamma = 0.7;

	Matrix *weights, *biases, *values, *LWC, *LBC;

	public:
		Network(int* neurons, size_t _layers, double _learningRate = 0.1, double _gamma = 0.1);
		static double sigmoid(double value);
		static double dsigmoid(double value);
		Matrix forward(Matrix input);
		void backPropagate(Matrix error);
		void train(Matrix input, Matrix output);
};