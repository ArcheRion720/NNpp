#pragma once
#include "Matrix.h"
#include <math.h>

class Network
{
	friend struct NPPFile;
	 
	size_t layers;
	size_t* neurons;
	Matrix *weights, *biases, *values, *LWC, *LBC;

	public:
		double learningRate = 0.2;
		double gamma = 0.5;

		Network();
		Network(size_t* _neurons, size_t _layers, double _learningRate = 0.1, double _gamma = 0.1);
		~Network();

		static double sigmoid(double value);
		static double dsigmoid(double value);
		Matrix forward(Matrix input);
		void backPropagate(Matrix error);
		void train(Matrix input, Matrix output);
};