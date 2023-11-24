/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:09:30 by lquehec           #+#    #+#             */
/*   Updated: 2023/11/24 15:33:40 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_cmd_finder(char *cmd, char **path, t_pipex *pipex_info)
{
	int		i;
	char	*path_builder;

	i = 0;
	*path = NULL;
	while (pipex_info->env_path && pipex_info->env_path[i])
	{
		free(*path);
		path_builder = ft_strjoin(pipex_info->env_path[i], "/");
		if (!path_builder)
			return (MEMORY_ERR);
		*path = ft_strjoin(path_builder, cmd);
		free(path_builder);
		if (!*path)
			return (free(path_builder), MEMORY_ERR);
		if (access(*path, F_OK) == 0)
			return (1);
		i++;
	}
	return (free(*path), CMD_NOT_FOUND_ERR);
}

t_list	*ft_parse_cmds(int ac, char **av, t_pipex *pipex_info)
{
	t_list	*cmds;
	char	*path;
	char	**cmd;
	int		cmd_finder;
	int		i;

	cmds = NULL;
	path = NULL;
	i = 1;
	while (++i < ac - 1)
	{
		pipex_info->cmds = cmds;
		cmd = ft_split(av[i], ' ');
		if (!cmd || !*cmd)
			return ((t_list *)ft_exit(NULL, CMD_NOT_FOUND_ERR,
					pipex_info, &cmd));
		cmd_finder = ft_cmd_finder(*cmd, &path, pipex_info);
		if (cmd_finder == MEMORY_ERR)
			return ((t_list *)ft_exit(NULL, MEMORY_ERR, pipex_info, &cmd));
		if (cmd_finder == CMD_NOT_FOUND_ERR)
			return ((t_list *)ft_exit(*cmd, CMD_NOT_FOUND_ERR,
					pipex_info, &cmd));
		ft_lstadd_back(&cmds, ft_lstnew_cmd(path, cmd));
	}
	return (cmds);
}
