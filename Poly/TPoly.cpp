#include "TPoly.h"
#include <map>
#include <algorithm>
#include <string.h>

int TPoly::intFromString(char* str)
{
	int result = 0, // результат		
		sign = 1, // знак
		i = 0; // текущий символ

	if (str[i] == '-') { sign = -1; i++; }
	else if (str[i] == '+') { sign = 1; i++; }
	//else throw 99;

	for (i; i < (int)strlen(str); i++)
	{
		result *= 10;
		result += (str[i] - 0x30); //  перевод символа в число
	}
	
	return 	result*sign;
}

void TPoly::addFromString(char* s)
{
	const char* sy = "-0123456789^x+";
	int length_sy = 14, l_s = strlen(s);

	for (int i = 0; i < l_s; i++)
	{
		bool ch = false;
		for (int j = 0; j < length_sy; j++)
		{
			if (s[i] == sy[j])
			{
				ch = true;
				break;
			}
		}
		if (!ch) return;
	}

	char buf[15];
	int i = 0;
	for (i = 0; i < l_s; i++)
	{
		int k = 0;
		while (s[i] != 'x' && i < l_s)
		{ 
			buf[k] = s[i];
			i++;
			k++; 
		}
		buf[k] = '\0';
		int coeff = intFromString(buf);
		i+=2;
		k = 0;
		while (s[i] != '+' && s[i] != '-' && i < l_s) 
		{
			buf[k] = s[i]; 
			i++;
			k++; 
		}
		buf[k] = '\0';
		int degree = intFromString(buf);
		TMember tm(coeff, degree);		
		TPoly::iterator it;

		for (it = this->begin(); it != this->end(); it++)
				if (it->getFDegree() == degree)
					this->add(it->getFCoeff() + coeff, it->getFDegree());
				else
					this->add(it->getFCoeff(), it->getFDegree());

		i--;
	}
}

void TPoly::cleanZero()
{
	TPoly result;
	TPoly::iterator it = this->begin();

	for (it = this->begin(); it != this->end(); it++)
	{
		if (it->getFCoeff() != 0)
		{
			TMember tm(it->getFCoeff(), it->getFDegree());
			result.push_back(tm);
		}
	}
	this->clear();
	*this = result;
}

char* TPoly::toString()
{
	int k = 0;

	TPoly::iterator it = this->begin();
	for (it; it < this->end(); it++)
	{
			char *s_temp = it->toString();
			int length = strlen(s_temp);
			if (s_temp[0] != '-' && it != this->begin())
			{
				buf[k] = '+';
				++k;
			}
			s_temp = it->toString();
			for (int j = 0; j < length; j++, k++)
			{
				buf[k] = s_temp[j];
			}
	}
	buf[k] = '\0';
	return this->buf;
}

void TPoly::add(int coef, int degr)
{
	if (coef != 0) //
	{
		bool flag = false; // изначально считаем, что в коллекции нет полином со степенью d
		TMember tm(coef, degr);
		TPoly::iterator it = this->begin();
		for (it; it < this->end(); it++)
			if (it->getFDegree() == degr) // если в коллекции есть полином той же степени
			{
				flag = true;
				break;
			}

		if (flag)
		{
			auto tmp = it->getFCoeff();
			it->setFCoeff(tmp + coef); // суммируем коеффициенты
		}
		else
			this->push_back(tm); // иначе записываем полином в конец
	}
}

int TPoly::getMaxDegree()
{
	int max = 0;
	TPoly::iterator it = this->begin();
	for (it; it < this->end(); it++)
		if(it->getFDegree() > max)
			max = it->getFDegree();
	return max;
}

void TPoly::Clear()
{
	this->clear();
}

void TPoly::differ()
{
	TPoly::iterator it = this->begin();
	for (it; it < this->end(); it++) {
		it->difference();
		TMember tm(it->getFCoeff(), it->getFDegree());
	}
	cleanZero();
}

int TPoly::calc(int x)
{
	int s = 0;
	TPoly::iterator it = this->begin();
	for (it; it < this->end(); it++)
	{
		s += it->calc(x);
	}
	return s;
}

TMember TPoly::getPoly(int index)
{
	TMember t(0, 0);
	int i = 0;
	TPoly::iterator it = this->begin();
	for (it; it < this->end(); i++, it++)
	{
		if (i == index)
		{
			return *it;
		}
	}
	return t;
}

TPoly TPoly::operator + (TPoly A)
{
	TPoly result;
	TPoly::iterator it;

	if (this->size() >= A.size())
	{
		for (it = this->begin(); it != this->end(); it++)
			result.add(it->getFCoeff(), it->getFDegree());

		for (it = A.begin(); it != A.end(); it++)
				result.add(it->getFCoeff(), it->getFDegree());
	}
	else
	{
		for (it = A.begin(); it != A.end(); it++)
			result.add(it->getFCoeff(), it->getFDegree());

		for (it = this->begin(); it != this->end(); it++)
				result.add(it->getFCoeff(), it->getFDegree());

	}
	result.cleanZero();
	result.sort();
	return result;
}

TPoly TPoly::operator-(TPoly A)
{
	TPoly result;
	TPoly::iterator it;

	if (this->size() >= A.size())
	{
		for (it = this->begin(); it != this->end(); it++)
			result.add(it->getFCoeff(), it->getFDegree());

		for (it = A.begin(); it != A.end(); it++)
			result.add(-it->getFCoeff(), it->getFDegree());
	}
	else
	{
		for (it = A.begin(); it != A.end(); it++)
			result.add(it->getFCoeff(), it->getFDegree());

		for (it = this->begin(); it != this->end(); it++)
			result.add(-it->getFCoeff(), it->getFDegree());

	}
	result.cleanZero(); 
	result.sort();
	return result;
}

TPoly TPoly::operator*(TPoly A)
{
	TPoly *result = new TPoly();
	TPoly::iterator it_A;
	TPoly::iterator it;

	for (it = this->begin(); it != this->end(); it++)
		for (it_A = A.begin(); it_A != A.end(); it_A++)

				result->add((it->getFCoeff() * it_A->getFCoeff()), (it->getFDegree() + it_A->getFDegree()));


	result->cleanZero();
	result->sort();
	return *result;
}


bool TPoly::operator==(TPoly A)
{
	TPoly::iterator it_A;
	TPoly::iterator it;
	if (this->size() != A.size())
		return false;
	else
	{
		auto element_count = A.size();
		it_A = A.begin();
		for (it_A; it_A < A.end(); it_A++)
		{
			it = this->begin();
			for (it; it < this->end(); it++)
				if (it->getFDegree() == it_A->getFDegree()
					&&
					it->getFCoeff() == it_A->getFCoeff()) element_count--;
		}
		if (element_count == 0) return true;

	}
	return false;
}

void TPoly::sort()
{
	TPoly::iterator it1 = this->begin();
	for (it1; it1 < this->end()-1; it1++)
	{
		TPoly::iterator it2 = it1 + 1;
		for (it2; it2 < this->end(); it2++)
			if (it1->getFDegree() < it2->getFDegree())
				iter_swap(it1, it2);
	}

}

TPoly::TPoly()
{	
}

TPoly::~TPoly()
{
}
