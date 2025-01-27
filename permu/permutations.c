/*
expected files: *.c *.h
function allowed: puts, malloc, calloc, realloc, free, write

write a program that will print all the permutations of a string given as an argument
solutions must be given in an alphabetical order

we will not try your program with duplicates. example: "abccd"

./permutations a
a

./permutations ab
ab
ba

./permutations abc
abc
acb
bac
bca
cab
cba
*/

#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
	write(1, "\n", 1);
}

void bubble_sort(char *str)
{
	int i, j;
	char temp;
	int len = 0;
	while (str[len])
		len++;

	//abc
	//str[a]
	//str[b]
	//str[c]

	for (i = 0; i < len - 1; i++)
	{
		for (j = 0; j < len - i - 1; j++)
		{
			if (str[j] > str[j + 1])
			{
				temp = str[j];
				str[j] = str[j + 1];
				str[j + 1] = temp;
			}
		}
	}
}

void generate_permutations(char *str, int *used, char *curr, int pos, int len)
{
	if (pos == len)
	{
		ft_putstr(curr);
		return ;
	}

	for (int i = 0; i < len; i++)
	{
		if (!used[i])
		{
			used[i] = 1;
			curr[pos] = str[i];
			generate_permutations(str, used, curr, pos + 1, len);
			used[i] = 0;
		}
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	char *str = argv[1];
	int len = 0;
	while (str[len])
		len++;

	char curr[len + 1];
	int used[len];
	curr[len] = '\0';

	for (int i = 0; i < len; i++)
		used[i] = 0;

	bubble_sort(str);
	generate_permutations(str, used, curr, 0, len);
	return 0;
}