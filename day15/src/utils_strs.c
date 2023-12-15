/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:26:01 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/13 11:26:01 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AOC.h"

void	add_line(char *str, char **strs)
{
	int i = 0;
	int j;
	int	len;

	while (strs[i] != NULL)
		i++;
	len = ft_strlen(str);
	strs[i] = malloc(len);
	ft_bzero(strs[i], len);
	for (j = 0; str[j] && str[j] != '\n'; j++)
		strs[i][j] = str[j];
	strs[i][j] = '\0';
}

void	reset_matrix(char **strs)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (strs[i] != NULL)
			free(strs[i]);
		strs[i] = NULL;
	}
}

int	row_cmp(char **strs, int x, int y)
{
	size_t	i;

	i = 0;
	while (strs[x][i] && strs[y][i])
	{
		if (strs[x][i] != strs[y][i])
			return (strs[x][i] - strs[y][i]);
		i++;
	}
	return (strs[x][i] - strs[y][i]);
}

int	col_cmp(char **strs, int x, int y)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		if (strs[i][x] != strs[i][y])
		{
			return (strs[i][x] - strs[i][y]);
		}
		i++;
	}
	return (0);
}
