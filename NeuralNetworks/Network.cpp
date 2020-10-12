#include "Network.h"

Network::Network(int* neurons, int _layers) : layers(_layers)
{
	weights = new Matrix[layers - 1];
	biases  = new Matrix[layers - 1];
	values  = new Matrix[layers];
	LWC     = new Matrix[layers - 1];
	LBC     = new Matrix[layers - 1];

	for (int i = 0; i < layers - 1; i++)
	{
		weights[i].initRandom(neurons[i + 1], neurons[i], -2.0, 2.0);
		biases[i].initRandom(neurons[i + 1], 1, -2, 2);

		LWC[i] = Matrix(neurons[i + 1], neurons[i]);
		LBC[i] = Matrix(neurons[i + 1], 1);
	}
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

	for (int i = 0; i < layers - 1; i++)
	{
		values[i + 1] = (weights[i] * values[i]) + biases[i];

		for (int j = 0; j < values[i + 1].rows; j++)
		{
			for (int k = 0; k < values[i + 1].cols; k++)
			{
				values[i + 1][j][k] = sigmoid(values[i + 1][j][k]);
			}
		}
	}

	return values[layers - 1];
}

void Network::backPropagate(Matrix error)
{
	for (int i = layers - 2; i >= 0; i--)
	{
		Matrix ds = Matrix(values[i + 1]);
		for (int j = 0; j < ds.rows; j++)
		{
			for (int k = 0; k < ds.cols; k++)
			{
				ds[j][k] = dsigmoid(ds[j][k]);
			}
		}

		Matrix m = error ^ ds;

		LWC[i] = (LWC[i] * gamma) + ((m * learningRate) * values[i].transpose());
		LBC[i] = (LBC[i] * gamma) + (m * learningRate);

		weights[i] += LWC[i];
		biases[i] += LBC[i];

		error = weights[i].transpose() * error;

		m.dispose();
		ds.dispose();
	}	
}

void Network::train(Matrix input, Matrix output)
{
	Matrix error = output - forward(input);
	backPropagate(error);
}