# include <stdio.h> //To call printf() for printing to the STDOUT
# include <stdlib.h> //To call malloc(), free() for memory management
# include <stdint.h> 
# include <sys/wait.h>
# include <unistd.h> //To call write(), usleep()
# include <stdbool.h> //To use boolean values
# include <errno.h> //To access various error codes during execution
# include <string.h> //To call memset()
# include <pthread.h> //For thread related functions
# include <sys/time.h> //To call gettimeofday()
# include <limits.h> //To use the MIN and MAX macros


//ANSI Escape Sequences for text formatting*****
# define RESET		"\033[0m" //Reset to default color 
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define MAGENTA	"\033[1;35m"
# define CYAN		"\033[1;36m"

void	error_exit(const char *error_msg)
{
	printf(MAGENTA "%s\n" RESET, error_msg);
	exit(EXIT_FAILURE);
}

//Define a function to convert the string input arguments into long integers. Static because it's only used for parsing here
static long	ft_atol(const char *s)
{
	long		res; //To store the converted string to integer. Long to handle larger than int data
	int			len; //To check the string length is not > 10, as INT_MAX has 10 digits
	
	res = 0;
	while ((*s == 32 || *s >= 9 && *s <= 13)) //Skip leading whitespaces
		s++;
	if (*s == '-' || *s == '+') //Check for `-` signs, and skip `+` signs
	{
		if (*s == '-')
			error_exit("Positive values only");
		s++;
	}
	if (!(*s >= '0' && *s <= '9')) //Check for invalid characters that are not digits
		error_exit("Digit values only");
	len = 0;
	while (*s >= '0' && *s <= '9')
	{
		res = (res * 10) + (*s - '0');
		s++;
		len++;
	}
	if (len > 10 || res > INT_MAX) //Check if the input is 10 or more digits, and if the result is > INT_MAX
		error_exit("The value cannot exceed the INT_MAX value 2147483647");
	return (res);
}


int main() {
    const char *test_string = "1234567890";
    long result = ft_atol(test_string);
    printf("Result: %ld\n", result);
    return 0;
}