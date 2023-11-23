#include "pipex.h"

t_pipex	*ft_init_pipex(int ac, char **av, int here_doc)
{
	t_pipex	*pipex_info;

	pipex_info = (t_pipex *) malloc(sizeof(t_pipex));
	if (!pipex_info)
		return (NULL); // ERROR W/ MEMORY => NO_MEMORY
	pipex_info->here_doc = 0;
	pipex_info->cmds = NULL;
	pipex_info->fd_in = open(av[1], O_RDONLY);
	if (pipex_info->fd_in == -1)
		return (NULL); // ERROR W/ FILE => NO_FILE
	if (!here_doc)
		pipex_info->fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (access(av[ac - 1], F_OK) == -1)
		return (NULL); // ERROR W/ FILE => NO_FILE
	if (access(av[ac - 1], W_OK) == -1)
		return (NULL); // ERROR W/ FILE PERMISSION => NO_FILE_PERM
	return (pipex_info);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipex_info;

	(void)envp;
	printf("envp: %s\n", envp[5]);
	if (ac != 5)
		return (1); // ADD ERROR HANDLING
	if (access(av[1], F_OK) == -1)
		return (1); // ADD ERROR HANDLING
	if (access(av[1], R_OK) == -1)
		return (1); // ADD ERROR HANDLING
	printf("FT_INIT\n");
	pipex_info = ft_init_pipex(ac, av, 1);
	printf("OUTPUT: %i\n", pipex_info->fd_in);
	// ft_parse_cmds();
	// ft_parse_args();
	// ft_exec();
	// ft_cleanup();
	return (0);

}