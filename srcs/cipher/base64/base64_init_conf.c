#include "base64.h"

void base64_init_conf(void *v_args, void *v_conf)
{
    t_base64_args *args = (t_base64_args *)v_args;
	t_base64_conf *conf = (t_base64_conf *)v_conf;
    
    if (args->infile)
    {
        conf->input = open(args->infile, O_RDWR, 0);
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
        conf->input = open(args->outfile, O_CREAT | O_TRUNC | O_RDWR , 0);
        if (conf->input < 0)
        {
            perror("outfile open");
            exit(1);
        }
    }
    else
        conf->input = STDOUT_FILENO;
}