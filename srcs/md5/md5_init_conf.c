#include "md5.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void md5_init_conf(t_md5_args *args, t_md5_conf *conf)
{
	memset(conf->file_in, -1, sizeof(int) * 9);
	conf->cmd = MD5;
	conf->append= (t_md5_conf *)args->append;
	conf->quiet_mode = (t_md5_conf *)args->quiet_mode;
	conf->reverse_mode = (t_md5_conf *)args->reverse_mode;
	int i = 0;
	int y = 0;
	char buffer[1024] = {0};

    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) | O_NONBLOCK);
	if (read(STDIN_FILENO, &buffer, 1024) > 0)
	{
		printf("READ STDIN:	FUND\n");
		conf->file_in[i] = fileno(tmpfile());
		write(conf->file_in[i], buffer, strlen(buffer));
		lseek(conf->file_in[i++], 0, SEEK_SET);
	}
	else
		printf("READ STDIN:	NOT_FUND\n");
	if (args->str_in)
	{
		printf("READ STR:	FUND\n");
		conf->file_in[i] = fileno(tmpfile());
		write(conf->file_in[i], args->str_in, strlen(args->str_in));
		lseek(conf->file_in[i++], 0, SEEK_SET);
	}
	else
		printf("READ STR:	NOT_FUND\n");
	if (!args->file_in[y])
		printf("READ FILE:	NOT_FUND\n");
	while (args->file_in[y] && y < MAX_INPUT_FILE)
	{
		// printf("READ FILE:	%s\n", args->file_in[y]);
		printf("READ FILE:	FUND\n");
		conf->file_in[i] = open(args->file_in[y], O_RDONLY);
		i++;
		y++;
	}
}
