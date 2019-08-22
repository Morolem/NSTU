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
	printf("�������� ��������\n\n");

	printf("������� ������� ��������: ");
	scanf_s("%d", &degree);
	for (int i = degree; i >= 0; i--)
	{
		printf("������� ���������� ��� ����� �������� �� �������� %d: ", i);
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
			printf("\n����\n\n");
			printf("1 - ��������� ������� \n");
			printf("2 - ���������������� ������� \n");
			printf("3 - �������� ���������� ������� �������� \n");
			printf("4 - �������� ���������� ��� k-�� ������� \n");
			printf("5 - �������� i-��� ������� ��������\n");
			printf("6 - ������� ��� �������� \n");
			printf("7 - ������� ��� �������� \n");
			printf("8 - �������� ��� ��������\n");
			printf("9 - �������� ��� �������� \n");
			printf("10 - ��������� ������� ������� � ������ ������ \n");
			printf("11 - ����� \n\n");
			printf("�������� �����: ");
			scanf_s("%d", &n);
			printf("\n");
		}
		break;

		case 1: // ��������� �������
		{
			printf("������� x: ");
			scanf_s("%d", &x);
			printf("f(x) = %s\n", A.toString());

			printf("f(%d) = %d\n",x, A.calc(x));
			//�������
			n = 0;
		}
		break;

		case 2: // ���������������� �������
		{
			printf("1 �������: %s\n", A.toString());
			A.differ();
			printf("���������: %s\n", A.toString());


			n = 0;
		}
		break;

		case 3: // �������� ���������� ������� ��������
		{
			//�������
			printf("1 �������: %s\n", A.toString());

			printf("���������� �������: %d\n",A.getMaxDegree());
			n = 0;
		}
		break;

		case 4: // �������� ����������� ��� k-�� �������
		{
			printf("������� �������: ");
			scanf_s("%d", &k);
			TMember tmp = A.getPoly(k);
			//�������
			printf("1 �������: %s\n", A.toString());

			printf("\n �����������: %d\n",tmp.getFCoeff());
			n = 0;
		}
		break;

		case 5: // �������� i-��� �������
		{
			printf("������� ����� ��������� ��������: ");
			scanf_s("%d", &i);
			TMember tmp = A.getPoly(i-1);
			//�������
			printf("1 �������: %s\n", A.toString());

			printf("\n �����������: %d",tmp.getFCoeff());
			printf("\n �������: %d\n",tmp.getFDegree());
			n = 0;
		}
		break;

		case 6: // ������� ��� ��������
		{
			printf("�������� 2 ��������\n\n");

			printf("������� ������� ��������: ");
			scanf_s("%d", &degree);
			for (int i = degree; i >= 0; i--)
			{
				printf("������� ���������� ��� ����� �������� �� �������� %d: ", i);
				scanf_s("%d", &coeff);
				B.add(coeff, i);
			}
			printf("1 �������: %s\n", A.toString());
			printf("2 �������: %s\n", B.toString());
			A = A + B;
			//�������

			printf("�������� ����������: %s\n", A.toString());
			B.Clear();
			n = 0;
		}
		break;

		case 7: // ������� ��� ��������
		{
			printf("�������� 2 ��������\n\n");

			printf("������� ������� ��������: ");
			scanf_s("%d", &degree);
			for (int i = degree; i >= 0; i--)
			{
				printf("������� ���������� ��� ����� �������� �� �������� %d: ", i);
				scanf_s("%d", &coeff);
				B.add(coeff, i);
			}
			printf("1 �������: %s\n", A.toString());
			printf("2 �������: %s\n", B.toString());

			//�������
			A = A - B;

			printf("�������� ����������: %s\n", A.toString());
			B.Clear();
			n = 0;
		}
		break;

		case 8: // �������� ��� ��������
		{
			printf("�������� 2 ��������\n\n");

			printf("������� ������� ��������: ");
			scanf_s("%d", &degree);
			for (int i = degree; i >= 0; i--)			
			{
				printf("������� ���������� ��� ����� �������� �� �������� %d: ", i);
				scanf_s("%d", &coeff);
				B.add(coeff, i);
			}
			printf("1 �������: %s\n", A.toString());
			printf("2 �������: %s\n", B.toString());

			//�������
			A = A * B;

			printf("�������� ����������: %s\n", A.toString());
			B.Clear();
			n = 0;
		}
		break;

		case 9: // �������� ��� ��������
		{
			printf("�������� 2 ��������\n\n");

			printf("������� ������� ��������: ");
			scanf_s("%d", &degree);
			for (int i = 0; i <= degree; i++)
			{
				printf("������� ���������� ��� ����� �������� �� �������� %d: ", i);
				scanf_s("%d", &coeff);
				B.add(coeff, i);
			}
			printf("1 �������: %s\n", A.toString());
			printf("2 �������: %s\n", B.toString());

			//�������
			if(A == B)
				printf("�������� �����\n");
			else 
				printf("�������� �� �����\n");

			B.Clear();
			
			n = 0;
		}
		break;


		case 10: //��������� ������� ������� � ������ ������
		{
			A.Clear();
			//�������
			printf("�������� ��������\n\n");

			printf("������� ������� ��������: ");
			scanf_s("%d", &degree);
			for (int i = 0; degree >= i; degree--)
			{
				printf("������� ���������� ��� ����� �������� �� �������� %d: ", degree);
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