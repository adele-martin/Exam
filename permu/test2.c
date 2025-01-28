#include <stdio.h>
#include <stdlib.h>

int ft_strlen(char *s)
{
    int len = 0;
    while (*s)
    {
        s++;
        len++;
    }
    return (len);
}

void swap_char(char *first, char *second)
{
    char temp = *first;
    *first = *second;
    *second = temp;
}

void sort_string(char *s, int s_len)
{
	int i = 0;
	int j = 0;

	while (i < (s_len - 1))
	{
		j = 0;
		while (j < (s_len - i - 1))
		{
			if (s[j] > s[j + 1])
				swap_char(&s[j], &s[j+1]);
			j++;
		}
		i++;
	}
}


// Recursive function to generate permutations
void generate_permutations(char *s, int ind, int s_len)
{
    if (ind == s_len - 1)
    {
        puts(s); // Print the current permutation
        return;
    }

    int i = ind; // Iterator starts from the current index
    while (i < s_len)
    {
        swap_char(&s[ind], &s[i]); // Swap to generate a new combination
        generate_permutations(s, ind + 1, s_len); // Recur for the next index
        swap_char(&s[ind], &s[i]); // Backtrack to restore original order
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;

    int s_len = ft_strlen(argv[1]);
    if (s_len == 0)
        return 1;

    char *working_string = malloc(s_len + 1);
    if (!working_string)
        return 1;

    for (int i = 0; i < s_len; i++)
        working_string[i] = argv[1][i];
    working_string[s_len] = '\0';


    // Sort the string once to ensure permutations are generated in lexicographical order
	sort_string(working_string, s_len);
    generate_permutations(working_string, 0, s_len);
    free(working_string);
    return 0;
}