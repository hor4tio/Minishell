/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 23:29:18 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/05 19:59:14 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd_process(t_token *token)
{
	char	buff[PATH_MAX];

	if (token->option != NULL)
		return (write_errors5(token->cmd, token->option[0], 0));
	else if (getcwd(buff, PATH_MAX))
	{
		ft_putendl_fd(buff, 1);
		g_sig.exit_status = 0;
	}
	else
	{
		ft_putendl_fd("PATH error", STDERR_FILENO);
		g_sig.exit_status = 1;
	}
	return (TRUE);
}
