#include "../include/ft_ssl.h"

static void ssl(t_conf *conf)
{
	switch(conf->ssl_conf.cmd)
	{
		case MD5:
		{
			md5((t_digest_conf *)conf);	
			break ;
		}
		case SHA256:
		{
			hash_sha256((t_digest_conf *)conf);
			break ;
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
			digest_init_conf((t_digest_args *)args, (t_digest_conf *)conf);	
			break ;
		}
		case SHA256:
		{
			digest_init_conf((t_digest_args *)args, (t_digest_conf *)conf);
			break ;
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
}
