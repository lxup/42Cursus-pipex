/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:09:35 by lquehec           #+#    #+#             */
/*   Updated: 2023/11/24 12:26:36 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipexcmd	*ft_new_cmd(char *path, char **cmd)
{
	t_pipexcmd	*new_cmd;

	if (!cmd || !path)
		return (NULL);
	new_cmd = malloc(sizeof(t_pipexcmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->path = path;
	if (!new_cmd->path)
	{
		free(new_cmd);
		return (NULL);
	}
	new_cmd->cmd = cmd;
	return (new_cmd);
}

t_list	*ft_lstnew_cmd(char *path, char **cmd)
{
	t_list	*new_lst;

	new_lst = (t_list *)malloc(sizeof(t_list));
	if (!new_lst)
		return (NULL);
	new_lst->content = ft_new_cmd(path, cmd);
	if (!new_lst->content)
	{
		free(new_lst);
		return (NULL);
	}
	new_lst->next = NULL;
	return (new_lst);
}

char	*ft_get_env_path(char *str, char **envp)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		path = ft_substr(envp[i], 0, j);
		if (ft_strncmp(path, str, ft_strlen(str)) == 0)
		{
			free(path);
			return (envp[i] + j + 1);
		}
		free(path);
		i++;
	}
	return (NULL);
}

int	ft_is_edge_case(char *str)
{
	if (ft_strncmp(str, "/dev/urandom", 12) == 0)
		return (1);
	if (ft_strncmp(str, "/dev/stdin", 10) == 0)
		return (1);
	return (0);
}
