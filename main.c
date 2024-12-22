#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#pragma warning(disable : 4996)
int field[30][20][35], count = 0;


int getInput(int maxValue)
{
	char inputBuffer[100];
	int number = 0;
	while (1) {
		printf("¬ведите число от 0 до %d: ", maxValue);
		if (fgets(inputBuffer, sizeof(inputBuffer), stdin) != NULL)
		{
			inputBuffer[strcspn(inputBuffer, "\n")] = 0;
			int isNumeric = 1;
			for (int i = 0; i < strlen(inputBuffer); i++) 
			{
				if (!isdigit(inputBuffer[i])) 
				{
					isNumeric = 0;
					break;
				}
			}
			if (isNumeric && strlen(inputBuffer) > 0 && strlen(inputBuffer) <= 2)
			{
				sscanf(inputBuffer, "%d", &number);
				if (number >= 0 && number <= maxValue) 
				{
					return number; 
				}
			}
		}
		printf("ќшибка: введите корректное число от 1 до %d.\n", maxValue);
	}
}

int recursion(int cx, int cy, int cz, int tx, int ty, int tz)
{
	if (cx == tx && cy == ty && cz == tz) 
	{
		return 1; 
	}
	int found = 0;
	if (tx > cx) 
	{
		found = recursion(cx + 1, cy, cz, tx, ty, tz);
	}
	else if (tx < cx)
	{
		found = recursion(cx - 1, cy, cz, tx, ty, tz);
	}
	if (found == 0)
	{
		if (ty > cy) 
		{
			found = recursion(cx, cy + 1, cz, tx, ty, tz);
		}
		else if (ty < cy)
		{
			found = recursion(cx, cy - 1, cz, tx, ty, tz);
		}
	}
	if (found == 0) {
		if (tz > cz) {
			found = recursion(cx, cy, cz + 1, tx, ty, tz);
		}
		else if (tz < cz) {
			found = recursion(cx, cy, cz - 1, tx, ty, tz);
		}
	}
	if (found == 1) 
	{
		count++;
	}

	return found;
}

void decide(int a1, int b1, int c1, int a2, int b2, int c2, int x, int y, int z) {
	int p1 = 0, p2 = 0;
	recursion(a1, b1, c1, x, y, z);
	p1 = count;
	count = 0;
	recursion(a2, b2, c2, x, y, z);
	p2 = count;

	if (p1 < p2) {
		field[z][x - 1][y - 1] = p1;
	}
	else if (p2 < p1) {
		field[z][x - 1][y - 1] = p2;
	}
	else {
		field[z][x - 1][y - 1] = p1;
	}
}

void printSections(z, x, y)
{
	for (int i = 0; i < x; i++) 
	{
		for (int j = 0; j < y; j++) 
		{
			printf("%4d", field[z][i][j]);
		}
		printf("\n");
	}
}

int main() {
	int field[30][20][35] = { -1 };
	setlocale(LC_ALL, "RUS");
	int x = 0, y = 0, z = 0, x1 = 0, y1 = 0, z1 = 0, x2 = 0, y2 = 0, z2 = 0;
	printf("¬ведите значени€ точек параллелепипеда: \n");
	printf("X: ");
	x = getInput(20);
	printf("Y: ");
	y = getInput(35);
	printf("Z: ");
	z = getInput(30);
	printf("\n¬ведите координаты первой точки: \n");
	printf("X1: ", x);
	x1 = getInput(x);
	printf("Y1: ", y);
	y1 = getInput(y);
	printf("Z1: ", z);
	z1 = getInput(z);
	printf("\n¬ведите координаты второй точки: \n");
	printf("X2 ", x);
	x2 = getInput(x);
	printf("Y2 ", y);
	y2 = getInput(y);
	printf("Z3 ", z);
	z2 = getInput(z);
	for (int currentlay = 0; currentlay <= z; currentlay++)
	{
		printf("%d) \n", currentlay + 1);
		for (int i = 1; i <= x; i++) 
		{
			for (int j = 1; j <= y; j++)
			{
				count = 0;
				decide(x1, y1, z1, x2, y2, z2, i, j, currentlay);
				count = 0;
			}
		}
		printSections(currentlay, x, y);
		printf("\n");

	}
}