#include <iostream>
#include <fstream>
#include <string>
#include "parameter.h"
#include "statement.h"
using namespace std;

void readrinex(GPSdata G[5000], BDSdata C[12000], string broadcastfile)
{
	//��ȡ����
	string fileName = broadcastfile;
	fstream file;
	file.open(fileName);//�����ļ�

	if (!file)//�ж��Ƿ��ҵ��ļ�
	{
		cout << "�ļ���ַ���󣬴�ʧ�ܣ�" << endl;
	}

	string buf;//��ʱ�洢���ݵ�ÿһ�У������ַ����飬��Ȼ���治�ö���
	int realnumber = 0;//ʵ�ʵ��ļ�������
	int GPSnum = 0;//GPS����
	int BDSnum = 0;//��������
	//������ʱ���ʱ�����
	double year = 0;
	double month = 0;
	double day = 0;
	double hour = 0;
	double min = 0;
	double sec = 0;

	//�����ļ�ͷ����
	while (1)//ֱ�ӽ�ѭ������ʼ���ļ�
	{
		getline(file, buf);//ÿһ��ȡһ�е�����
		realnumber++;//ʵ�ʵ���������һ
		//�ж��ļ�ͷ�Ƿ���꣬�������ļ�ͷ������ѭ��
		if (buf.find("END OF HEADER") == 60)
			break;
	}

	//������ļ������
	for (realnumber; realnumber < 127068;)
	{
		getline(file, buf);//ÿһ��ȡһ�е�����
		realnumber++;//ʵ�ʵ���������һ
		//���жϿ�ͷ���������ض����Ž���һ����ѭ��
		string firstletter= buf.substr(0, 1);//ȡ����ͷ�ĵ�һ����ĸ
		string initial_judge;//ȡ����ͷ��ǰ������ĸ
		initial_judge = buf.substr(0, 3);
		if (firstletter == ">")//ʱ����������ʱ��
		{
			year = stod(buf.substr(2, 4));
			month = stod(buf.substr(7, 2));
			day = stod(buf.substr(10, 2));
			hour = stod(buf.substr(13, 2));
			min = stod(buf.substr(16, 2));
			sec = stod(buf.substr(19, 10));
			continue;
		}
		if (initial_judge == "G01" | initial_judge == "G02" | initial_judge == "G03" | initial_judge == "G04" | initial_judge == "G05")//GPS��������GPS����
		{

			//������ʱ��
			G[GPSnum].year = year;
			G[GPSnum].month = month;
			G[GPSnum].day = day;
			G[GPSnum].hour = hour;
			G[GPSnum].min = min;
			G[GPSnum].sec = sec;

			//������������
			G[GPSnum].PRN = buf.substr(0, 3);

			if (buf.substr(5, 12) == "            ")
				;//ȫ�ǿո��ʲôҲ����
			else
				G[GPSnum].C1C = stod(buf.substr(5, 12));

			if (buf.substr(21, 12) == "            ")
				;//ȫ�ǿո��ʲôҲ����
			else
				G[GPSnum].C2W = stod(buf.substr(21, 12));

			if (buf.substr(37, 12) == "            ")
				;//ȫ�ǿո��ʲôҲ����
			else
				G[GPSnum].C2X = stod(buf.substr(37, 12));

			if (buf.substr(53, 12) == "            ")
				;//ȫ�ǿո��ʲôҲ����
			else
				G[GPSnum].C5X = stod(buf.substr(53, 12));

			if (buf.substr(72, 9) == "         ")
				;//ȫ�ǿո��ʲôҲ����
			else
				G[GPSnum].D1C = stod(buf.substr(72, 9));

			if (buf.substr(88, 9) == "         ")
				;//ȫ�ǿո��ʲôҲ����
			else
				G[GPSnum].D2W = stod(buf.substr(88, 9));

			if (buf.substr(104, 9) == "         ")
				;//ȫ�ǿո��ʲôҲ����
			else
				G[GPSnum].D2X = stod(buf.substr(104, 9));

			if (buf.substr(120, 9) == "         ")
				;//ȫ�ǿո��ʲôҲ����
			else
				G[GPSnum].D5X = stod(buf.substr(120, 9));

			if (buf.substr(132, 13) == "             ")
				;//ȫ�ǿո��ʲôҲ����
			else
				G[GPSnum].L1C = stod(buf.substr(132, 13));

			if (buf.substr(148, 13) == "             ")
				;//ȫ�ǿո��ʲôҲ����
			else
				G[GPSnum].L2W = stod(buf.substr(148, 13));

			if (buf.substr(164, 13) == "             ")
				;//ȫ�ǿո��ʲôҲ����
			else
				G[GPSnum].L2X = stod(buf.substr(164, 13));

			if (buf.substr(180, 13) == "             ")
				;//ȫ�ǿո��ʲôҲ����
			else
				G[GPSnum].L5X = stod(buf.substr(180, 13));

			if (buf.substr(203, 6) == "             ")
				;//ȫ�ǿո��ʲôҲ����
			else
				G[GPSnum].S1C = stod(buf.substr(203, 6));

			if (buf.length() > 219)
			{
				if (buf.substr(219, 6) == "      ")
					;//ȫ�ǿո��ʲôҲ����
				else
					G[GPSnum].S2W = stod(buf.substr(219, 6));

				if (buf.length() > 235)
				{
					if (buf.substr(235, 6) == "      ")
						;//ȫ�ǿո��ʲôҲ����
					else
						G[GPSnum].S2X = stod(buf.substr(235, 6));

					if (buf.length() > 251)
					{
						if (buf.substr(251, 6) == "      ")
							;//ȫ�ǿո��ʲôҲ����
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

		//���뱱��������
		if (initial_judge == "C01" | initial_judge == "C02" | initial_judge == "C06" | initial_judge == "C07" | initial_judge == "C20" | initial_judge == "C21")//BDS��������BDS����
		{

			//������ʱ��
			C[BDSnum].year = year;
			C[BDSnum].month = month;
			C[BDSnum].day = day;
			C[BDSnum].hour = hour;
			C[BDSnum].min = min;
			C[BDSnum].sec = sec;

			//��������������
			C[BDSnum].PRN = buf.substr(0, 3);

			if (buf.substr(5, 12) == "            ")
				;//ȫ�ǿո��ʲôҲ����
			else
				C[BDSnum].C2I = stod(buf.substr(5, 12));

			if (buf.substr(21, 12) == "            ")
				;//ȫ�ǿո��ʲôҲ����
			else
				C[BDSnum].C6I = stod(buf.substr(21, 12));

			if (buf.substr(37, 12) == "            ")
				;//ȫ�ǿո��ʲôҲ����
			else
				C[BDSnum].C7I = stod(buf.substr(37, 12));

			if (buf.substr(53, 12) == "            ")
				;//ȫ�ǿո��ʲôҲ����
			else
				C[BDSnum].D2I = stod(buf.substr(53, 12));

			if (buf.substr(72, 9) == "         ")
				;//ȫ�ǿո��ʲôҲ����
			else
				C[BDSnum].D6I = stod(buf.substr(72, 9));

			if (buf.substr(88, 9) == "         ")
				;//ȫ�ǿո��ʲôҲ����
			else
				C[BDSnum].D7I = stod(buf.substr(88, 9));

			if (buf.substr(100, 13) == "             ")
				;//ȫ�ǿո��ʲôҲ����
			else
				C[BDSnum].L2I = stod(buf.substr(100, 13));

			if (buf.substr(116, 13) == "             ")
				;//ȫ�ǿո��ʲôҲ����
			else
				C[BDSnum].L6I = stod(buf.substr(116, 13));

			if (buf.substr(132, 13) == "             ")
				;//ȫ�ǿո��ʲôҲ����
			else
				C[BDSnum].L7I = stod(buf.substr(132, 13));

			if (buf.substr(155, 6) == "      ")
				;//ȫ�ǿո��ʲôҲ����
			else
				C[BDSnum].S2I = stod(buf.substr(155, 6));

			if (buf.length() > 171)
			{
				if (buf.substr(171, 6) == "      ")
					;//ȫ�ǿո��ʲôҲ����
				else
					C[BDSnum].S6I = stod(buf.substr(171, 6));


				if (buf.length() > 186)
				{
					if (buf.substr(186, 6) == "      ")
						;//ȫ�ǿո��ʲôҲ����
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