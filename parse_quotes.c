/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 15:41:52 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/02/20 15:48:35 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	*label_quotes(char *input, int *arr, int type)
{
	int		i;
	int		start;
	int		sup;
	char	d_or_s;

	sup = 0;
	i = 0;
	d_or_s = get_quote_type(type);
	while (input[i])
	{
		if (input[i] == d_or_s && sup == 0)
		{
			start = i;
			i++;
			sup = 1;
		}
		if (input[i] == d_or_s && sup == 1)
		{
			arr = label_vals(start, i, arr, type);
			sup = 0;
		}
		i++;
	}
	return (arr);
}

char	get_quote_type(int type)
{
	if (type == 0)
		return ('\'');
	else
		return ('\"');
}
