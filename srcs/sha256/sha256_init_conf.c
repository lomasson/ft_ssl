#include "sha256.h"

void sha256_init_conf(t_sha256_args *args, t_sha256_conf *conf)
{
	memset(conf->input_fd, -1, sizeof(int) * 9);
	conf->cmd = SHA256;
	conf->append= (t_sha256_conf *)args->append;
	conf->quiet_mode = (t_sha256_conf *)args->quiet_mode;
	conf->reverse_mode = (t_sha256_conf *)args->reverse_mode;
	int i = 0;
	int y = 0;
	char buffer[1024] = {0};
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);


	char	check_stdin;
	fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
	if (read(STDIN_FILENO, &check_stdin, 1) > 0 && conf->input_fd[0] < 0)
		fcntl(STDIN_FILENO, F_SETFL, flags );

	if (read(STDIN_FILENO, &buffer, 1024) > 0)
	{
		conf->input_fd[i] = fileno(tmpfile());
		write(conf->input_fd[i], &check_stdin, strlen(&check_stdin));
		while (read(STDIN_FILENO, &buffer, 1024) > 0)
			write(conf->input_fd[i], buffer, strlen(buffer));
		lseek(conf->input_fd[i], 0, SEEK_SET);
		conf->file_in[i++] = "stdin";
	}
	if (args->str_in)
	{
		conf->input_fd[i] = fileno(tmpfile());
		write(conf->input_fd[i], args->str_in, strlen(args->str_in));
		lseek(conf->input_fd[i], 0, SEEK_SET);
		conf->file_in[i++] = args->str_in;
	}
	while (args->file_in[y] && y < MAX_INPUT_FILE)
	{
		// printf("READ FILE:	%s\n", args->input_fd[y]);
		conf->input_fd[i] = open(args->file_in[y], O_RDONLY);
		conf->file_in[i] = args->file_in[y];
		i++;
		y++;
	}
}
