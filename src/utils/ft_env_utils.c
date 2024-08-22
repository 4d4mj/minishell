/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:56:43 by akaterji          #+#    #+#             */
/*   Updated: 2024/08/11 16:18:55 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_env_new(char *str)
{
	t_env	*new_env;
	int		i;
	char	*var;
	char	*comp;

	i = 0;
	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->next = NULL;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	var = ft_substr(str, 0, i);
	comp = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	new_env->env_var = ft_strjoin("$", var);
	if (comp == NULL)
		comp = ft_strdup("' '");
	new_env->env_comp = ft_strdup(comp);
	free(var);
	free(comp);
	return (new_env);
}

void	ft_env_add_back(t_env **env_list, t_env *new_env)
{
	t_env	*current_env;

	current_env = *env_list;
	if (*env_list == NULL)
	{
		*env_list = new_env;
		return ;
	}
	while (current_env->next != NULL)
		current_env = current_env->next;
	current_env->next = new_env;
}

void	ft_add_env_list(char *str, t_env **env_list)
{
	t_env	*new_env;

	new_env = ft_env_new(str);
	if (!new_env)
		return ;
	ft_env_add_back(env_list, new_env);
}

char	*ft_get_shlvl(char *str)
{
	char		*ret;
	int			i;
	char		*itoa;

	ret = NULL;
	ret = ft_substr(str, 6, ft_strlen(ret) - 5);
	i = ft_atoi(ret);
	i++;
	free(ret);
	itoa = ft_itoa(i);
	ret = ft_strjoin("SHLVL=", itoa);
	free(itoa);
	return (ret);
}
