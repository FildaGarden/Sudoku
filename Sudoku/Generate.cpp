#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int mat[9][9];
int n = 9;
int k;
int srn = 3;



bool unUsedInBox(int rowStart, int colStart, int num) {
	for (int i = 0; i < srn; i++) {
		for (int j = 0; j < srn; j++) {
			if (mat[rowStart + i][colStart + j] == num) {
				return false;
			}
		}
	}
	return true;
}

bool unUsedInRow(int i, int num) {
	for (int j = 0; j < 9; j++) {
		if (mat[i][j] == num) {
			return false;
		}
	}
	return true;
}

bool unUsedInCol(int j, int num) {
	for (int i = 0; i < 9; i++) {
		if (mat[i][j] == num) {
			return false;
		}
	}
	return true;
}

bool checkIfSafe(int i, int j, int num) {
	return (unUsedInRow(i, num) && unUsedInCol(j, num) && unUsedInBox(i - i % 3, j - j % 3, num));
}



void fillBox(int row, int col) {
	int num;
	for (int i = 0; i < srn; i++) {

		for (int j = 0; j < srn; j++) {
			do {
				num = (rand() % 9) + 1;
			} while (!unUsedInBox(row, col, num));

			mat[row + i][col + j] = num;
		}
	}
}
void fillDiagonal() {
	for (int i = 0; i < 9; i = i + srn) {
		fillBox(i, i);
	}

}

bool fillRemaining(int i, int j)
{

	if (j >= 9 && i < 9 - 1)
	{
		i = i + 1;
		j = 0;
	}
	if (i >= 9 && j >= 9) {
		return true;
	}

	if (i < 3)
	{
		if (j < 3)
			j = 3;
	}
	else if (i < 9 - 3)
	{
		if (j == (int)(i / 3) * 3) {
			j = j + 3;
		}
	}
	else
	{
		if (j == 9 - 3)
		{
			i = i + 1;
			j = 0;
			if (i >= 9)
				return true;
		}
	}

	for (int num = 1; num <= 9; num++)
	{
		if (checkIfSafe(i, j, num))
		{
			mat[i][j] = num;
			if (fillRemaining(i, j + 1)) {
				return true;
			}

			mat[i][j] = 0;
		}
	}
	return false;
}

void printSudoku() {
	for (int i = 0; i < 9; i++) {
		printf("\n\n");
		for (int j = 0; j < 9; j++) {

			printf("%d", mat[i][j]);
			printf("\t");

		}
	}

}

void removeDigits(int count) {
	while (count != 0) {
		int cellId = (rand() % 81) - 1;
		int i = (cellId / 9);
		int j = (cellId % 9);
		if (j != 0) {
			j = j - 1;
		}
		if (mat[i][j] != 0) {
			count--;
			mat[i][j] = 0;
		}
	}

}

void saveGame(){
	
	FILE* file;
	file = fopen("C:/Sudoku/sudoku.txt","w+");

	
		for (int i = 0; i < 9; i++) {
			fprintf(file, "%d %d %d %d %d %d %d %d %d\n", mat[i][0], mat[i][1], mat[i][2], mat[i][3], mat[i][4], mat[i][5], mat[i][6], mat[i][7], mat[i][8]);
		}
		fclose(file);
}



int fillValues(int count) {

	fillDiagonal();
	fillRemaining(0, 3);
	removeDigits(count);

	return 0;
}




