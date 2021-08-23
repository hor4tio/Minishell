/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:34:34 by allanganoun       #+#    #+#             */
/*   Updated: 2021/08/24 00:48:16 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_name(char *name)
{
	int i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '=' && (i > 0))
			return (i);
		i++;
	}
	return (0);
}

void	rm_dollar_str(char **str)
{
	char *tmp;

	if ((*str)[0] == '$')
	{
		tmp = ft_malloc(ft_strlen(*str));
		ft_strcpy(tmp, &((*str)[1]));
		safe_free(str);
		*str = tmp;
	}
}

char	**export_name_tab(char **env)
{
	int i;
	int j;
	char **tab;

	i = 0;
	tab = ft_malloc(sizeof(char *) * (tablen(env) + 1));
	while (env[i] != NULL)
	{
		tab[i] = ft_strdup(env[i]);
		i++;
	}
	tab[i] = NULL;
	i = 0;
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j] != '=')
			j++;
		tab[i][j + 1] = '\0';
		i++;
	}
	return (tab);
}

void	export_process2(t_token *token, char ***env, char **str, char **tab)
{
	if (variable_existence(*str, tab) > 0 && check_name(*str) > 0)
	{
		if ((*str)[0] == '$')
			(*str)++;
		if (token->exp == 1)
			get_variable_value(str, *env);
		free((*env)[variable_existence(*str, tab)]);
		(*env)[variable_existence(*str, tab)] = ft_strdup(*str);
	}
	else if ((*str)[0] == '$')
		write_errors(6, &((*str)[check_name(*str)]));
	else
	{
		if (token->exp == 1)
			get_variable_value(str, *env);
		printf("test = %s\n", *str);
		reallocate_tab(env, *str);
	}
}

int		export_process(t_token *token, char ***env)
{
	int i;
	char *str;
	char **tab;

	i = 0;
	tab = export_name_tab(*env);
	if (token->arg)
		quote_remover(&(token->arg[i]), &token);
	if (token->arg == NULL ||
		(token->arg[i][0] == '$' && check_name(token->arg[i]) == 0))
			print_sorted_tab(*env);
	else
	{
		while (token->arg && token->arg[i] != NULL)
		{
			quote_remover(&(token->arg[i]), &token);
			str = ft_strdup(token->arg[i]);
			export_process2(token, env, &str, tab);
			i++;
		}
	}
	free_tab(&tab);
	return (TRUE);
}
