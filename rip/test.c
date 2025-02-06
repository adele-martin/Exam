#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

//if count is less than 0 you have got to return 0 because it won't be balanced
int is_balanced(char *s)
{
    int i = 0, count = 0;
    while (s[i])
    {
        if (s[i] == '(')
            count++;
        else if (s[i] == ')')
            count--;
        if (count < 0)
            return 0;
        i++;
    }
    if (count == 0)
		return (1);
	else
		return (0);
}

void process_brackets(char *s, int ind, int s_len, int *min, int current_op, int print_mode)
{
    if (ind == s_len)
        return;

    for (int i = ind; i < s_len; i++)
    {
        char tmp = s[i];
        s[i] = ' ';  // Simulate removal
        current_op++;

        if (!is_balanced(s))
        {
            process_brackets(s, i + 1, s_len, min, current_op, print_mode);
        }
        else
        {
            if (!print_mode)  // Finding minimum removals
            {
                if (current_op < *min)
                    *min = current_op;
            }
            else if (current_op == *min)  // Printing solutions when at minimum removals
            {
                puts(s);
            }
        }

        s[i] = tmp;  // Backtrack
        current_op--;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 0;

    int s_len = ft_strlen(argv[1]);
    if (s_len == 0)
    {
        puts("");
        return 0;
    }
    if (is_balanced(argv[1]))
    {
        puts(argv[1]);
        return 0;
    }

    int min = INT_MAX;
    process_brackets(argv[1], 0, s_len, &min, 0, 0);
    process_brackets(argv[1], 0, s_len, &min, 0, 1);
//Don't forget the current operator!!
    return 0;
}
