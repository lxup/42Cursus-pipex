#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft/libft.h"

// Error handling
enum errors
{
    NO_MEMORY = -1,
};

typedef struct s_pipex
{
    int		fd_in;
    int		fd_out;
    t_list	*cmds;   
}   t_pipex;

typedef struct s_pipexcmd
{
    char    *path;
    char    **cmd;
}   t_pipexcmd;


void    ft_error(char *param, int error);
t_pipex	*ft_init_pipex(int ac, char **av);


#endif