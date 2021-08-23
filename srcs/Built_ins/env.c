/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:06:24 by allanganoun       #+#    #+#             */
/*   Updated: 2021/08/24 00:48:00 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		env_process(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strchr(env[i], '=') != NULL)
		{
			ft_putstr_fd(env[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return (TRUE);
}
