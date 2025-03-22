#include "base64.h"

void base64_init_conf(void *v_args, void *v_conf)
{
    t_base64_args *args = (t_base64_args *)v_args;
	t_base64_conf *conf = (t_base64_conf *)v_conf;
    
    if (args->infile)
    {
        conf->input = open(args->infile, O_RDONLY, 0);
        if (conf->input < 0)
        {
            perror("infile open");
            exit(1);
        }
    }
    else
        conf->input = STDIN_FILENO;
    if (args->outfile)
    {
        conf->fd_outfile = open(args->outfile, O_RDWR | O_CREAT | O_TRUNC , 0666);
        printf("outfile: %s:fd:%d\n", args->outfile, conf->fd_outfile);
        if (conf->fd_outfile < 0)
        {
            perror("outfile open");
            exit(1);
        }
    }
    else
        conf->fd_outfile = STDOUT_FILENO;
    conf->encode = args->encode;
}
