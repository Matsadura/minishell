#include "../includes/execution.h"

/**
 * 
 */
void	clean_exit(int exit_code)
{
	gc_cleanup();
	exit(exit_code);
}
