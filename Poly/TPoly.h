#pragma once
#include <vector>
#include <deque>
#include "TMember.h"
using namespace std;

typedef class TPoly: deque<TMember>
{
private:
	//vector<TMember> Tmembers;
	//TPoly TMembers;
	char buf[1024];
	void cleanZero();
public:
	TPoly();
	~TPoly();

	void addFromString(char* str);
	void add(int c, int d);
	void differ();
	void Clear();
	void sort();

	int intFromString(char* str);
	int getMaxDegree();
	int calc(int x);

	char* toString();

	TMember getPoly(int index);

	TPoly operator +(TPoly A);
	TPoly operator -(TPoly A);
	TPoly operator *(TPoly A);
	//TPoly operator =(TPoly A);
	bool operator ==(TPoly A);
} *PTPoly;

