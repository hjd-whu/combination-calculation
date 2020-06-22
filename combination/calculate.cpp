//���ڼ������ֵ��д���ļ�
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "parameter.h"
#include "statement.h"
using namespace std;

//����GPS��GF��MW���ֵ����
void calGPS(GPSdata G[5000],  string broadcastfile,string outfile)
{
    //���볣��
    double c = 299792458;//����
    double L1 = 1575.42 * pow(10, 6);//GPS��L1��λ
    double lambda1 = c / L1;//GPS��L1�Ĳ���
    double L2 = 1227.6 * pow(10, 6);//GPS��L2��λ
    double lambda2 = c / L2;//GPS��L2�Ĳ���
    double B1I = 1561.098 * pow(10, 6);//������L1��λ
    double lambdaB1I = c / B1I;//������L1�Ĳ���
    double B3I = 1268.52 * pow(10, 6);//������L3��λ
    double lambdaB3I = c / B3I;//������L3�Ĳ���

    //����GPS���ǵ��������ͼ�����λ
    double G01_result[1000][3];//����������
    int G01num = 0;//���ڼ���
    double G02_result[1000][3];//����������
    int G02num = 0;//���ڼ���
    double G03_result[1000][3];//����������
    int G03num = 0;//���ڼ���
    double G04_result[1000][3];//����������
    int G04num = 0;//���ڼ���
    double G05_result[1000][3];//����������
    int G05num = 0;//���ڼ���
    double G03_result_time[1000][9];//����������
    //����GPS����
    for (int i = 0; i < 5000; i++)
    {
        if ((G[i].L1C == 0) | (G[i].L2W == 0) | (G[i].C1C == 0) | (G[i].C2W == 0))//��ʹ��ȱʧ���ݵ�ʱ��
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

    //���G01�ļ�
    ofstream file_result_G01;//��������ļ���
    //��������ļ���ַ
    string name_G01 = "/G01result.txt";
    name_G01 = outfile + name_G01;
    file_result_G01.open(name_G01);//�����޸��ļ�·��
    //��ʼ�����ά���������ֵ
    for (int i = 0; i < G01num; i++)
    {
        file_result_G01.flags(ios::fixed);
        file_result_G01.precision(6);//���ñ���С��λ����ȡ6λ
        file_result_G01 << setw(12) << right << G01_result[i][0] << setw(12) << right << G01_result[i][1] << setw(12) << right << G01_result[i][2] << "\n";
    }
    //�ر�����ļ���
    file_result_G01.close();
    cout << "�����G01���ǵõ���GF��MW��ϼ���ֵ" << endl;

    //���G02�ļ�
    ofstream file_result_G02;//��������ļ���
    //��������ļ���ַ
    string name_G02 = "/G02result.txt";
    name_G02 = outfile + name_G02;
    file_result_G02.open(name_G02);//�����޸��ļ�·��
    //��ʼ�����ά���������ֵ
    for (int i = 0; i < G02num; i++)
    {
        file_result_G02.flags(ios::fixed);
        file_result_G02.precision(6);//���ñ���С��λ����ȡ6λ
        file_result_G02 << setw(12) << right << G02_result[i][0] << setw(12) << right << G02_result[i][1] << setw(12) << right << G02_result[i][2] << "\n";
    }
    //�ر�����ļ���
    file_result_G02.close();
    cout << "�����G02���ǵõ���GF��MW��ϼ���ֵ" << endl;

    //���G03�ļ�
    ofstream file_result_G03;//��������ļ���
    //��������ļ���ַ
    string name_G03 = "/G03result.txt";
    name_G03 = outfile + name_G03;
    file_result_G03.open(name_G03);//�����޸��ļ�·��
    //��ʼ�����ά���������ֵ
    for (int i = 0; i < G03num; i++)
    {
        file_result_G03.flags(ios::fixed);
        file_result_G03.precision(6);//���ñ���С��λ����ȡ6λ
        file_result_G03 << setw(12) << right << G03_result[i][0] << setw(12) << right << G03_result[i][1] << setw(12) << right << G03_result[i][2] << "\n";
    }
    //�ر�����ļ���
    file_result_G03.close();
    cout << "�����G03���ǵõ���GF��MW��ϼ���ֵ" << endl;

    //���G04�ļ�
    ofstream file_result_G04;//��������ļ���
    //��������ļ���ַ
    string name_G04 = "/G04result.txt";
    name_G04 = outfile + name_G04;
    file_result_G04.open(name_G04);//�����޸��ļ�·��
    //��ʼ�����ά���������ֵ
    for (int i = 0; i < G04num; i++)
    {
        file_result_G04.flags(ios::fixed);
        file_result_G04.precision(6);//���ñ���С��λ����ȡ6λ
        file_result_G04 << setw(12) << right << G04_result[i][0] << setw(12) << right << G04_result[i][1] << setw(12) << right << G04_result[i][2] << "\n";
    }
    //�ر�����ļ���
    file_result_G04.close();
    cout << "�����G04���ǵõ���GF��MW��ϼ���ֵ" << endl;

    //���G05�ļ�
    ofstream file_result_G05;//��������ļ���
    //��������ļ���ַ
    string name_G05 = "/G05result.txt";
    name_G05 = outfile + name_G05;
    file_result_G05.open(name_G05);//�����޸��ļ�·��
    //��ʼ�����ά���������ֵ
    for (int i = 0; i < G05num; i++)
    {
        file_result_G05.flags(ios::fixed);
        file_result_G05.precision(6);//���ñ���С��λ����ȡ6λ
        file_result_G05 << setw(12) << right << G05_result[i][0] << setw(12) << right << G05_result[i][1] << setw(12) << right << G05_result[i][2] << "\n";
    }
    //�ر�����ļ���
    file_result_G05.close();
    cout << "�����G05���ǵõ���GF��MW��ϼ���ֵ" << endl;

    ////�������һ��G03�Ĵ���ʱ����ļ�������Ԫ����ע�������õ��������ģ��м�û�жϹ�
    //ofstream file_result_G03_time;//��������ļ���
    ////��������ļ���ַ
    //string name_G03_time = "/G03result_time.txt";
    //name_G03_time = outfile + name_G03_time;
    //file_result_G03_time.open(name_G03_time);//�����޸��ļ�·��
    ////��ʼ�����ά���������ֵ
    //for (int i = 0; i < G03num; i++)
    //{
    //    file_result_G03_time.flags(ios::fixed);
    //    file_result_G03_time.precision(6);//���ñ���С��λ����ȡ6λ
    //    file_result_G03_time << setw(12) << right << G03_result_time[i][0] << setw(12) << right << G03_result_time[i][1] << setw(12) << right << G03_result_time[i][2]
    //        << setw(12) << right << G03_result_time[i][3] << setw(12) << right << G03_result_time[i][4] << setw(12) << right << G03_result_time[i][5]
    //        << setw(12) << right << G03_result_time[i][6] << setw(12) << right << G03_result_time[i][7] << setw(12) << right << G03_result_time[i][8] << "\n";
    //}
    ////�ر�����ļ���
    //file_result_G03_time.close();
    //cout << "�����G03���ǵõ���GF��MW��ϼ���ֵ��������ʱ��" << endl;
}


//���㱱����GF��MW���ֵ����
void calBDS(BDSdata C[12000], string broadcastfile, string outfile)
{
    //���볣��
    double c = 299792458;//����
    double L1 = 1575.42 * pow(10, 6);//GPS��L1Ƶ��
    double lambda1 = c / L1;//GPS��L1�Ĳ���
    double L2 = 1227.6 * pow(10, 6);//GPS��L2Ƶ��
    double lambda2 = c / L2;//GPS��L2�Ĳ���
    double B1I = 1561.098 * pow(10, 6);//������L1Ƶ��
    double lambdaB1I = c / B1I;//������L1�Ĳ���
    double B3I = 1268.52 * pow(10, 6);//������L3Ƶ��
    double lambdaB3I = c / B3I;//������L3�Ĳ���

    //�����������ǵ��������ͼ�����λ
    double C01_result[3000][3];//����������
    int C01num = 0;//���ڼ���
    double C02_result[3000][3];//����������
    int C02num = 0;//���ڼ���
    double C06_result[3000][3];//����������
    int C06num = 0;//���ڼ���
    double C07_result[3000][3];//����������
    int C07num = 0;//���ڼ���
    double C20_result[3000][3];//����������
    int C20num = 0;//���ڼ���
    double C21_result[3000][3];//����������
    int C21num = 0;//���ڼ���
    double C07_result_time[3000][9];//����������
    //���㱱������
    for (int i = 0; i < 12000; i++)
    {
        if ((C[i].L2I == 0) | (C[i].L6I == 0) | (C[i].C2I == 0) | (C[i].C6I == 0))//��ʹ��ȱʧ���ݵ�ʱ��
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
    //���C01�ļ�
    ofstream file_result_C01;//��������ļ���
    //��������ļ���ַ
    string name_C01 = "/C01result.txt";
    name_C01 = outfile + name_C01;
    file_result_C01.open(name_C01);//�����޸��ļ�·��
    //��ʼ�����ά���������ֵ
    for (int i = 0; i < C01num; i++)
    {
        file_result_C01.flags(ios::fixed);
        file_result_C01.precision(6);//���ñ���С��λ����ȡ6λ
        file_result_C01 << setw(12) << right << C01_result[i][0] << setw(12) << right << C01_result[i][1] << setw(12) << right << C01_result[i][2] << "\n";
    }
    //�ر�����ļ���
    file_result_C01.close();
    cout << "�����C01���ǵõ���GF��MW��ϼ���ֵ" << endl;

    //���C02�ļ�
    ofstream file_result_C02;//��������ļ���
    //��������ļ���ַ
    string name_C02 = "/C02result.txt";
    name_C02 = outfile + name_C02;
    file_result_C02.open(name_C02);//�����޸��ļ�·��
    //��ʼ�����ά���������ֵ
    for (int i = 0; i < C02num; i++)
    {
        file_result_C02.flags(ios::fixed);
        file_result_C02.precision(6);//���ñ���С��λ����ȡ6λ
        file_result_C02 << setw(12) << right << C02_result[i][0] << setw(12) << right << C02_result[i][1] << setw(12) << right << C02_result[i][2] << "\n";
    }
    //�ر�����ļ���
    file_result_C02.close();
    cout << "�����C02���ǵõ���GF��MW��ϼ���ֵ" << endl;

    //���C06�ļ�
    ofstream file_result_C06;//��������ļ���
    //��������ļ���ַ
    string name_C06 = "/C06result.txt";
    name_C06 = outfile + name_C06;
    file_result_C06.open(name_C06);//�����޸��ļ�·��
    //��ʼ�����ά���������ֵ
    for (int i = 0; i < C06num; i++)
    {
        file_result_C06.flags(ios::fixed);
        file_result_C06.precision(6);//���ñ���С��λ����ȡ6λ
        file_result_C06 << setw(12) << right << C06_result[i][0] << setw(12) << right << C06_result[i][1] << setw(12) << right << C06_result[i][2] << "\n";
    }
    //�ر�����ļ���
    file_result_C06.close();
    cout << "�����C06���ǵõ���GF��MW��ϼ���ֵ" << endl;

    //���C07�ļ�
    ofstream file_result_C07;//��������ļ���
    //��������ļ���ַ
    string name_C07 = "/C07result.txt";
    name_C07 = outfile + name_C07;
    file_result_C07.open(name_C07);//�����޸��ļ�·��
    //��ʼ�����ά���������ֵ
    for (int i = 0; i < C07num; i++)
    {
        file_result_C07.flags(ios::fixed);
        file_result_C07.precision(6);//���ñ���С��λ����ȡ6λ
        file_result_C07 << setw(12) << right << C07_result[i][0] << setw(12) << right << C07_result[i][1] << setw(12) << right << C07_result[i][2] << "\n";
    }
    //�ر�����ļ���
    file_result_C07.close();
    cout << "�����C07���ǵõ���GF��MW��ϼ���ֵ" << endl;

    //���C20�ļ�
    ofstream file_result_C20;//��������ļ���
    //��������ļ���ַ
    string name_C20 = "/C20result.txt";
    name_C20 = outfile + name_C20;
    file_result_C20.open(name_C20);//�����޸��ļ�·��
    //��ʼ�����ά���������ֵ
    for (int i = 0; i < C20num; i++)
    {
        file_result_C20.flags(ios::fixed);
        file_result_C20.precision(6);//���ñ���С��λ����ȡ6λ
        file_result_C20 << setw(12) << right << C20_result[i][0] << setw(12) << right << C20_result[i][1] << setw(12) << right << C20_result[i][2] << "\n";
    }
    //�ر�����ļ���
    file_result_C20.close();
    cout << "�����C20���ǵõ���GF��MW��ϼ���ֵ" << endl;

    //���C21�ļ�
    ofstream file_result_C21;//��������ļ���
    //��������ļ���ַ
    string name_C21 = "/C21result.txt";
    name_C21 = outfile + name_C21;
    file_result_C21.open(name_C21);//�����޸��ļ�·��
    //��ʼ�����ά���������ֵ
    for (int i = 0; i < C21num; i++)
    {
        file_result_C21.flags(ios::fixed);
        file_result_C21.precision(6);//���ñ���С��λ����ȡ6λ
        file_result_C21 << setw(12) << right << C21_result[i][0] << setw(12) << right << C21_result[i][1] << setw(12) << right << C21_result[i][2] << "\n";
    }
    //�ر�����ļ���
    file_result_C21.close();
    cout << "�����C21���ǵõ���GF��MW��ϼ���ֵ" << endl;

    ////�������һ��C07�Ĵ���ʱ����ļ�������Ԫ����ע�������õ��������ģ��м�û�жϹ�
    //ofstream file_result_C07_time;//��������ļ���
    ////��������ļ���ַ
    //string name_C07_time = "/C07result_time.txt";
    //name_C07_time = outfile + name_C07_time;
    //file_result_C07_time.open(name_C07_time);//�����޸��ļ�·��
    ////��ʼ�����ά���������ֵ
    //for (int i = 0; i < C07num; i++)
    //{
    //    file_result_C07_time.flags(ios::fixed);
    //    file_result_C07_time.precision(6);//���ñ���С��λ����ȡ6λ
    //    file_result_C07_time << setw(12) << right << C07_result_time[i][0] << setw(12) << right << C07_result_time[i][1] << setw(12) << right << C07_result_time[i][2] 
    //        << setw(12) << right << C07_result_time[i][3] << setw(12) << right << C07_result_time[i][4] << setw(12) << right << C07_result_time[i][5] 
    //        << setw(12) << right << C07_result_time[i][6] << setw(12) << right << C07_result_time[i][7] << setw(12) << right << C07_result_time[i][8] << "\n";
    //}
    ////�ر�����ļ���
    //file_result_C07_time.close();
    //cout << "�����C07���ǵõ���GF��MW��ϼ���ֵ��������ʱ��" << endl;


}