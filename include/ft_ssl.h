#ifndef FT_SSL_HPP
# define FT_SSL_HPP
# include "../srcs/digest/md5/md5.h"
# include "../srcs/digest/sha256/sha256.h"

# define ARRAY_CMD { \
	{"sha256", digest_init_conf, digest_parser, sha256},\
	{"md5", digest_init_conf, digest_parser, md5},\
	{NULL, NULL, NULL, NULL}}

typedef union {
	struct	s_digest_args		digest_args;
} t_args;

typedef union {
	struct	s_digest_conf		digest_conf;
} t_conf;

typedef struct s_ssl {
	char *name;
	void (*init)(void *, void *);
	void (*parser)(int, char **, void *);
	void (*hash)(void *);

} t_ssl;


#endif // !FT_SSL_HPP
