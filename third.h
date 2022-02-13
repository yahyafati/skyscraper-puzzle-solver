/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahaji <yahaji@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:53:53 by yahaji            #+#    #+#             */
/*   Updated: 2022/02/13 10:22:07 by yahaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

/* If the string has more than one character, 
	or it has just one character but that character isn't a number
	then it is a wrong input and it will return -1.
	other wise it will return the integer value of the single digit.

	Conditions:
		1. first character has to be a number between 1 and 4
		2. next character must be nothing or space
	if conditions are not satisfied return -1 to show error, 
	otherwise return the int value of the character '0' => 0, '1' => 1...
*/
int	char_to_int_safe(char *str)
{
	if (str[0] < '1' || str[0] > '4')
		return (-1);
	if (str[1] && str[1] != ' ')
		return (-1);
	return (str[0] - '0');
}

/*
	Check if the current number combination satisfies the conditions
	given by the user.
*/
int	check_constraints(int given[4][4], int *view_count, int i)
{
	return ((given[0][i] != 0 && view_count[0] != given[0][i]) ||
				(given[1][i] != 0 && view_count[1] != given[1][i]) ||
				(given[2][i] != 0 && view_count[2] != given[2][i]) ||
				(given[3][i] != 0 && view_count[3] != given[3][i]));
}

/*
prints the solution of the array line by line.
it takes result and prints it one row at a time.
*/
void	print_solution(int result[4][4], int i, int j, char c)
{
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			c = '0' + result[i][j];
			write(1, &c, 1);
			if (j != 3)
				write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
