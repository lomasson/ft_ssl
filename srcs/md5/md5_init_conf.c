#include "md5.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
void md5_init_conf(t_md5_args *args, t_md5_conf *conf)
{
	memset(conf->input_fd, -1, sizeof(int) * 9);
	conf->file_in[0] = NULL;
	conf->cmd = MD5;
	conf->append= (t_md5_conf *)args->append;
	conf->quiet_mode = (t_md5_conf *)args->quiet_mode;
	conf->reverse_mode = (t_md5_conf *)args->reverse_mode;
	int i = 0;
	int y = 0;
	char	*save_buffer = calloc(51, 1);
	char	tmp_buffer[1025] = {0};
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);


	// char	check_stdin = 0;
	fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
	if (read(STDIN_FILENO, save_buffer, 50) <= 0 && !*args->file_in)
		fcntl(STDIN_FILENO, F_SETFL, flags );
	if (strlen(save_buffer) || !*args->file_in)
	{
			// conf->file_in[i] = buffer;
		conf->input_fd[i] = fileno(tmpfile());
		write(conf->input_fd[i], save_buffer , strlen(save_buffer));
		while (read(STDIN_FILENO, tmp_buffer, 1024) > 0)
		{
			if (!*save_buffer)
				strncpy(save_buffer, tmp_buffer, 50);
			write(conf->input_fd[i], tmp_buffer, strlen(tmp_buffer));
		}
		lseek(conf->input_fd[i], 0, SEEK_SET);
		conf->input_fd[i] = STDIN_FILENO;
		conf->file_in[i] = save_buffer;
		i++;
	}
	else
		free(save_buffer);
	if (args->str_in)
	{
		conf->input_fd[i] = fileno(tmpfile());
		write(conf->input_fd[i], args->str_in, strlen(args->str_in));
		lseek(conf->input_fd[i], 0, SEEK_SET);
		conf->file_in[i++] = args->str_in;
	}
	while (args->file_in[y] && y < MAX_INPUT_FILE)
	{
		conf->input_fd[i] = open(args->file_in[y], O_RDONLY);
		if (conf->input_fd[i] < 0)
		{
			printf("%s: %s\n",args->file_in[y] ,strerror(errno));
			y++;
			continue ;
		}
		conf->file_in[i] = args->file_in[y];
		i++;
		y++;
	}
}
