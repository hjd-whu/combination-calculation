#pragma once
#include <string>
using namespace std;
//GPS卫星参数
class GPSdata
{
public:
	//时间参数
	double year = 0;
	double month = 0;
	double day = 0;
	double hour = 0;
	double min = 0;
	double sec = 0;
	//信息参数
	string PRN = "initializationGPS";
	double C1C = 0;
	double C2W = 0;
	double C2X = 0;
	double C5X = 0;
	double D1C = 0;
	double D2W = 0;
	double D2X = 0;
	double D5X = 0;
	double L1C = 0;
	double L2W = 0;
	double L2X = 0;
	double L5X = 0;
	double S1C = 0;
	double S2W = 0;
	double S2X = 0;
	double S5X = 0;
	//组合计算量
	double GF_L = 0;//相位GF组合
	double GF_P = 0;//伪距GF组合
	double MW = 0;//MW组合
};

//北斗卫星参数
class BDSdata
{
public:
	//时间参数
	double year = 0;
	double month = 0;
	double day = 0;
	double hour = 0;
	double min = 0;
	double sec = 0;
	//信息参数
	string PRN = "initializationBDS";
	double C2I = 0;
	double C6I = 0;
	double C7I = 0;
	double D2I = 0;
	double D6I = 0;
	double D7I = 0;
	double L2I = 0;
	double L6I = 0;
	double L7I = 0;
	double S2I = 0;
	double S6I = 0;
	double S7I = 0;
	//组合计算量
	double GF_L = 0;//相位GF组合
	double GF_P = 0;//伪距GF组合
	double MW = 0;//MW组合
};