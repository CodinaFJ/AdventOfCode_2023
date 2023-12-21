/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:03:48 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/21 20:03:48 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AOC.h"

long long	min_n(long long n1, long long n2)
{
	if (n1 < n2)
		return n1;
	else
		return n2;
}

long long	get_mcd(long long n1, long long n2)
{
	long long min;

	min = min_n(n1, n2);
	for (int i = min; i >= 0; i--)
	{
		if (n1 % i == 0 && n2 % i == 0)
			return (i);
	}
	return (1);
}

long long	mcm(long long n1, long long n2)
{
	long long	res;
	long long	mcd;

	res = n1 * n2;
	if (res < 0)
		res *= -1;
	mcd = get_mcd(n1, n2);
	res = res / mcd;
	return (res);
}

int	main(void)
{
	long long res;

	res = mcm(3739, 3793);
	res = mcm(res, 3923);
	res = mcm(res, 4027);
	printf("Res: %lld\n", res);
	return (0);
}