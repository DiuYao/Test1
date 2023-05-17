// Processing_Light_Intensity.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "ComputeRealProj.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

int main()
{
    FILE* fp;
    size_t dNum = 4;
    size_t views = 2;
    size_t fileHeader = 16;   // 单位 Byte

    fp = fopen("TestData/test.raw", "rb");
    ComputeRealProj *Proj =new ComputeRealProj(fp, dNum, views, fileHeader);
    fclose(fp);

    unsigned short* dataI = new unsigned short[dNum * dNum * views];
    float* dataI0 = new float[dNum * dNum];
    float* proj = new float[dNum * dNum * views];
    Proj->getIandI0(dataI, dataI0);
    //dataI = Proj->getI();
    //dataI0 = Proj->getI0();
    Proj->computeProj();
    Proj->getProj(proj);

    char wPath[] = "projData/test.raw";
    Proj->saveAs(wPath);


#if 0
    cout << "dataI :" << endl;
    for (size_t i = 0; i < dNum * dNum * views; i++)
    {
        cout << dataI[i] << " ";
    }

    cout << endl << "dataI0 :" << endl;
    for (size_t i = 0; i < dNum * dNum; i++)
    {
        cout << *(dataI0 + i) << " ";
    }

    cout << endl << "proj :" << endl;
    for (size_t i = 0; i < dNum * dNum * views; i++)
    {
        cout << proj[i] << " ";
    }
#endif // 0

    

    /*fp = fopen(wPath, "wb");
    fwrite(proj, 1, dNum * dNum * views, fp);
    fclose(fp);*/

    float* projA = new float[dNum * dNum * views];
    fp = fopen("projData/test.raw", "rb");
    fread(projA, 1, dNum * dNum * views * sizeof(float), fp);
    fclose(fp);
    cout << endl << "projA :" << endl;
    for (size_t i = 0; i < dNum * dNum * views; i++)
    {
        cout << projA[i] << " ";
    }
    delete Proj;
}












// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
