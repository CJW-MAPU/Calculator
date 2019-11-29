#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <Windows.h>

#define MAXSIZE 1000
#define RANK 3

int PositionX = 6;
int PositionY = 3;
//test
int NumCnt = 0;
int OprCnt = 0;

void gotoxy(int, int);
void hideCursor();
char *InPutFunction();
double *NUMBERPOP(char *);
char *OPERATORPOP(char *);
double RESULT(double *, char *);
void Interface();

int main()
{
	char ch;
	char *Input; // 문자열을 입력받을 배열
	double *Number; // 입력한 숫자가 들어갈 배열
	char *Operator; // 입력한 연산자가 들어갈 배열	

	hideCursor();

	while (1)
	{
		Interface();
		Input = InPutFunction();

		Operator = OPERATORPOP(Input);
		Number = NUMBERPOP(Input);

		Interface();
		gotoxy(PositionX, PositionY);
		printf("result : %.2lf\n", RESULT(Number, Operator));

		free(Input);
		free(Number);
		free(Operator);
		if (ch = _getch())
			continue;
	}
	return 0;
}
// gotoxy
void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
// hideCursor	
void hideCursor()
{
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}
// 입력
char *InPutFunction()
{
	char *Input = malloc(MAXSIZE);
	int i = 0;

	gotoxy(PositionX, PositionY);
	while (Input[i] = _getche())
	{
		i++;
		if (Input[i - 1] == '\n')
		{
			Input[i - 1] = '\0';
			break;
		}
		if (Input[i - 1] == '\b')
		{
			i = i - 2;
		}
	}

	return Input;
}
// 숫자 뽑기
double *NUMBERPOP(char *s)
{
	double *arr = malloc(MAXSIZE);

	char *delimiter = "+-*/%^";
	char *ptoken;
	char *next_token;

	int cnt = 0;

	ptoken = strtok_s(s, delimiter, &next_token);
	while (ptoken != NULL)
	{
		NumCnt++;
		arr[cnt++] = (double)atoi(ptoken);

		ptoken = strtok_s(NULL, delimiter, &next_token);
	}

	return arr;
}
// 연산자 뽑기
char *OPERATORPOP(char *s)
{
	char *ary = malloc(MAXSIZE);

	int i = 0;
	int cnt = 0;

	while (s[i++] != '\0')
	{
		if (s[i - 1] == '+')
		{
			ary[cnt++] = '+';
			OprCnt++;
		}
		if (s[i - 1] == '-')
		{
			ary[cnt++] = '-';
			OprCnt++;
		}
		if (s[i - 1] == '*')
		{
			ary[cnt++] = '*';
			OprCnt++;
		}
		if (s[i - 1] == '/')
		{
			ary[cnt++] = '/';
			OprCnt++;
		}
		if (s[i - 1] == '%')
		{
			ary[cnt++] = '%';
			OprCnt++;
		}
		if (s[i - 1] == '^')
		{
			ary[cnt++] = '^';
			OprCnt++;
		}
	}

	return ary;
}
// 계산
double RESULT(double *number, char *operator)
{
	int index = 0; // 첨자
	int cnt = 0;
	int backup = 0;

	int reduction = 0; // 감소용

	for (int i = 0; i < RANK; i++)
	{
		cnt = index;
		if (i == 0)
		{
			while (cnt < OprCnt)
			{
				if (operator[cnt] == '^')
				{
					backup++;
					number[cnt + 1] = pow(number[cnt], number[cnt + 1]);
					reduction = cnt;
					while (reduction > index)
					{
						number[reduction] = number[reduction - 1];
						operator[reduction] = operator[reduction - 1];
						reduction--;
					}
				}
				cnt++;
			}
			index = backup;
			reduction = 0;
		}
		if (i == 1)
		{
			while (cnt < OprCnt)
			{
				if (operator[cnt] == '*')
				{
					backup++;
					number[cnt + 1] = number[cnt] * number[cnt + 1];
					reduction = cnt;
					while (reduction > index)
					{
						number[reduction] = number[reduction - 1];
						operator[reduction] = operator[reduction - 1];
						reduction--;
					}
				}
				if (operator[cnt] == '/')
				{
					backup++;
					number[cnt + 1] = number[cnt] / number[cnt + 1];
					reduction = cnt;
					while (reduction > index)
					{
						number[reduction] = number[reduction - 1];
						operator[reduction] = operator[reduction - 1];
						reduction--;
					}
				}
				if (operator[cnt] == '%')
				{
					backup++;
					number[cnt + 1] = (int)number[cnt] % (int)number[cnt + 1];
					reduction = cnt;
					while (reduction > index)
					{
						number[reduction] = number[reduction - 1];
						operator[reduction] = operator[reduction - 1];
						reduction--;
					}
				}
				cnt++;
			}
			index = backup;
			reduction = 0;
		}
		if (i == 2)
		{
			while (cnt < OprCnt)
			{
				if (operator[cnt] == '+')
				{
					number[cnt + 1] = number[cnt] + number[cnt + 1];
					cnt++;
				}
				if (operator[cnt] == '-')
				{
					number[cnt + 1] = number[cnt] - number[cnt + 1];
					cnt++;
				}
			}
		}
	}

	return number[NumCnt - 1];
}
// 인터페이스
void Interface()
{
	gotoxy(0, 0);
	puts("■■■■■■■■■■■■■■■■■■■■■■■■■■");
	puts("■□□□□□□□□□□□□□□□□□□□□□□□□■");
	puts("■□                                            □■");
	puts("■□                                            □■");
	puts("■□                                            □■");
	puts("■□□□□□□□□□□□□□□□□□□□□□□□□■");
	puts("■■■■■■■■■■■■■■■■■■■■■■■■■■");
	printf("수식 입력, ctrl + enter 시 NULL 입력\n");
}