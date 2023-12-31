/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:09:26 by lquehec           #+#    #+#             */
/*   Updated: 2023/11/24 16:18:05 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*ft_init_pipex(int ac, char **av, char **envp)
{
	t_pipex	*pipex_info;

	pipex_info = (t_pipex *) malloc(sizeof(t_pipex));
	if (!pipex_info)
		return ((t_pipex *)ft_exit(NULL, MEMORY_ERR, NULL, NULL));
	pipex_info->cmds = NULL;
	pipex_info->env_path = NULL;
	pipex_info->fd_in = open(av[1], O_RDONLY);
	if (pipex_info->fd_in == -1)
		return ((t_pipex *)ft_exit(av[1], FILE_ERR, pipex_info, NULL));
	pipex_info->fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (access(av[ac - 1], F_OK) == -1)
		return ((t_pipex *)ft_exit(av[ac - 1], FILE_ERR, pipex_info, NULL));
	if (access(av[ac - 1], W_OK) == -1)
		return ((t_pipex *)ft_exit(av[ac - 1], F_PERM_ERR, pipex_info, NULL));
	pipex_info->env_path = ft_split(ft_get_env_path("PATH", envp), ':');
	if (!pipex_info->env_path)
		return ((t_pipex *)ft_exit(NULL, ENV_PATH_ERR, pipex_info, NULL));
	return (pipex_info);
}

void	*ft_child_proc(t_pipex *info, t_list *cmd_head, int fd[2], char **envp)
{
	t_pipexcmd	*cmd;

	cmd = cmd_head->content;
	close(fd[0]);
	if (cmd_head->next && dup2(fd[1], STDOUT_FILENO) == -1)
		return (ft_exit(NULL, DUP_ERR, info, NULL));
	if (!cmd_head->next && dup2(info->fd_out, STDOUT_FILENO) == -1)
		return (ft_exit(NULL, DUP_ERR, info, NULL));
	close(fd[1]);
	close(info->fd_in);
	close(info->fd_out);
	if (execve(cmd->path, cmd->cmd, envp) == -1)
		return (ft_exit(*cmd->cmd, EXEC_ERR, info, NULL));
	return (NULL);
}

void	*ft_exec(t_pipex *pipex_info, char **envp)
{
	t_list	*cmd_head;
	int		fd[2];
	pid_t	pid;

	cmd_head = pipex_info->cmds;
	if (dup2(pipex_info->fd_in, STDIN_FILENO) == -1)
		return (ft_exit(NULL, DUP_ERR, pipex_info, NULL));
	while (cmd_head)
	{
		if (pipe(fd) == -1)
			return (ft_exit(NULL, PIPE_ERR, pipex_info, NULL));
		pid = fork();
		if (pid == -1)
			return (ft_exit(NULL, FORK_ERR, pipex_info, NULL));
		if (pid == 0)
			ft_child_proc(pipex_info, cmd_head, fd, envp);
		close(fd[1]);
		if (cmd_head->next && dup2(fd[0], STDIN_FILENO) == -1)
			return (ft_exit(NULL, DUP_ERR, pipex_info, NULL));
		waitpid(pid, NULL, 0);
		close(fd[0]);
		cmd_head = cmd_head->next;
	}
	return (NULL);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipex_info;

	if (ac < 5)
		return (*(int *)ft_exit("./pipex file1 cmd1 cmd2 ... cmd file2",
				ARGS_ERR, NULL, NULL));
	if (access(av[1], F_OK) == -1)
		return (*(int *)ft_exit(av[1], FILE_ERR, NULL, NULL));
	if (access(av[1], R_OK) == -1)
		return (*(int *)ft_exit(av[1], F_PERM_ERR, NULL, NULL));
	if (ft_is_edge_case(av[1]))
		return (*(int *)ft_exit(av[1], EDGE_CASE_ERR, NULL, NULL));
	pipex_info = ft_init_pipex(ac, av, envp);
	pipex_info->cmds = ft_parse_cmds(ac, av, pipex_info);
	ft_exec(pipex_info, envp);
	return (*(int *)ft_exit(NULL, 0, pipex_info, NULL));
}
