#include "Network.h"

Network::Network()
{
}

Network::Network(size_t* _neurons, size_t _layers, double _learningRate, double _gamma) : layers(_layers), learningRate(_learningRate), gamma(_gamma)
{
	neurons = new size_t[_layers];
	memcpy(neurons, _neurons, _layers * sizeof(size_t));

	weights = new Matrix[layers - 1];
	biases  = new Matrix[layers - 1];
	values  = new Matrix[layers];
	LWC     = new Matrix[layers - 1];
	LBC     = new Matrix[layers - 1];

	for (size_t i = 0; i < layers - 1; i++)
	{
		weights[i].initRandom(_neurons[i + 1], _neurons[i], -2.0, 2.0);
		biases[i].initRandom(_neurons[i + 1], 1, -2, 2);

		LWC[i] = Matrix(_neurons[i + 1], _neurons[i]);
		LBC[i] = Matrix(_neurons[i + 1], 1);
	}
}

Network::~Network()
{
	//delete[] neurons;
	//delete[] weights;
	//delete[] biases;
	//delete[] values;
	//delete[] LWC;
	//delete[] LBC;
}

double Network::sigmoid(double value)
{
	return 1.0 / (1.0 + exp(-value));
}

double Network::dsigmoid(double value)
{
	return value * (1.0 - value);
}

Matrix Network::forward(Matrix input)
{
	values[0] = input;

	for (size_t i = 0; i < layers - 1; i++)
	{
		values[i + 1] = (weights[i] * values[i]) + biases[i];

		values[i + 1].callOnElements(sigmoid);
	}

	return values[layers - 1];
}

void Network::backPropagate(Matrix error)
{
	for (size_t i = layers - 1; i --> 0; )
	{
		Matrix ds = Matrix(values[i + 1]);
		ds.callOnElements(dsigmoid);

		Matrix m = error ^ ds;

		LWC[i] = (LWC[i] * gamma) + ((m * learningRate) * ~values[i]);
		LBC[i] = (LBC[i] * gamma) + (m * learningRate);

		weights[i] += LWC[i];
		biases[i] += LBC[i];

		error = ~weights[i] * error;
	}	
}

void Network::train(Matrix input, Matrix output)
{
	Matrix error = output - forward(input);
	backPropagate(error);
}