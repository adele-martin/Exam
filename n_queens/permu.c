 #include <stdio.h>
#include <stdlib.h>


int are_queens_ok(int array[], int row, int col)
{
	int i = 0;
	while (i < col)
	{
	if (array[i] == row)
		return 0;
	if (array[i] == col)
		return (0);
	i++;
	}
	return (1);
}

void print_sol(int array[], int n)
{
	int i = 0;
	while (i < n)
	{
		printf("%d", array[i]);
		if (i < n - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}


void n_queens(int arr[], int n, int col)
{
	int row = 0;
	while (row < n)
	{
	arr[col] = row;
	if (are_queens_ok(arr, row, col))
	{
		if (row == n - 1)
		{
			print_sol(arr, n);
			break;
		}
		else
			n_queens(arr, row, 0);
	}
	row++;
	}
}


int main(int ac, char **av)
{
	int n;
	n = atoi(av[1]);

	int array[n];
	n_queens(array, n, 0);
}