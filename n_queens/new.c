#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_print_arr(int *arr, int n)
{
	int i = 0;

	while (i < n - 1)
	{
		printf("%d ",arr[i]);
		i++;
	}
	printf("%d",arr[i]);
	printf("\n");
}

int	ft_valid(int *arr, int row, int col)
{
	int	row_it;
	int	col_it;

	col_it = 0;
	while (col_it < col)
	{
		row_it = arr[col_it];
		if (row_it == row)
			return (0);
		if	(col - col_it == row - row_it)
			return (0);
		if	(col - col_it == (-1) * (row - row_it))
			return (0);
		col_it++;
	}
	return (1);
}

void	ft_queens(int *arr, int n, int col)
{
    int row = 0;
    while (row < n)
    {
        arr[col] = row;
        if (ft_valid(arr, row, col))
        {
            if (col == n - 1)
                ft_print_arr(arr, n);
            else
                ft_queens(arr, n, col + 1);
        }
        row++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (0);
    int n = atoi(argv[1]);
    int arr[n];
    ft_queens(arr, n, 0);
    return (0);
}