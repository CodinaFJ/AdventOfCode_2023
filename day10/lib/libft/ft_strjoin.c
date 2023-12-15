/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:09:04 by jcodina-          #+#    #+#             */
/*   Updated: 2023/11/11 19:27:59 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * Allocates a string where the result of the concatenation of s1 and s2
 * is copied - memory liberated after join.
 * @param s1 string 1.
 * @param s2 string 2.
 * @return Allocated string. NULL if allocation fails.
 */
char	*ft_strjoin_free(char **s1, char **s2)
{
	char	*str;
	size_t	size;

	size = ft_strlen(*s1) + ft_strlen(*s2);
	str = (char *)ft_calloc(1, size + 1);
	if (!str)
	{
		free(*s1);
		free(*s2);
		return (NULL);
	}
	ft_strlcat(str, *s1, size + 1);
	ft_strlcat(str, *s2, size + 1);
	free(*s1);
	free(*s2);
	*s1 = NULL;
	*s2 = NULL;
	return (str);
}

/**
 * Allocates a string where the result of the concatenation of s1 and s2
 * is copied.
 * @param s1 string 1.
 * @param s2 string 2.
 * @return Allocated string. NULL if allocation fails.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(size + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, size + 1);
	ft_strlcat(str, s2, size + 1);
	return (str);
}
