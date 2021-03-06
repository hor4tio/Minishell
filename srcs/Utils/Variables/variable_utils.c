/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:34:27 by allanganoun       #+#    #+#             */
/*   Updated: 2021/10/04 23:07:03 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	init_values(int *i, int *j, int *ret)
{
	*i = 0;
	*j = 0;
	*ret = 0;
}

int	variable_process_end(int j, int ret, char **str, char **result)
{
	(*result)[j] = '\0';
	free_replace(str, result);
	return (ret);
}

int	cpy_variable(int *i, int *j, char *name, char *value)
{
	*i += ft_strlen(name);
	*j += ft_strlen(value);
	return (1);
}

int	replace_word(char **str, char *name, char *value, char **tab)
{
	int		i;
	int		j;
	int		ret;
	char	*result;

	init_values(&i, &j, &ret);
	result = malloc(count_to_copy(*str, name)
			+ (count_word(*str, name) * ft_strlen(value)) + 1);
	while (str && (*str)[i] != '\0')
	{
		if ((*str)[i] == '$' && is_convertible(*str, i) == SUCCESS && ret == 0)
		{
			ret = 2;
			if (ft_strncmp(&((*str)[i]), name, variable_len(&((*str)[i]))) == 0)
			{
				ft_strcpy(&result[j], value);
				ret = cpy_variable(&i, &j, name, value);
			}
			else if (value_existence(&((*str)[i]), tab) == 0)
				i += variable_len(&((*str)[i]));
		}
		if ((*str)[i] != '\0')
			result[j++] = (*str)[i++];
	}
	return (variable_process_end(j, ret, str, &result));
}

void	get_variable_value(char **str, char **env)
{
	char	**tab;
	char	**env2;
	char	*sig_int;
	int		i;

	sig_int = ft_itoa(g_sig.sigquit);
	env2 = ft_tabdup(env);
	reallocate_tab(&env2, ft_strjoin("?=", sig_int));
	tab = value_name_tab(env2);
	i = 0;
	if ((*str)[0] == '~' && ((*str)[1] == '/'
			|| (*str)[1] == '\0'))
		tild_replacer(str, env);
	while (tab[i] != NULL && *str)
	{
		if (replace_word(str, tab[i], my_getenv(tab[i] + 1, env2), tab) == 1)
			i = -1;
		i++;
	}
	safe_free(&sig_int);
	free_tab(&tab);
	free_tab(&env2);
}
