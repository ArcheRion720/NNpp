#pragma once
#include "Matrix.h"
#include <math.h>
#include <fstream>
#include <iostream>

#define DELETE(ptr) if(ptr != nullptr) delete[] ptr;

class Network
{	 
	private:
		size_t layers;
		Matrix *weights, *biases, *values, *LWC, *LBC;

		void init(size_t* _neurons, size_t _layers, double _learningRate = 0.1, double _gamma = 0.1);
		void dispose();

	public:
		size_t* neurons;
		double learningRate;
		double gamma;

		Network();
		Network(size_t* _neurons, size_t _layers, double _learningRate = 0.1, double _gamma = 0.1);
		~Network();

		static double sigmoid(double value);
		static double dsigmoid(double value);
		Matrix forward(Matrix input);
		void backPropagate(Matrix error);
		void train(Matrix input, Matrix output);

		struct File
		{
			public:

				struct InvalidHeaderException : public std::exception
				{
					const char* what() const throw()
					{
						return "NPP file header was invalid";
					}
				};

				static void read(const char* fname, Network& nn);
				static void write(const char* fname, Network& nn);

			private:
				inline static void writeMatrix(Matrix& mat, std::ofstream& file);	
				inline static void readMatrix(Matrix* mat, double* buffer, std::ifstream& file);
		};

	private:
		#pragma pack(push, 1)
		struct NPPFileHeader
		{
			char magic[3]{ 'N', 'P', 'P' };
			size_t layers{ 0 };
			double lr{ 0 };
			double gamma{ 0 };
			char magic2[2]{ '.', '.' };

			bool valid()
			{
				return (
					magic[0] == 'N' &&
					magic[1] == 'P' &&
					magic[2] == 'P' &&
					magic2[0] == '.' &&
					magic2[1] == '.');
			}
		};
		#pragma pack(pop)
};