#include "NPPFile.h"
#include <iostream>
#include <iomanip>

NPPFile::NPPFile() { }

NPPFile::~NPPFile()
{

}

void NPPFile::read(const char* fname, Network& nn)
{	
	std::ifstream file(fname, std::ios::binary);
	
	if (file)
	{
		nn.~Network();

		file.read(reinterpret_cast<char*>(&header), sizeof(NPPFileHeader));

		if (!header.valid())
			throw;

		layers = new size_t[header.layers];

		for (int i = 0; i < header.layers; i++)
		{
			file.read(reinterpret_cast<char*>(&layers[i]), sizeof(size_t));
		}

		nn = Network(layers, header.layers, header.lr, header.gamma);

		delete[] layers;

		size_t bufferSize = 0;
		size_t temp;

		for (size_t i = 0; i < nn.layers - 1; i++)
		{
			temp = nn.neurons[i + 1] * nn.neurons[i];
			if (temp > bufferSize)
				bufferSize = temp;
		}

		double* buffer = new double[bufferSize];
		for (size_t i = 0; i < nn.layers - 1; i++)
		{
			readMatrix(&nn.weights[i], buffer, file);
			readMatrix(&nn.biases[i],  buffer, file);
			readMatrix(&nn.LWC[i],     buffer, file);
			readMatrix(&nn.LBC[i],     buffer, file);
		}

		delete[] buffer;
	}
}

inline void NPPFile::readMatrix(Matrix* mat, double* buffer, std::ifstream& file)
{
	for (size_t bf = 0; bf < mat->length(); bf++)
	{
		file.read(reinterpret_cast<char*>(&buffer[bf]), sizeof(double));
	}
	mat->readFromArray(buffer);
}

void NPPFile::write(const char* fname, Network& nn)
{
	header.gamma = nn.gamma;
	header.lr = nn.learningRate;
	header.layers = nn.layers;

	std::ofstream file(fname, std::ios::binary);

	if (file)
	{
		file.write(reinterpret_cast<char*>(&header), sizeof(header));

		for (int i = 0; i < nn.layers; i++)
		{
			file.write(reinterpret_cast<char*>(&nn.neurons[i]), sizeof(size_t));
		}

		for (int i = 0; i < nn.layers - 1; i++)
		{
			writeMatrix(nn.weights[i], file);
			writeMatrix(nn.biases[i],  file);
			writeMatrix(nn.LWC[i],     file);
			writeMatrix(nn.LBC[i],     file);
		}
	}
}

inline void NPPFile::writeMatrix(Matrix& mat, std::ofstream& file)
{
	for (int x = 0; x < mat.rows; x++)
	{
		for (int y = 0; y < mat.cols; y++)
		{
			file.write(reinterpret_cast<char*>(&mat[x][y]), sizeof(double));
		}
	}
}
