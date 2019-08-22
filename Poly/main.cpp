#include "TPoly.h"
#include "TMember.h"
#include <iostream>
#include <locale.h>
#include <stdio.h>
#include <cstdlib>

int main()
{
	setlocale(LC_ALL, "Rus");
	TPoly A;
	TPoly B;

	int degree, coeff, x, i, k;
	printf("СОЗДАНИЕ ПОЛИНОМА\n\n");

	printf("Введите СТЕПЕНЬ полинома: ");
	scanf_s("%d", &degree);
	for (int i = degree; i >= 0; i--)
	{
		printf("Введите КОЭФИЦИЕНТ для члена полинома со степенью %d: ", i);
		scanf_s("%d", &coeff);
		A.add(coeff, i);
	}
	printf("%s\n", A.toString());

	for (int n = 0; n != 11; )
	{
		switch (n)
		{
		case 0:
		{
			printf("\nМЕНЮ\n\n");
			printf("1 - вычислить полином \n");
			printf("2 - дифференцировать полином \n");
			printf("3 - получить наибольшую степень полинома \n");
			printf("4 - получить коэфициент при k-ой степени \n");
			printf("5 - получить i-тый элемент полинома\n");
			printf("6 - сложить два полинома \n");
			printf("7 - вычесть два полинома \n");
			printf("8 - умножить два полинома\n");
			printf("9 - сравнить два полинома \n");
			printf("10 - отчистить текущий полином и ввести заново \n");
			printf("11 - выход \n\n");
			printf("Выберите опцию: ");
			scanf_s("%d", &n);
			printf("\n");
		}
		break;

		case 1: // вычислить полином
		{
			printf("Введите x: ");
			scanf_s("%d", &x);
			printf("f(x) = %s\n", A.toString());

			printf("f(%d) = %d\n",x, A.calc(x));
			//Функция
			n = 0;
		}
		break;

		case 2: // дифференцировать полином
		{
			printf("1 полином: %s\n", A.toString());
			A.differ();
			printf("Результат: %s\n", A.toString());


			n = 0;
		}
		break;

		case 3: // получить наибольшую степень полинома
		{
			//Функция
			printf("1 полином: %s\n", A.toString());

			printf("Наибольшая степень: %d\n",A.getMaxDegree());
			n = 0;
		}
		break;

		case 4: // получить коэффициент при k-ой степени
		{
			printf("Введите степень: ");
			scanf_s("%d", &k);
			TMember tmp = A.getPoly(k);
			//Функция
			printf("1 полином: %s\n", A.toString());

			printf("\n Коэффициент: %d\n",tmp.getFCoeff());
			n = 0;
		}
		break;

		case 5: // получить i-тый элемент
		{
			printf("Введите номер желаемого элемента: ");
			scanf_s("%d", &i);
			TMember tmp = A.getPoly(i-1);
			//Функция
			printf("1 полином: %s\n", A.toString());

			printf("\n Коэффициент: %d",tmp.getFCoeff());
			printf("\n Степень: %d\n",tmp.getFDegree());
			n = 0;
		}
		break;

		case 6: // сложить два полинома
		{
			printf("СОЗДАНИЕ 2 ПОЛИНОМА\n\n");

			printf("Введите степень полинома: ");
			scanf_s("%d", &degree);
			for (int i = degree; i >= 0; i--)
			{
				printf("Введите КОЭФИЦИЕНТ для члена полинома со степенью %d: ", i);
				scanf_s("%d", &coeff);
				B.add(coeff, i);
			}
			printf("1 полином: %s\n", A.toString());
			printf("2 полином: %s\n", B.toString());
			A = A + B;
			//Функция

			printf("Резултат вычислений: %s\n", A.toString());
			B.Clear();
			n = 0;
		}
		break;

		case 7: // вычесть два полинома
		{
			printf("СОЗДАНИЕ 2 ПОЛИНОМА\n\n");

			printf("Введите степень полинома: ");
			scanf_s("%d", &degree);
			for (int i = degree; i >= 0; i--)
			{
				printf("Введите КОЭФИЦИЕНТ для члена полинома со степенью %d: ", i);
				scanf_s("%d", &coeff);
				B.add(coeff, i);
			}
			printf("1 полином: %s\n", A.toString());
			printf("2 полином: %s\n", B.toString());

			//Функция
			A = A - B;

			printf("Резултат вычислений: %s\n", A.toString());
			B.Clear();
			n = 0;
		}
		break;

		case 8: // умножить два полинома
		{
			printf("СОЗДАНИЕ 2 ПОЛИНОМА\n\n");

			printf("Введите степень полинома: ");
			scanf_s("%d", &degree);
			for (int i = degree; i >= 0; i--)			
			{
				printf("Введите КОЭФИЦИЕНТ для члена полинома со степенью %d: ", i);
				scanf_s("%d", &coeff);
				B.add(coeff, i);
			}
			printf("1 полином: %s\n", A.toString());
			printf("2 полином: %s\n", B.toString());

			//Функция
			A = A * B;

			printf("Резултат вычислений: %s\n", A.toString());
			B.Clear();
			n = 0;
		}
		break;

		case 9: // сравнить два полинома
		{
			printf("СОЗДАНИЕ 2 ПОЛИНОМА\n\n");

			printf("Введите степень полинома: ");
			scanf_s("%d", &degree);
			for (int i = 0; i <= degree; i++)
			{
				printf("Введите КОЭФИЦИЕНТ для члена полинома со степенью %d: ", i);
				scanf_s("%d", &coeff);
				B.add(coeff, i);
			}
			printf("1 полином: %s\n", A.toString());
			printf("2 полином: %s\n", B.toString());

			//Функция
			if(A == B)
				printf("Полиномы равны\n");
			else 
				printf("Полиномы не равны\n");

			B.Clear();
			
			n = 0;
		}
		break;


		case 10: //отчистить текущий полином и ввести заново
		{
			A.Clear();
			//Функция
			printf("СОЗДАНИЕ ПОЛИНОМА\n\n");

			printf("Введите степень полинома: ");
			scanf_s("%d", &degree);
			for (int i = 0; degree >= i; degree--)
			{
				printf("Введите КОЭФИЦИЕНТ для члена полинома со степенью %d: ", degree);
				scanf_s("%d", &coeff);
				A.add(coeff, degree);
			}
			printf("%s\n", A.toString());

			n = 0;
		}
		break;
		}
	}
	//system("cls");
	return 0;
}