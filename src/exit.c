/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:09:38 by lquehec           #+#    #+#             */
/*   Updated: 2023/11/24 12:20:20 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_valid_error(int error)
{
	return (error == MEMORY_ERR || error == CMD_NOT_FOUND_ERR
		|| error == INVALID_ARGS || error == NO_FILE
		|| error == NO_FILE_PERMISSION || error == NO_ENV_PATH
		|| error == DUP_ERR || error == PIPE_ERR || error == FORK_ERR
		|| error == EXEC_ERR || error == EDGE_CASE_ERR);
}

void	*ft_exit(char *param, int error, t_pipex *pipex_info, char ***cmd)
{
	if (is_valid_error(error))
		ft_error(param, error);
	if (cmd)
		ft_free_matrix(cmd);
	if (pipex_info)
	{
		close(pipex_info->fd_in);
		close(pipex_info->fd_out);
		close(STDIN_FILENO);
		if (pipex_info->env_path)
			ft_free_matrix(&pipex_info->env_path);
		if (pipex_info->cmds)
			ft_lstclear(&pipex_info->cmds, ft_free_cmd);
		free(pipex_info);
	}
	if (error < 0)
		return (exit(EXIT_FAILURE), (void *)EXIT_FAILURE);
	else
		return (exit(EXIT_SUCCESS), (void *)EXIT_SUCCESS);
	return (0);
}

void	ft_error(char *param, int error)
{
	if (error == MEMORY_ERR)
		ft_putstr_fd("DAMN, no memory left on device", 2);
	if (error == CMD_NOT_FOUND_ERR)
		ft_putstr_fd("That's sad, this command not found: ", 2);
	if (error == INVALID_ARGS)
		ft_putstr_fd("Mhh, bro... come one, give me valid arguments", 2);
	if (error == NO_FILE)
		ft_putstr_fd("Well, there is something wrong with this file: ", 2);
	if (error == NO_FILE_PERMISSION)
		ft_putstr_fd("U DONT HAVE THE PERMISSION ON THIS FILE: ", 2);
	if (error == NO_ENV_PATH)
		ft_putstr_fd("Are u even using a computer ? I dont find the fucking env path bro...", 2);
	if (error == DUP_ERR)
		ft_putstr_fd("I dont know why, but the dup2() function failed", 2);
	if (error == PIPE_ERR)
		ft_putstr_fd("A pi() function can failed ? Well I didn't know", 2);
	if (error == FORK_ERR)
		ft_putstr_fd("A fork() error, did u know that ? Unlucky af !", 2);
	if (error == EXEC_ERR)
		ft_putstr_fd("F***, the execution of this command failed: ", 2);
	if (error == EDGE_CASE_ERR)
		ft_putstr_fd("Come one, u try to broke my code right ? Who df u think u are ? Well this file is an edge case: ", 2);
	if (param)
		ft_putstr_fd(param, 2);
	ft_putstr_fd("\n", 2);
}
