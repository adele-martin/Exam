#include <stdio.h>
#include <unistd.h>

#include <limits.h>

size_t ft_strlen(char *s)
{
	int len = 0;
	while(*s)
	{
		len++;
		s++;
	}
	return (len);
}
int is_balanced(char *s)
{
	int i = 0;
	int count = 0;

	while(s[i])
	{
		if (s[i] == '(')
			count++;
		if (s[i] == ')')
			count--;
		if (count < 0) // If there are more closing brackets than opening ones
			return 0;
		i++;
	}
	if (count == 0)
		return (1);
	else
		return (0);
}

void find_min(char *s, size_t ind, size_t s_len, int *min, int current_op)
{
	char tmp;
	if (ind == s_len)
		return;
	size_t i = ind;
	while(i < s_len)
	{
		tmp = s[i];
		s[i] = ' ';
		current_op++;
		if (!is_balanced(s))
			find_min(s, i + 1, s_len, min, current_op);
		else if (is_balanced(s) && current_op < *min)
			*min = current_op;
		s[i] = tmp;
		current_op--;
		i++;
	}
}

void find_sol(char *s, size_t ind, size_t s_len, int min, int current_op)
{
	char tmp;
	//base case is reached
	if (ind == s_len)
		return;
	if (current_op > min)
		return;
	size_t i = ind;
	while (i < s_len)
	{
		tmp = s[i];
		s[i] = ' ';
		current_op++;
		if (!is_balanced(s))
			find_sol(s, i + 1, s_len, min, current_op);
		else if (is_balanced(s) == 1 && current_op == min)
			puts(s);
		s[i] = tmp;
		current_op--;
		i++;
	}
}

void backtrack(char *s, int ind, int s_len, int min, int current_op, int *found_solution) {
    if (ind == s_len)
        return;
    int i = ind;
    while (i < s_len)
	{
        char tmp = s[i];
        s[i] = ' '; // Temporarily remove character
        current_op++;
        if (!is_balanced(s))
            backtrack(s, i + 1, s_len, min, current_op, found_solution);
        else if (is_balanced(s) && current_op <= min)
		{
            if (current_op < min)
			{
                min = current_op;
                *found_solution = 1;
            }
            puts(s);
        }
        s[i] = tmp; // Backtrack
        current_op--;
        i++;
    }
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 0;
	size_t s_len = ft_strlen(argv[1]);
	//If the string is empty, return
	if (s_len == 0)
	{
		puts("");
		return 0;
	}
	if (is_balanced(argv[1]) == 1)
	{
		puts(argv[1]);
		return 0;
	}
	//At this point the string is unbalanced!
	int min = INT_MAX;
	find_min(argv[1], 0, s_len, &min, 0);
	find_sol(argv[1], 0, s_len, min, 0);
	return 0;
}