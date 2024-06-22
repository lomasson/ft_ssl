#include "../include/ft_ssl.h"

static void ssl(t_conf *conf)
{
	switch(conf->ssl_conf.cmd)
	{
		case MD5:
		{
			md5(&conf->md5_conf);	
		}
		case SHA256:
		{

		}
		default:
		{
		}
	}
}

static void init_ssl_conf(t_conf *conf, t_args *args)
{
	switch(args->ssl_conf.cmd)
	{
		case MD5:
		{
			md5_init_conf((t_md5_args *)args, (t_md5_conf *)conf);	
		}
		case SHA256:
		{

		}
		default:
		{
		}
	}

}


int main(int argc, char **argv) {
	t_args ssl_args;
	t_conf ssl_conf;

	ssl_parser(argc, argv, &ssl_args);
	init_ssl_conf(&ssl_conf, &ssl_args);
	ssl(&ssl_conf);
	printf("TOTO\n");
}
