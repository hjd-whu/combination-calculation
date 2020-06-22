#include <iostream>
#include <fstream>
#include <string>
#include "parameter.h"
#include "statement.h"
using namespace std;

void readrinex(GPSdata G[5000], BDSdata C[12000], string broadcastfile)
{
	//读取数据
	string fileName = broadcastfile;
	fstream file;
	file.open(fileName);//读入文件

	if (!file)//判断是否找到文件
	{
		cout << "文件地址错误，打开失败！" << endl;
	}

	string buf;//临时存储数据的每一行，不用字符数组，不然后面不好断行
	int realnumber = 0;//实际的文件总行数
	int GPSnum = 0;//GPS数量
	int BDSnum = 0;//北斗数量
	//用来暂时存放时间变量
	double year = 0;
	double month = 0;
	double day = 0;
	double hour = 0;
	double min = 0;
	double sec = 0;

	//处理文件头程序
	while (1)//直接进循环，开始读文件
	{
		getline(file, buf);//每一次取一行的内容
		realnumber++;//实际的总行数加一
		//判断文件头是否读完，当读完文件头后跳出循环
		if (buf.find("END OF HEADER") == 60)
			break;
	}

	//进入读文件体程序
	for (realnumber; realnumber < 127068;)
	{
		getline(file, buf);//每一次取一行的内容
		realnumber++;//实际的总行数加一
		//先判断开头，当遇见特定符号进入一个大循环
		string firstletter= buf.substr(0, 1);//取出开头的第一个字母
		string initial_judge;//取出开头的前三个字母
		initial_judge = buf.substr(0, 3);
		if (firstletter == ">")//时间行则输入时间
		{
			year = stod(buf.substr(2, 4));
			month = stod(buf.substr(7, 2));
			day = stod(buf.substr(10, 2));
			hour = stod(buf.substr(13, 2));
			min = stod(buf.substr(16, 2));
			sec = stod(buf.substr(19, 10));
			continue;
		}
		if (initial_judge == "G01" | initial_judge == "G02" | initial_judge == "G03" | initial_judge == "G04" | initial_judge == "G05")//GPS行则输入GPS数据
		{

			//先输入时间
			G[GPSnum].year = year;
			G[GPSnum].month = month;
			G[GPSnum].day = day;
			G[GPSnum].hour = hour;
			G[GPSnum].min = min;
			G[GPSnum].sec = sec;

			//输入后面的内容
			G[GPSnum].PRN = buf.substr(0, 3);

			if (buf.substr(5, 12) == "            ")
				;//全是空格就什么也不做
			else
				G[GPSnum].C1C = stod(buf.substr(5, 12));

			if (buf.substr(21, 12) == "            ")
				;//全是空格就什么也不做
			else
				G[GPSnum].C2W = stod(buf.substr(21, 12));

			if (buf.substr(37, 12) == "            ")
				;//全是空格就什么也不做
			else
				G[GPSnum].C2X = stod(buf.substr(37, 12));

			if (buf.substr(53, 12) == "            ")
				;//全是空格就什么也不做
			else
				G[GPSnum].C5X = stod(buf.substr(53, 12));

			if (buf.substr(72, 9) == "         ")
				;//全是空格就什么也不做
			else
				G[GPSnum].D1C = stod(buf.substr(72, 9));

			if (buf.substr(88, 9) == "         ")
				;//全是空格就什么也不做
			else
				G[GPSnum].D2W = stod(buf.substr(88, 9));

			if (buf.substr(104, 9) == "         ")
				;//全是空格就什么也不做
			else
				G[GPSnum].D2X = stod(buf.substr(104, 9));

			if (buf.substr(120, 9) == "         ")
				;//全是空格就什么也不做
			else
				G[GPSnum].D5X = stod(buf.substr(120, 9));

			if (buf.substr(132, 13) == "             ")
				;//全是空格就什么也不做
			else
				G[GPSnum].L1C = stod(buf.substr(132, 13));

			if (buf.substr(148, 13) == "             ")
				;//全是空格就什么也不做
			else
				G[GPSnum].L2W = stod(buf.substr(148, 13));

			if (buf.substr(164, 13) == "             ")
				;//全是空格就什么也不做
			else
				G[GPSnum].L2X = stod(buf.substr(164, 13));

			if (buf.substr(180, 13) == "             ")
				;//全是空格就什么也不做
			else
				G[GPSnum].L5X = stod(buf.substr(180, 13));

			if (buf.substr(203, 6) == "             ")
				;//全是空格就什么也不做
			else
				G[GPSnum].S1C = stod(buf.substr(203, 6));

			if (buf.length() > 219)
			{
				if (buf.substr(219, 6) == "      ")
					;//全是空格就什么也不做
				else
					G[GPSnum].S2W = stod(buf.substr(219, 6));

				if (buf.length() > 235)
				{
					if (buf.substr(235, 6) == "      ")
						;//全是空格就什么也不做
					else
						G[GPSnum].S2X = stod(buf.substr(235, 6));

					if (buf.length() > 251)
					{
						if (buf.substr(251, 6) == "      ")
							;//全是空格就什么也不做
						else
							G[GPSnum].S5X = stod(buf.substr(251, 6));
					}
				}
			}
			//cout << GPSnum << " " << G[GPSnum].PRN << endl;
			//cout << G[GPSnum].year << "." << G[GPSnum].month << "." << G[GPSnum].day << "  " << G[GPSnum].hour << "." << G[GPSnum].min << "." << G[GPSnum].sec << endl;
			GPSnum++;
			continue;
		}

		//读入北斗的数据
		if (initial_judge == "C01" | initial_judge == "C02" | initial_judge == "C06" | initial_judge == "C07" | initial_judge == "C20" | initial_judge == "C21")//BDS行则输入BDS数据
		{

			//先输入时间
			C[BDSnum].year = year;
			C[BDSnum].month = month;
			C[BDSnum].day = day;
			C[BDSnum].hour = hour;
			C[BDSnum].min = min;
			C[BDSnum].sec = sec;

			//再输入后面的数据
			C[BDSnum].PRN = buf.substr(0, 3);

			if (buf.substr(5, 12) == "            ")
				;//全是空格就什么也不做
			else
				C[BDSnum].C2I = stod(buf.substr(5, 12));

			if (buf.substr(21, 12) == "            ")
				;//全是空格就什么也不做
			else
				C[BDSnum].C6I = stod(buf.substr(21, 12));

			if (buf.substr(37, 12) == "            ")
				;//全是空格就什么也不做
			else
				C[BDSnum].C7I = stod(buf.substr(37, 12));

			if (buf.substr(53, 12) == "            ")
				;//全是空格就什么也不做
			else
				C[BDSnum].D2I = stod(buf.substr(53, 12));

			if (buf.substr(72, 9) == "         ")
				;//全是空格就什么也不做
			else
				C[BDSnum].D6I = stod(buf.substr(72, 9));

			if (buf.substr(88, 9) == "         ")
				;//全是空格就什么也不做
			else
				C[BDSnum].D7I = stod(buf.substr(88, 9));

			if (buf.substr(100, 13) == "             ")
				;//全是空格就什么也不做
			else
				C[BDSnum].L2I = stod(buf.substr(100, 13));

			if (buf.substr(116, 13) == "             ")
				;//全是空格就什么也不做
			else
				C[BDSnum].L6I = stod(buf.substr(116, 13));

			if (buf.substr(132, 13) == "             ")
				;//全是空格就什么也不做
			else
				C[BDSnum].L7I = stod(buf.substr(132, 13));

			if (buf.substr(155, 6) == "      ")
				;//全是空格就什么也不做
			else
				C[BDSnum].S2I = stod(buf.substr(155, 6));

			if (buf.length() > 171)
			{
				if (buf.substr(171, 6) == "      ")
					;//全是空格就什么也不做
				else
					C[BDSnum].S6I = stod(buf.substr(171, 6));


				if (buf.length() > 186)
				{
					if (buf.substr(186, 6) == "      ")
						;//全是空格就什么也不做
					else
						C[BDSnum].S7I = stod(buf.substr(187, 6));
				}
			}
			//cout << BDSnum << " " << C[BDSnum].PRN << endl;
			//cout << C[BDSnum].year << "." << C[BDSnum].month << "." << C[BDSnum].day << "  " << C[BDSnum].hour << "." << C[BDSnum].min << "." << C[BDSnum].sec << endl;
			BDSnum++;
			continue;
		}
	}
}