#ifndef FT_SSL_HPP
# define FT_SSL_HPP
# include "../include/commands.h"
# include "../srcs/digest/digest.h"

typedef struct s_ssl_args {
	enum COMMAND	cmd;
} t_ssl_args;

typedef union {
	struct	s_ssl_args		ssl_conf;
	struct	s_digest_args		digest_args;
} t_args;

typedef union {
	struct	s_ssl_args		ssl_conf;
	struct	s_digest_conf		digest_conf;
} t_conf;


void	ssl_parser(const int argc, char **argv, t_args *ssl_args);

#endif // !FT_SSL_HPP
