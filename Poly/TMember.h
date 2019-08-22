#pragma once
#include <math.h>
class TMember
{
private:
	int FCoeff, FDegree;
	void numberToString(int n, char* res); // ������� ����� � ������
	char buf[64];
	int Abs(int a); // ������ ����� �
public:
	TMember(int c, int d);
	TMember();
	~TMember();
	int getFCoeff(); // �������� �����������
	int getFDegree(); // �������� �������
	void setFCoeff(int c); // �������� ����.
	void setFDegree(int d); // �������� �������
	void difference(); // �������������������
	int calc(int x); // ��������� �������
	char* toString(); // ������� �������� � ������
	bool operator<(TMember &A);
	TMember operator+(TMember A);
};

