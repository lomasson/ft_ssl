#include "../include/ft_ssl.h"

int main(int argc, char **argv)
{
	t_args ssl_args;
	t_conf ssl_conf;

	t_ssl array[] = ARRAY_CMD;
	for (int i = 0; array[i].name; i++)
	{
		if (strcmp(array[i].name, argv[1]) != 0)
			continue ;
		array[i].parser(--argc, ++argv, &ssl_args);
		array[i].init(&ssl_args, &ssl_conf);
		array[i].hash(&ssl_conf);
	}
}
