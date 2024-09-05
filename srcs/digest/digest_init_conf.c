#include "digest.h"

static void init_struct_digest(t_digest_args *args, t_digest_conf *conf)
{
	*conf = (t_digest_conf){ 
		.file_in[0] = NULL,
			.cmd = args->cmd,
			.append = args->append,
			.quiet_mode = args->quiet_mode,
			.reverse_mode = args->reverse_mode,
			.std_in_fd = -1,
	};
	memset(conf->input_fd, -1, sizeof(int) * 9);
}

void digest_init_conf(t_digest_args *args, t_digest_conf *conf)
{
	init_struct_digest(args, conf);
	int i = 0;
	int y = 0;
		
	char	*save_buffer = calloc(51, 1);
	char	tmp_buffer[1025] = {0};
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);


	// char	check_stdin = 0;
	fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
	if (read(STDIN_FILENO, save_buffer, 50) <= 0 && !*args->file_in && !args->str_in)
		fcntl(STDIN_FILENO, F_SETFL, flags );
	if (strlen(save_buffer) || (!*args->file_in && !args->str_in))
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
		conf->std_in_fd = conf->input_fd[i];
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
