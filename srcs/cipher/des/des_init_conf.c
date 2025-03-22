#include "des.h"

void des_init_conf(void *v_args, void *v_conf)
{
    t_des_args *args = (t_des_args *)v_args;
	t_des_conf *conf = (t_des_conf *)v_conf;
    
    if (args->infile)
    {
        conf->fd_input = open(args->infile, O_RDONLY, 0);
        if (conf->fd_input < 0)
        {
            perror("input file opening");
            exit(1);
        }
        free(args->infile);
    }
    else
        conf->fd_input = STDIN_FILENO;
    if (args->outfile)
    {
        conf->fd_output = open(args->outfile, O_RDWR | O_CREAT | O_TRUNC , 0666);
        if (conf->fd_output < 0)
        {
            perror("output file opening");
            exit(1);
        }
        free(args->outfile);
    }
    else
        conf->fd_output = STDOUT_FILENO;
}
