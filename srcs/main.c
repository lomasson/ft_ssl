#include "../include/ft_ssl.h"
#include "md5/md5.h"
#include "sha256/sha256.h"

static void ssl(t_conf *conf)
{
	switch(conf->ssl_conf.cmd)
	{
		case MD5:
		{
			md5((t_md5_conf *)conf);	
			break ;
		}
		case SHA256:
		{
			hash_sha256((t_sha256_conf *)conf);
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
			md5_init_conf((t_md5_args *)args, (t_md5_conf *)conf);	
			break ;
		}
		case SHA256:
		{
			sha256_init_conf((t_sha256_args *)args, (t_sha256_conf *)conf);
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
