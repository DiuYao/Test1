#include"ComputeRealProj.h"

#include <cmath>


ComputeRealProj::ComputeRealProj(FILE* m_fp, size_t m_dNum, size_t m_views, size_t m_fileHeader)
{
	fp = m_fp;
	dNum = m_dNum;
	views = m_views;
	fileHeader = m_fileHeader;

	readIandI0();
	//fclose(fp);
}

ComputeRealProj::~ComputeRealProj()
{
	std::cout << "调用析构函数" << std::endl;
	delete[] dataI;
	delete[] dataI0;
	delete[] proj;
}

void ComputeRealProj::getIandI0(unsigned short *m_dataI, float *m_dataI0)
{
	for (size_t i = 0; i < dNum * dNum * views; i++)
	{
		m_dataI[i] = dataI[i];
	}
	for (size_t i = 0; i < dNum * dNum; i++)
	{
		m_dataI0[i] = dataI0[i];
	}
}

unsigned short* ComputeRealProj::getI()
{
	return dataI;
}

float* ComputeRealProj::getI0()
{
	return dataI0;
}

void ComputeRealProj::readIandI0()
{
	dataI = new unsigned short[dNum * dNum * views];
	dataI0 = new float[dNum * dNum];
	fseek(fp, fileHeader, SEEK_SET);
	fread(dataI, 1, dNum * dNum * views * sizeof(unsigned short), fp);
	fread(dataI0, 1, dNum * dNum * sizeof(float), fp);
}

void ComputeRealProj::computeProj()
{
	proj = new float[dNum * dNum * views];
	for (size_t i = 0; i < views; i++)
	{
		for (size_t j = 0; j < dNum * dNum; j++)
		{
			proj[j + i * dNum * dNum] = log((dataI0[j] + 1e-8) / (dataI[j + i * dNum * dNum] + 1e-8));
		}
	}
}

void ComputeRealProj::getProj(float* m_proj)
{
	for (size_t i = 0; i < views; i++)
	{
		for (size_t j = 0; j < dNum * dNum; j++)
		{
			m_proj[j + i * dNum * dNum] = proj[j + i * dNum * dNum];
		}
	}

}

void ComputeRealProj::saveAs(char* wPath)
{
	fp = fopen(wPath, "wb");
	fwrite(proj, 1, dNum * dNum * views* sizeof(float), fp);
	fclose(fp);
}
