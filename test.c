#include <stdlib.h>
#include <stdio.h>

int queensareok(int arr[], int q_row, int q_col)
{
	int i = 0;
	while (i < q_col)
	{
		if (arr[i] == q_row)
			return 0;
		if (arr[i] == q_row - (q_col - i))
			return 0;
		if (arr[i] == q_row + (q_col - i))
			return 0;
		i++;
	}
	return (1);

}


void print_sol(int arr[], int n)
{
	int i = 0;
	while (i < n - 1)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("%d", arr[i]);
	printf("\n");
}


void n_queens(int arr[], int n, int col)
{
	int row = 0;
	while (row < n)
	{
		arr[col] = row;
		if (queensareok(arr, row, col))
		{
			if (col == n - 1)
				print_sol(arr, n);
			else
				n_queens(arr, n, col + 1);
		}
		row++;
	}


}

int main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	int n = atoi(av[1]);
	int arr[n];

	n_queens(arr, n, 0);


}