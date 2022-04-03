/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahaji <yahaji@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 19:36:57 by yahaji            #+#    #+#             */
/*   Updated: 2022/02/13 10:31:52 by yahaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "third.h"

/*
* Don't underestimate this function!
* arguments:
    1. int n => the number containing the current status of the column
    2. int col_index => index of column to check.
* How is it stored?
    Initially n = 0 => 0000 (in binary form)

    Example:
        when only 0th column is taken then n = 1000 (binary form) = 8
        when only 1st column is taken then n = 0100 (binary form) = 4
        when only 2nd column is taken then n = 0010 (binary form) = 2
        when only 3rd column is taken then n = 0001 (binary form) = 1

        When 1st and 3rd column is taken n = 0101 (binary form) = 5
        When 1st, 2nd and 3rd column is taken n = 0111 (binary form) = 7
        ...
* So if the bit at index of col is 1, then that column is already taken, else that column is still free
The operators:
* << = Left Shift -> shifts each bit of a number to the left the specified amount of time.
    0001 << 2 => 0100
    0001 << 1 => 0010
* >> = Right Shift -> shifts each bit of a number to the right the specified amount of time.
    1100 >> 2 => 0011
    0101 >> 3 => 0001 (the last one will be removed since it can't go anywhere)
* & => AND -> if both bits are 1 then 1, else it's 0
    1010 & 0010 = 0010
*/
int is_col_taken(int n, int col_index)
{
    return ((n & (1 << col_index)) >> col_index);
}

/*
    Takes an integer array, and makes each of its value 0.
*/
void zeroize(int *arr, int size)
{
    while (size--)
        arr[size] = 0;
}

/*
    items - contains the value of the table from the four different views
    items[0] => view from top = res[j][i];
    items[1] => view from bottom = res[3 - j][i];
    items[2] => view from left = res[i][3 - j];
    items[3] => view from right = res[i][3 - j];

    so this function puts takes this values from the table (res[4][4])
    and puts it into the items array.
*/
void set_items(int res[4][4], int *items, int i, int j)
{
    items[0] = res[j][i];
    items[1] = res[3 - j][i];
    items[2] = res[i][j];
    items[3] = res[i][3 - j];
}

/*
    view_count -> this array contains the number of buildings we can see
    from all 4 angles (Top, Bottom, Left, Right)
    maxes -> the height of the maximum building seen from all sides (Top, B, L, R)
    items - contains the current buildings we are checking from all sides.
        if the height of the current building (item[i]) is greater than
        the maximum height of a building from that side (max[i])
        then we add the number of buildings we can see (view_count[i]++);
*/
void set_values(int *view_count, int *maxes, int *items)
{
    if (items[0] > maxes[0]) // From Top
    {
        view_count[0]++;
        maxes[0] = items[0];
    }
    if (items[1] > maxes[1]) // From Bottom
    {
        view_count[1]++;
        maxes[1] = items[1];
    }
    if (items[2] > maxes[2]) // From Left
    {
        view_count[2]++;
        maxes[2] = items[2];
    }
    if (items[3] > maxes[3]) // From Right
    {
        view_count[3]++;
        maxes[3] = items[3];
    }
}

/*
    changes num to array (list)
    if num = 4532 => arr becomes {4, 5, 3, 2}
*/
void to_int_array(int *arr, int num)
{
    arr[0] = num / 1000;
    arr[1] = (num / 100) % 10;
    arr[2] = (num / 10) % 10;
    arr[3] = num % 10;
}
