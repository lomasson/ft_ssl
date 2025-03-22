#include "ecb.h"

void	ecb(void *v_conf)
{
	t_des_conf *conf = (t_des_conf *)v_conf;
    printf("des: Work in progress\n");
    free(conf->iv);
    free(conf->key);
    free(conf->password);
    free(conf->salt);
    if (conf->fd_output != STDOUT_FILENO)
		close(conf->fd_output);
	if (conf->fd_input != STDIN_FILENO)
		close(conf->fd_input);
}