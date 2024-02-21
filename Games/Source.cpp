#include<iostream>
#include"Header.h"
#include<iomanip>
#define LENGTH_MAX 100
using namespace std;

int length = 2;

void Bien_tren();
void Bien_duoi();
void Bien_trai();
void Bien_phai();

void khoi_tao_ran(int[], int[]);
void ve_ran(int[], int[]);
void xoa_duoi(int[], int[]);
void them(int[], int);
void xoa(int[], int);
void xu_li_ran(int[], int[], int, int, int&, int&);

bool kt_cham_tuong(int[], int[]);
bool kt_cham_duoi(int[], int[]);
bool GameOver(int[], int[]);

void tao_qua(int&, int&, int[], int[]);
bool kt_qua_bi_de(int[], int[], int, int);

bool kt_ran_an_qua(int, int, int&, int&);

int main()
{
	
	ShowCur(0);
	int X[LENGTH_MAX], Y[LENGTH_MAX];
	int check = 2;
	int x = 50;
	int y = 13;
	bool gameOver = false;
	

	// --- vẽ biên
	Bien_tren();
	Bien_duoi();
	Bien_trai();
	Bien_phai();

	// --- tạo con rắn
	khoi_tao_ran(X, Y);
	ve_ran(X, Y);

	// --- tạo quả  
	srand(time(NULL));
	int x_qua = 0, y_qua = 0;
	tao_qua(x_qua, y_qua, X, Y);

	while(gameOver == false)
	{
		xoa_duoi(X, Y);
		/*	Check hướng: 0: di xuong
						 1: di len   
						 2: qua phai
						 3: qua trai */	

		// điều khiển rắn:
		if (_kbhit())
		{
			char kitu = _getch();
			if (kitu == 'w' && check != 0)
			{
				check = 1;
			}
			else if (kitu == 'a' && check != 2)
			{
				check = 3;
			}
			else if (kitu == 's' && check != 1)
			{
				check = 0;
			}
			else if (kitu == 'd' && check != 3)
			{
				check = 2;
			}
		}

		if (check == 0)
		{
			y++;
		}
		else if (check == 1)
		{
			y--;
		}
		else if (check == 2)
		{
			x++;
		}
		else if (check == 3)
		{
			x--;
		}

		xu_li_ran(X, Y, x, y, x_qua, y_qua);
		gameOver = GameOver(X, Y);
		Sleep(100);
	}
	_getch();
	return 0;
}

//--------------- Vẽ tường----------------------//
void Bien_tren()
{
	int x = 10; int y = 1;
	while (x <= 100)
	{
		gotoXY(x, y);
		cout << "+";
		x++;
	}
}
void Bien_duoi()
{
	int x = 10; int y = 29;
	while (x <= 100)
	{
		gotoXY(x, y);
		cout << "+";
		x++;
	}
}
void Bien_trai()
{
	int x = 10; int y = 1;
	while (y<=28)
	{
		gotoXY(x, y);
		cout << "+";
		y++;
	}
}
void Bien_phai()
{
	int x = 100; int y = 1;
	while (y <= 28)
	{
		gotoXY(x, y);
		cout << "+";
		y++;
	}
}

//-------------- Tạo rắn ----------------------//
void khoi_tao_ran(int X[], int Y[])
{
	int x = 50;
	int y = 13;
	
	for (int i = 0; i < length; i++)
	{
		X[i] = x;
		Y[i] = y;
		x--;
	}
}
void ve_ran(int X[], int Y[])
{
	for (int i = 0; i < length; i++)
	{
		gotoXY(X[i], Y[i]);
		if (i == 0)
			cout << "0";
		else
			cout << "o";
	}
}
void xoa_duoi(int X[], int Y[])
{
	for (int i = 0; i < length; i++)
	{
		gotoXY(X[i], Y[i]);
		cout << " ";
	}
}
void them(int a[], int x)
{
	for (int i = length; i > 0; i--)
	{
		a[i] = a[i - 1];
	}
	a[0] = x;
	length++;
}
void xoa(int a[], int x)
{
	for (int i = x; i < length; i++)
	{
		a[i] = a[i + 1];
	}
	length--;
}
void xu_li_ran(int X[], int Y[], int x, int y, int& x_qua, int& y_qua)
{
	them(X, x);
	them(Y, y);

	if (kt_ran_an_qua(X[0], Y[0], x_qua, y_qua) == false)
	{
		xoa(X, length - 1);
		xoa(Y, length - 1);
	}
	else
	{
		tao_qua(x_qua, y_qua, X, Y);
		length--;
	}

	ve_ran(X, Y);
}

//--------------- Game Over ------------------//
bool kt_cham_tuong(int X[], int Y[])
{
	if (X[0] == 10 || X[0] == 100)
		return true;
	else if (Y[0] == 1 || Y[0] == 29)
		return true;
	return false;
}
bool kt_cham_duoi(int X[], int Y[])
{
	for (int i = 1; i < length; i++)
		if (X[0] == X[i] && Y[0] == Y[i])
			return true;
	return false;
}
bool GameOver(int X[], int Y[])
{
	if (kt_cham_tuong(X, Y) == true || kt_cham_duoi(X, Y) == true)
		return true;
	return false;
}

//-------------- Tạo quả --------------------// 
void tao_qua(int& x_qua, int& y_qua, int X[], int Y[])
{
	do
	{
		// 11 <= x_qua <= 99
		x_qua = rand() % (99 - 11 + 1) + 11;
		// 2 <= y_qua <= 28
		y_qua = rand() % (28 - 2 + 1) + 2;
	} while (kt_qua_bi_de(X, Y, x_qua, y_qua) == true);

	gotoXY(x_qua, y_qua);
	cout << "&";
}
bool kt_qua_bi_de(int X[], int Y[], int x, int y)
{
	for (int i = 0; i < length; i++)
	{
		if (x == X[i] && y == Y[i])
			return true;
	}
	return false;
}

//-------------- Xử lí rắn ăn quả ----------//
bool kt_ran_an_qua(int X, int Y, int& x_qua, int& y_qua)
{
	if (X == x_qua && Y == y_qua)
	{
		return true;
	}
	return false;
}