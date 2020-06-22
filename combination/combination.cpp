#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "parameter.h"
#include "statement.h"
using namespace std;

int main()
{
    //规定文件地址
    string broadcastfile = "D:/学习要紧/GNSS/编程作业二/相关数据/JFNG00CHN_R_20200010000_01D_30S_MO.20o";//请自行修改源文件位置
    string outfile = "D:/学习要紧/GNSS/编程作业二/得出数据";//请自行修改输出文件夹的位置

    //声明所有的卫星对象数组
    GPSdata G[5000];
    BDSdata C[12000];

    //读取文件，输入要处理的卫星的
    readrinex(G, C, broadcastfile);

   //计算GPS和北斗的GF、MW组合值，并输出结果
    calGPS(G, broadcastfile, outfile);
    calBDS(C, broadcastfile, outfile);
    
    return 0;
}
