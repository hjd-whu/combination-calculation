#pragma once
//用于声明函数

//函数声明
void readrinex(GPSdata G[5000], BDSdata C[12000], string broadcastfile);
void calGPS(GPSdata G[5000],  string broadcastfile, string outfile);
void calBDS(BDSdata C[12000], string broadcastfile, string outfile);



