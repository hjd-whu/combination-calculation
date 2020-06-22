//用于计算组合值和写入文件
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "parameter.h"
#include "statement.h"
using namespace std;

//计算GPS的GF和MW组合值函数
void calGPS(GPSdata G[5000],  string broadcastfile,string outfile)
{
    //放入常数
    double c = 299792458;//光速
    double L1 = 1575.42 * pow(10, 6);//GPS的L1相位
    double lambda1 = c / L1;//GPS的L1的波长
    double L2 = 1227.6 * pow(10, 6);//GPS的L2相位
    double lambda2 = c / L2;//GPS的L2的波长
    double B1I = 1561.098 * pow(10, 6);//北斗的L1相位
    double lambdaB1I = c / B1I;//北斗的L1的波长
    double B3I = 1268.52 * pow(10, 6);//北斗的L3相位
    double lambdaB3I = c / B3I;//北斗的L3的波长

    //创建GPS卫星的输出数组和计数单位
    double G01_result[1000][3];//用于输出结果
    int G01num = 0;//用于计数
    double G02_result[1000][3];//用于输出结果
    int G02num = 0;//用于计数
    double G03_result[1000][3];//用于输出结果
    int G03num = 0;//用于计数
    double G04_result[1000][3];//用于输出结果
    int G04num = 0;//用于计数
    double G05_result[1000][3];//用于输出结果
    int G05num = 0;//用于计数
    double G03_result_time[1000][9];//用于输出结果
    //计算GPS卫星
    for (int i = 0; i < 5000; i++)
    {
        if ((G[i].L1C == 0) | (G[i].L2W == 0) | (G[i].C1C == 0) | (G[i].C2W == 0))//不使用缺失数据的时刻
            continue;
        else
        {
            G[i].GF_L = lambda1 * G[i].L1C - lambda2 * G[i].L2W;
            G[i].GF_P = G[i].C1C - G[i].C2W;
            G[i].MW = -(L1 - L2) / (L1 + L2) * (G[i].C1C / lambda1 + G[i].C2W / lambda2) + (G[i].L1C - G[i].L2W);
            if (G[i].PRN == "G01")
            {
                G01_result[G01num][0] = G[i].GF_L;
                G01_result[G01num][1] = G[i].GF_P;
                G01_result[G01num][2] = G[i].MW;
                G01num++;
            }
            if (G[i].PRN == "G02")
            {
                G02_result[G02num][0] = G[i].GF_L;
                G02_result[G02num][1] = G[i].GF_P;
                G02_result[G02num][2] = G[i].MW;
                G02num++;
            }
            if (G[i].PRN == "G03")
            {
                G03_result[G03num][0] = G[i].GF_L;
                G03_result[G03num][1] = G[i].GF_P;
                G03_result[G03num][2] = G[i].MW;
                G03_result_time[G03num][0] = G[i].GF_L;
                G03_result_time[G03num][1] = G[i].GF_P;
                G03_result_time[G03num][2] = G[i].MW;
                G03_result_time[G03num][3] = G[i].year;
                G03_result_time[G03num][4] = G[i].month;
                G03_result_time[G03num][5] = G[i].day;
                G03_result_time[G03num][6] = G[i].hour;
                G03_result_time[G03num][7] = G[i].min;
                G03_result_time[G03num][8] = G[i].sec;
                G03num++;
            }
            if (G[i].PRN == "G04")
            {
                G04_result[G04num][0] = G[i].GF_L;
                G04_result[G04num][1] = G[i].GF_P;
                G04_result[G04num][2] = G[i].MW;
                G04num++;
            }
            if (G[i].PRN == "G05")
            {
                G05_result[G05num][0] = G[i].GF_L;
                G05_result[G05num][1] = G[i].GF_P;
                G05_result[G05num][2] = G[i].MW;
                G05num++;
            }
        }
    }

    //输出G01文件
    ofstream file_result_G01;//创建输出文件流
    //创建输出文件地址
    string name_G01 = "/G01result.txt";
    name_G01 = outfile + name_G01;
    file_result_G01.open(name_G01);//自行修改文件路径
    //开始输出二维数组里的数值
    for (int i = 0; i < G01num; i++)
    {
        file_result_G01.flags(ios::fixed);
        file_result_G01.precision(6);//设置保留小数位数，取6位
        file_result_G01 << setw(12) << right << G01_result[i][0] << setw(12) << right << G01_result[i][1] << setw(12) << right << G01_result[i][2] << "\n";
    }
    //关闭输出文件流
    file_result_G01.close();
    cout << "已输出G01卫星得到的GF和MW组合计算值" << endl;

    //输出G02文件
    ofstream file_result_G02;//创建输出文件流
    //创建输出文件地址
    string name_G02 = "/G02result.txt";
    name_G02 = outfile + name_G02;
    file_result_G02.open(name_G02);//自行修改文件路径
    //开始输出二维数组里的数值
    for (int i = 0; i < G02num; i++)
    {
        file_result_G02.flags(ios::fixed);
        file_result_G02.precision(6);//设置保留小数位数，取6位
        file_result_G02 << setw(12) << right << G02_result[i][0] << setw(12) << right << G02_result[i][1] << setw(12) << right << G02_result[i][2] << "\n";
    }
    //关闭输出文件流
    file_result_G02.close();
    cout << "已输出G02卫星得到的GF和MW组合计算值" << endl;

    //输出G03文件
    ofstream file_result_G03;//创建输出文件流
    //创建输出文件地址
    string name_G03 = "/G03result.txt";
    name_G03 = outfile + name_G03;
    file_result_G03.open(name_G03);//自行修改文件路径
    //开始输出二维数组里的数值
    for (int i = 0; i < G03num; i++)
    {
        file_result_G03.flags(ios::fixed);
        file_result_G03.precision(6);//设置保留小数位数，取6位
        file_result_G03 << setw(12) << right << G03_result[i][0] << setw(12) << right << G03_result[i][1] << setw(12) << right << G03_result[i][2] << "\n";
    }
    //关闭输出文件流
    file_result_G03.close();
    cout << "已输出G03卫星得到的GF和MW组合计算值" << endl;

    //输出G04文件
    ofstream file_result_G04;//创建输出文件流
    //创建输出文件地址
    string name_G04 = "/G04result.txt";
    name_G04 = outfile + name_G04;
    file_result_G04.open(name_G04);//自行修改文件路径
    //开始输出二维数组里的数值
    for (int i = 0; i < G04num; i++)
    {
        file_result_G04.flags(ios::fixed);
        file_result_G04.precision(6);//设置保留小数位数，取6位
        file_result_G04 << setw(12) << right << G04_result[i][0] << setw(12) << right << G04_result[i][1] << setw(12) << right << G04_result[i][2] << "\n";
    }
    //关闭输出文件流
    file_result_G04.close();
    cout << "已输出G04卫星得到的GF和MW组合计算值" << endl;

    //输出G05文件
    ofstream file_result_G05;//创建输出文件流
    //创建输出文件地址
    string name_G05 = "/G05result.txt";
    name_G05 = outfile + name_G05;
    file_result_G05.open(name_G05);//自行修改文件路径
    //开始输出二维数组里的数值
    for (int i = 0; i < G05num; i++)
    {
        file_result_G05.flags(ios::fixed);
        file_result_G05.precision(6);//设置保留小数位数，取6位
        file_result_G05 << setw(12) << right << G05_result[i][0] << setw(12) << right << G05_result[i][1] << setw(12) << right << G05_result[i][2] << "\n";
    }
    //关闭输出文件流
    file_result_G05.close();
    cout << "已输出G05卫星得到的GF和MW组合计算值" << endl;

    ////额外输出一个G03的带上时间的文件用于历元间求差，注意这里用的是连续的，中间没有断过
    //ofstream file_result_G03_time;//创建输出文件流
    ////创建输出文件地址
    //string name_G03_time = "/G03result_time.txt";
    //name_G03_time = outfile + name_G03_time;
    //file_result_G03_time.open(name_G03_time);//自行修改文件路径
    ////开始输出二维数组里的数值
    //for (int i = 0; i < G03num; i++)
    //{
    //    file_result_G03_time.flags(ios::fixed);
    //    file_result_G03_time.precision(6);//设置保留小数位数，取6位
    //    file_result_G03_time << setw(12) << right << G03_result_time[i][0] << setw(12) << right << G03_result_time[i][1] << setw(12) << right << G03_result_time[i][2]
    //        << setw(12) << right << G03_result_time[i][3] << setw(12) << right << G03_result_time[i][4] << setw(12) << right << G03_result_time[i][5]
    //        << setw(12) << right << G03_result_time[i][6] << setw(12) << right << G03_result_time[i][7] << setw(12) << right << G03_result_time[i][8] << "\n";
    //}
    ////关闭输出文件流
    //file_result_G03_time.close();
    //cout << "已输出G03卫星得到的GF和MW组合计算值，并具有时间" << endl;
}


