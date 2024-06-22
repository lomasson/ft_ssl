#ifndef FT_SSL_HPP
# define FT_SSL_HPP
# include <stdio.h>
# include <getopt.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <argp.h>
# include "../srcs/md5/md5.h"

typedef struct s_ssl_args {
	enum COMMAND	cmd;
} t_ssl_args;

typedef union {
	struct	s_ssl_args		ssl_conf;
	struct	s_md5_args		md5_args;
	// struct	s_sha256_args	sha256_args;
} t_args;

typedef union {
	struct	s_ssl_args		ssl_conf;
	struct	s_md5_conf		md5_conf;
	// struct	s_sha256_args	sha256_args;
} t_conf;


void	ssl_parser(const int argc, char **argv, t_args *ssl_args);

#endif // !FT_SSL_HPP
