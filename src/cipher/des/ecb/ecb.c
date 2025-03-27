#include "ecb.h"

#define ECB_READ_SIZE 8

void	ecb(void *v_conf)
{
	t_des_conf *conf = (t_des_conf *)v_conf;
  printf("des: Work in progress\n");
  // int rread = read(conf->fd_input)
  free(conf->iv);
  if (conf->fd_output != STDOUT_FILENO)
		close(conf->fd_output);
	if (conf->fd_input != STDIN_FILENO)
		close(conf->fd_input);
}