//计算北斗的GF和MW组合值函数
void calBDS(BDSdata C[12000], string broadcastfile, string outfile)
{
    //放入常数
    double c = 299792458;//光速
    double L1 = 1575.42 * pow(10, 6);//GPS的L1频率
    double lambda1 = c / L1;//GPS的L1的波长
    double L2 = 1227.6 * pow(10, 6);//GPS的L2频率
    double lambda2 = c / L2;//GPS的L2的波长
    double B1I = 1561.098 * pow(10, 6);//北斗的L1频率
    double lambdaB1I = c / B1I;//北斗的L1的波长
    double B3I = 1268.52 * pow(10, 6);//北斗的L3频率
    double lambdaB3I = c / B3I;//北斗的L3的波长

    //创建北斗卫星的输出数组和计数单位
    double C01_result[3000][3];//用于输出结果
    int C01num = 0;//用于计数
    double C02_result[3000][3];//用于输出结果
    int C02num = 0;//用于计数
    double C06_result[3000][3];//用于输出结果
    int C06num = 0;//用于计数
    double C07_result[3000][3];//用于输出结果
    int C07num = 0;//用于计数
    double C20_result[3000][3];//用于输出结果
    int C20num = 0;//用于计数
    double C21_result[3000][3];//用于输出结果
    int C21num = 0;//用于计数
    double C07_result_time[3000][9];//用于输出结果
    //计算北斗卫星
    for (int i = 0; i < 12000; i++)
    {
        if ((C[i].L2I == 0) | (C[i].L6I == 0) | (C[i].C2I == 0) | (C[i].C6I == 0))//不使用缺失数据的时刻
            continue;
        else
        {
            C[i].GF_L = lambdaB1I * C[i].L2I - lambdaB3I * C[i].L6I;
            C[i].GF_P = C[i].C2I - C[i].C6I;
            C[i].MW = -(B1I - B3I) / (B1I + B3I) * (C[i].C2I / lambdaB1I + C[i].C6I / lambdaB3I) + (C[i].L2I - C[i].L6I);
        }
        if (C[i].PRN == "C01")
        {
            C01_result[C01num][0] = C[i].GF_L;
            C01_result[C01num][1] = C[i].GF_P;
            C01_result[C01num][2] = C[i].MW;
            C01num++;
        }
        if (C[i].PRN == "C02")
        {
            C02_result[C02num][0] = C[i].GF_L;
            C02_result[C02num][1] = C[i].GF_P;
            C02_result[C02num][2] = C[i].MW;
            C02num++;
        }
        if (C[i].PRN == "C06")
        {
            C06_result[C06num][0] = C[i].GF_L;
            C06_result[C06num][1] = C[i].GF_P;
            C06_result[C06num][2] = C[i].MW;
            C06num++;
        }
        if (C[i].PRN == "C07")
        {
            C07_result[C07num][0] = C[i].GF_L;
            C07_result[C07num][1] = C[i].GF_P;
            C07_result[C07num][2] = C[i].MW;
            C07_result_time[C07num][0] = C[i].GF_L;
            C07_result_time[C07num][1] = C[i].GF_P;
            C07_result_time[C07num][2] = C[i].MW;
            C07_result_time[C07num][3] = C[i].year;
            C07_result_time[C07num][4] = C[i].month;
            C07_result_time[C07num][5] = C[i].day;
            C07_result_time[C07num][6] = C[i].hour;
            C07_result_time[C07num][7] = C[i].min;
            C07_result_time[C07num][8] = C[i].sec;
            C07num++;
        }
        if (C[i].PRN == "C20")
        {
            C20_result[C20num][0] = C[i].GF_L;
            C20_result[C20num][1] = C[i].GF_P;
            C20_result[C20num][2] = C[i].MW;
            C20num++;
        }
        if (C[i].PRN == "C21")
        {
            C21_result[C21num][0] = C[i].GF_L;
            C21_result[C21num][1] = C[i].GF_P;
            C21_result[C21num][2] = C[i].MW;
            C21num++;
        }
    }
    //输出C01文件
    ofstream file_result_C01;//创建输出文件流
    //创建输出文件地址
    string name_C01 = "/C01result.txt";
    name_C01 = outfile + name_C01;
    file_result_C01.open(name_C01);//自行修改文件路径
    //开始输出二维数组里的数值
    for (int i = 0; i < C01num; i++)
    {
        file_result_C01.flags(ios::fixed);
        file_result_C01.precision(6);//设置保留小数位数，取6位
        file_result_C01 << setw(12) << right << C01_result[i][0] << setw(12) << right << C01_result[i][1] << setw(12) << right << C01_result[i][2] << "\n";
    }
    //关闭输出文件流
    file_result_C01.close();
    cout << "已输出C01卫星得到的GF和MW组合计算值" << endl;

    //输出C02文件
    ofstream file_result_C02;//创建输出文件流
    //创建输出文件地址
    string name_C02 = "/C02result.txt";
    name_C02 = outfile + name_C02;
    file_result_C02.open(name_C02);//自行修改文件路径
    //开始输出二维数组里的数值
    for (int i = 0; i < C02num; i++)
    {
        file_result_C02.flags(ios::fixed);
        file_result_C02.precision(6);//设置保留小数位数，取6位
        file_result_C02 << setw(12) << right << C02_result[i][0] << setw(12) << right << C02_result[i][1] << setw(12) << right << C02_result[i][2] << "\n";
    }
    //关闭输出文件流
    file_result_C02.close();
    cout << "已输出C02卫星得到的GF和MW组合计算值" << endl;

    //输出C06文件
    ofstream file_result_C06;//创建输出文件流
    //创建输出文件地址
    string name_C06 = "/C06result.txt";
    name_C06 = outfile + name_C06;
    file_result_C06.open(name_C06);//自行修改文件路径
    //开始输出二维数组里的数值
    for (int i = 0; i < C06num; i++)
    {
        file_result_C06.flags(ios::fixed);
        file_result_C06.precision(6);//设置保留小数位数，取6位
        file_result_C06 << setw(12) << right << C06_result[i][0] << setw(12) << right << C06_result[i][1] << setw(12) << right << C06_result[i][2] << "\n";
    }
    //关闭输出文件流
    file_result_C06.close();
    cout << "已输出C06卫星得到的GF和MW组合计算值" << endl;

    //输出C07文件
    ofstream file_result_C07;//创建输出文件流
    //创建输出文件地址
    string name_C07 = "/C07result.txt";
    name_C07 = outfile + name_C07;
    file_result_C07.open(name_C07);//自行修改文件路径
    //开始输出二维数组里的数值
    for (int i = 0; i < C07num; i++)
    {
        file_result_C07.flags(ios::fixed);
        file_result_C07.precision(6);//设置保留小数位数，取6位
        file_result_C07 << setw(12) << right << C07_result[i][0] << setw(12) << right << C07_result[i][1] << setw(12) << right << C07_result[i][2] << "\n";
    }
    //关闭输出文件流
    file_result_C07.close();
    cout << "已输出C07卫星得到的GF和MW组合计算值" << endl;

    //输出C20文件
    ofstream file_result_C20;//创建输出文件流
    //创建输出文件地址
    string name_C20 = "/C20result.txt";
    name_C20 = outfile + name_C20;
    file_result_C20.open(name_C20);//自行修改文件路径
    //开始输出二维数组里的数值
    for (int i = 0; i < C20num; i++)
    {
        file_result_C20.flags(ios::fixed);
        file_result_C20.precision(6);//设置保留小数位数，取6位
        file_result_C20 << setw(12) << right << C20_result[i][0] << setw(12) << right << C20_result[i][1] << setw(12) << right << C20_result[i][2] << "\n";
    }
    //关闭输出文件流
    file_result_C20.close();
    cout << "已输出C20卫星得到的GF和MW组合计算值" << endl;

    //输出C21文件
    ofstream file_result_C21;//创建输出文件流
    //创建输出文件地址
    string name_C21 = "/C21result.txt";
    name_C21 = outfile + name_C21;
    file_result_C21.open(name_C21);//自行修改文件路径
    //开始输出二维数组里的数值
    for (int i = 0; i < C21num; i++)
    {
        file_result_C21.flags(ios::fixed);
        file_result_C21.precision(6);//设置保留小数位数，取6位
        file_result_C21 << setw(12) << right << C21_result[i][0] << setw(12) << right << C21_result[i][1] << setw(12) << right << C21_result[i][2] << "\n";
    }
    //关闭输出文件流
    file_result_C21.close();
    cout << "已输出C21卫星得到的GF和MW组合计算值" << endl;

    ////额外输出一个C07的带上时间的文件用于历元间求差，注意这里用的是连续的，中间没有断过
    //ofstream file_result_C07_time;//创建输出文件流
    ////创建输出文件地址
    //string name_C07_time = "/C07result_time.txt";
    //name_C07_time = outfile + name_C07_time;
    //file_result_C07_time.open(name_C07_time);//自行修改文件路径
    ////开始输出二维数组里的数值
    //for (int i = 0; i < C07num; i++)
    //{
    //    file_result_C07_time.flags(ios::fixed);
    //    file_result_C07_time.precision(6);//设置保留小数位数，取6位
    //    file_result_C07_time << setw(12) << right << C07_result_time[i][0] << setw(12) << right << C07_result_time[i][1] << setw(12) << right << C07_result_time[i][2] 
    //        << setw(12) << right << C07_result_time[i][3] << setw(12) << right << C07_result_time[i][4] << setw(12) << right << C07_result_time[i][5] 
    //        << setw(12) << right << C07_result_time[i][6] << setw(12) << right << C07_result_time[i][7] << setw(12) << right << C07_result_time[i][8] << "\n";
    //}
    ////关闭输出文件流
    //file_result_C07_time.close();
    //cout << "已输出C07卫星得到的GF和MW组合计算值，并具有时间" << endl;


}