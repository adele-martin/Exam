 #include <stdio.h>
#include <stdlib.h>
#include "strings.h"

void swap(char *first, char *second)
{
	char temp = *first;
	*first = *second;
	*second = temp;
}


void bubble_sort(char *s, int len)
{
	int i = 0;
	int j;
	while (i < (len - 1))
	{
		j = 0;
		while (j < (len - i - 1))
		{
			if (j < j + 1)
				swap(&s[j], &s[j + 1]);
			j++;
		}
		i++;
	}

}

void generate_perm(char *s, int len, int ind)
{
	if (ind == len - 1)
	{
		puts(s);
		return;
	}
	int i;
	i = ind;
	while (i < len)
	{
		swap(&s[ind], &s[i]);
		generate_perm(s, len, ind + 1);
		swap(&s[ind], &s[i]);
		i++;
	}


}

int main(int ac, char **av)
{
	if (ac != 2)
        return 1;

    int s_len = strlen(av[1]);
    if (s_len == 0)
        return 1;

    char *working_string = malloc(s_len + 1);
    if (!working_string)
        return 1;

    for (int i = 0; i < s_len; i++)
        working_string[i] = av[1][i];
    working_string[s_len] = '\0';

	generate_perm(working_string, s_len, 0);

}