/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:09:43 by lquehec           #+#    #+#             */
/*   Updated: 2023/11/23 22:09:44 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_matrix(char ***matrix)
{
	int	i;

	i = 0;
	while (matrix[0] && matrix[0][i])
	{
		free(matrix[0][i]);
		i++;
	}
	free(matrix[0]);
	matrix = NULL;
}

void	ft_free_cmd(void *content)
{
	t_pipexcmd	*cmd;

	cmd = (t_pipexcmd *)content;
	free(cmd->path);
	ft_free_matrix(&cmd->cmd);
	free(cmd);
}
