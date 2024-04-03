#include "philo.h"

//Print custom error message and exit
void	error_exit(const char *error_msg)
{
	printf(MAGENTA "%s\n" RESET, error_msg);
	return (INPUT_ERROR); //Exit
}

//Define malloc with a NULL return check for re-use and readability
void	*ft_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
	{
		printf(MAGENTA "Memory allocation unsuccessful" RESET);
		return (MALLOC_ERROR); //Exit
	}
	return (ret);
}
