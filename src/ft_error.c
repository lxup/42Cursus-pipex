#include "pipex.h"

void    ft_exit_handler(char *param, int error)
{
	(void)param;
	(void)error;
	exit(0);
}

void    ft_error(char *param, int error)
{
	if (error == NO_MEMORY)
		ft_putstr_fd("DAMN, no memory left on device", 2);
	// OTHER CASE

	if (param)
		ft_putstr_fd(param, 2);
	ft_putstr_fd("\n", 2);
}