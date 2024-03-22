#include "philo.h"

//Print custom error message and exit
void	error_exit(const char *error_msg)
{
	printf(MAGENTA "%s\n" RESET, error_msg);
	exit(EXIT_FAILURE);
}
