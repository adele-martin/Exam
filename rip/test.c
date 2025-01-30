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
    return (count == 0);
}

void find_min_removals(char *s, int ind, int s_len, int *min, int current_op)
{
    if (ind == s_len)
        return;

    for (int i = ind; i < s_len; i++)
    {
        char tmp = s[i];
        s[i] = ' ';
        current_op++;

        if (!is_balanced(s))
            find_min_removals(s, i + 1, s_len, min, current_op);
        else if (is_balanced(s) && current_op < *min)
            *min = current_op;

        s[i] = tmp;
        current_op--;
    }
}

void find_solutions(char *s, int ind, int s_len, int min, int current_op)
{
    if (ind == s_len || current_op > min)
        return;

    for (int i = ind; i < s_len; i++)
    {
        char tmp = s[i];
        s[i] = ' ';
        current_op++;

        if (!is_balanced(s))
            find_solutions(s, i + 1, s_len, min, current_op);
        else if (is_balanced(s) && current_op == min)
            puts(s);

        s[i] = tmp;
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
    find_min_removals(argv[1], 0, s_len, &min, 0);
    find_solutions(argv[1], 0, s_len, min, 0);

    return 0;
}
