#include "../../headers/cub3d.h"

void	ft_error(int x)
{
	if (x == 0)
		write(2, "Error : Wrong argument number\n", 30);
	if (x == 1)
		write(2, "Error : Wrong extention\n", 24);
	if (x == 2)
		write(2, "Error : This is a directory\n", 28);
	if (x == 3)
		write(2, "Error : Invalid char\n", 21);
	if (x == 4)
		write(2, "Error : No direction\n", 21);
	if (x == 5)
		write(2, "Error : Only one direction\n", 27);
	if (x == 6)
		write(2, "Error : Hole in the wall\n", 25);
	if (x == 7)
		write(2, "Error : File not properly read\n", 32);
	if (x == 8)
		write(2, "Error : Wrong parameter\n", 24);
	exit(EXIT_FAILURE);
}

int	ft_exit(void)
{
	write(1, "Bye Bye!\n", 9);
	exit(0);
}
