/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 03:48:18 by allanganoun       #+#    #+#             */
/*   Updated: 2021/08/22 03:49:05 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}
