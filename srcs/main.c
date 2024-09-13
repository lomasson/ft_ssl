#include "../include/ft_ssl.h"

static void ssl(t_conf *conf, t_args *args)
{
	switch(args->ssl_conf.cmd)
	{
		case MD5:
		{
			digest_init_conf((t_digest_args *)args, (t_digest_conf *)conf);
			md5((t_digest_conf *)conf);	
			break ;
		}
		case SHA256:
		{
			digest_init_conf((t_digest_args *)args, (t_digest_conf *)conf);
			hash_sha256((t_digest_conf *)conf);
			break ;
		}
		default:
		{
			fprintf(stderr, "ft_ssl: bad command\n");
			exit(1);
		}
	}
}

int main(int argc, char **argv)
{
	t_args ssl_args;
	t_conf ssl_conf;

	ssl_parser(argc, argv, &ssl_args);
	ssl(&ssl_conf, &ssl_args);
}
