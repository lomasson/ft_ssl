#include "ft_ssl.h"

void print_usage(t_ssl *array)
{
	printf("./ft_ssl [COMMAND] \n");
	while (array->name)
	{
		if (array->helper)
			array->helper();
		array++;
	}
	exit(1);
}

int main(int argc, char **argv)
{
	t_args ssl_args;
	t_conf ssl_conf;

	t_ssl array[] = ARRAY_CMD;
	if (argc < 2 ||strcmp(argv[1], "--usage") == 0)
		print_usage(array);
	for (int i = 0; array[i].name; i++)
	{
		if (strcmp(array[i].name, argv[1]) != 0)
			continue ;
		array[i].parser(--argc, ++argv, &ssl_args);
		array[i].init(&ssl_args, &ssl_conf);
		array[i].hash(&ssl_conf);
		exit(1);
	}
	print_usage(array);
}
