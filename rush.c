/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahaji <yahaji@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 09:07:29 by yahaji            #+#    #+#             */
/*   Updated: 2022/02/13 12:55:11 by yahaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "second.h"

struct s_valid_check {
	int	col_vals[5];
	int	view_count[4];
	int	maxes[4];
	int	items[4];
};

/**
* argv -> a string containaing the list of number given by the user.
* views[][] -> a 2 dimensional array where the users input is copied into.
*			-> it is a 4 x 4 table (4 rows, 4 cols)
*			-> each row - contains the view from one side
*				row[0] -> view from top
*				row[1] -> view from bottom
*				row[2] -> view from left
*				row[3] -> view from right
*/
int	initialize_array(int views[4][4], char *argv)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			views[i][j] = char_to_int_safe(argv + len);
			if (views[i][j] == -1)
				return (-1);
			j++;
			len += 2;
		}
		i++;
	}
	return (1);
}

/*
Checks for two things:
	1. are the columns valid
		are all numbers in column different
		1
		2
		3
		2
		Not Valid because 2 is repeated.
		3
		4
		1
		2
		Valid -> because all of them are different
	2. are the views valid from every perspective
		do they satisfy the input given by the user?
If at least one of them is false, then it is not valid, otherwise it is valid.
*/ 
int	is_valid(int res[4][4], int given[4][4], int i, int j)
{
	struct s_valid_check	checker;

	zeroize(checker.col_vals, 5);
	while (i < 4)
	{
		zeroize(checker.view_count, 4);
		zeroize(checker.maxes, 4);
		j = 0;
		while (j < 4)
		{
			set_items(res, checker.items, i, j);
			if (checker.items[0]
				&& is_col_taken(checker.col_vals[checker.items[0]], i))
				return (0);
			checker.col_vals[checker.items[0]] += (1 << i);
			set_values(checker.view_count, checker.maxes, checker.items);
			j++;
		}
		if (check_constraints(given, checker.view_count, i))
			return (0);
		i++;
	}
	return (1);
}

/*
	Check the solve_stuff() function first.
	
	Continuation of solve_stuff() function, because of norminette.

	Because of norminette, this changes only the first two numbers in the list
	{
		{1, 2, 3, 4}, this is managed by solve_stuff() function
		{2, 3, 4, 1}, this is also managed by solve_stuff() function
		{3, 4, 1, 2}, this is managed by this function
		{4, 1, 2, 3}, this is also managed by this function
	}
*/
int	last_two_values(int res[4][4], int given[4][4],
int *indexes, const int *values)
{	
	indexes[2] = 0;
	while (indexes[2] < 24)
	{
		to_int_array(res[2], values[indexes[2]]);
		indexes[3] = 0;
		while (indexes[3] < 24)
		{
			to_int_array(res[3], values[indexes[3]]);
			if (is_valid(res, given, 0, 0))
				return (1);
			indexes[3]++;
		}
		indexes[2]++;
	}
	return (0);
}

/*
	Solves the problem.
	
	It will try all possible combinations, and if it finds one that works,
	then it will return 1 - meaning it has succefully solved it.

	If it goes through everything, and couldn't find any combination that works,
	then it will return 0 - meaning there is no possible solution for it.

	Because of norminette, this changes only the first two numbers in the list
	{
		{1, 2, 3, 4},
		{2, 3, 4, 1},
		{3, 4, 1, 2}, this is managed by last_two_values() function
		{4, 1, 2, 3}, this is also managed by last_two_values() function
	}
*/
int	solve_stuff(int res[4][4], int given[4][4])
{
	const int	values[] = {1234, 1243, 1324, 1342, 1423, 1432, 2134,
		2143, 2314, 2341, 2413, 2431, 3124, 3142, 3214,
		3241, 3412, 3421, 4123, 4132, 4213, 4231, 4312, 4321};
	int			indexes[4];

	zeroize(indexes, 4);
	while (indexes[0] < 24)
	{
		to_int_array(res[0], values[indexes[0]]);
		indexes[1] = 0;
		while (indexes[1] < 24)
		{
			to_int_array(res[1], values[indexes[1]]);
			if (last_two_values(res, given, indexes, values))
				return (1);
			indexes[1]++;
		}
		indexes[0]++;
	}
	return (0);
}

/**
	This is the main function.
		argc - number of arguments given by the user in the terminal
		argv - a list containing these arguments
		
		Ex. ./a.out Hello There
				argc = 3
				argv = {"./a.out", "Hello", "There"}
			./a.out "Everything in a quotation mark is considered as one"
				argc = 2
				argv = {"./a.out", "Everything in a quotation mark is considered as one"}
	
	Program is executed like => ./a.out "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
	Therefore if the number of argument is greater than 2, it is an error.
	
	If the user input is also not valid:
		1. Contains anythign but number
		2. Does not contain enough number
	then, it is an error.

	int result[4][4] - a 2-Dimensional array (Table), containing the final result of the solution.
	int view[4][4] - the input the user gives
		view[0] -> views from top. eg. {1, 2, 2, 3}
		view[1] -> views from bottom
		view[2] -> views from left
		view[3] -> views from right
	
	we zeroize everything in result[][] first => we make all of its values 0.
	
	we try to solve the problem using solve_stuff(result, views)
		if solve_stuff(result, views) returns 0, there was no solution, and it's an error
		but if it returns 1 => it has successfully solved it.
	we then print_solution to the terminal
*/
int	main(int argc, char *argv[])
{
	int			views[4][4];
	int			result[4][4];
	int			i;

	if (argc != 2 || initialize_array(views, argv[1]) == -1)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	i = 0;
	while (i < 4)
		zeroize(result[i++], 4);
	if (solve_stuff(result, views) == 0)
	{
		write(1, "Error\n", 14);
		return (0);
	}
	print_solution(result, 0, 0, '0');
}
