/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:10:07 by lquehec           #+#    #+#             */
/*   Updated: 2023/11/24 15:52:39 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"

// Error handling
enum e_errors
{
	MEMORY_ERR = -1,
	CMD_NOT_FOUND_ERR = -2,
	ARGS_ERR = -3,
	FILE_ERR = -4,
	F_PERM_ERR = -5,
	ENV_PATH_ERR = -6,
	DUP_ERR = -7,
	PIPE_ERR = -8,
	FORK_ERR = -9,
	EXEC_ERR = -10,
	EDGE_CASE_ERR = -11,
};

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int		here_doc;
	char	**env_path;
	t_list	*cmds;
}	t_pipex;

typedef struct s_pipexcmd
{
	char	*path;
	char	**cmd;
}	t_pipexcmd;

t_pipex		*ft_init_pipex(int ac, char **av, char **envp);
void		*ft_exec(t_pipex *pipex_info, char **envp);
void		*ft_child_proc(t_pipex *info,
				t_list *cmd_head, int fd[2], char **envp);

// PARSING
int			ft_cmd_finder(char *cmd, char **path, t_pipex *pipex_info);
t_list		*ft_parse_cmds(int ac, char **av, t_pipex *pipex_info);

// ERROR
void		*ft_exit(char *param, int error, t_pipex *pipex_info, char ***cmd);
void		ft_error(char *param, int error);
int			is_valid_error(int error);

// FREE
void		ft_free_matrix(char ***matrix);
void		ft_free_cmd(void *content);

// UTILS
char		*ft_get_env_path(char *str, char **envp);
t_pipexcmd	*ft_new_cmd(char *path, char **cmd);
t_list		*ft_lstnew_cmd(char *path, char **cmd);
int			ft_is_edge_case(char *str);

#endif