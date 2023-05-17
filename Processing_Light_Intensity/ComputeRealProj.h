#pragma once

#include <iostream>

class ComputeRealProj
{
public:
	ComputeRealProj(FILE* m_fp, size_t m_dNum, size_t views, size_t m_fileHeader);
	~ComputeRealProj();

	void getIandI0(unsigned short* m_dataI, float* m_dataI0);
	
	unsigned short* getI();
	float* getI0();
	void readIandI0();

	void computeProj();
	void getProj(float* m_proj);

	void saveAs(char* wPath);

private:
	size_t dNum;
	size_t views;

	FILE* fp;

	size_t fileHeader;
	unsigned short* dataI; //= new unsigned short[dNum * dNum * views];
	float* dataI0;// = new float[dNum * dNum];

	float* proj;// = new float[dNum * dNum * views];
};

