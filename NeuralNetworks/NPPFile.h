#pragma once
#pragma once
#include <fstream>
#include "Network.h"

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

struct NPPFile
{
	NPPFileHeader header;
	size_t* layers{ 0 };

	NPPFile();
	~NPPFile();

	void read(const char* fname, Network& nn);
	inline void readMatrix(Matrix* mat, double* buffer, std::ifstream& file);

	void write(const char* fname, Network& nn);
	inline void writeMatrix(Matrix& mat, std::ofstream& file);

};