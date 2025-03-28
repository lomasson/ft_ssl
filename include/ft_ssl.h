#ifndef FT_SSL_H
# define FT_SSL_H
# include "../src/digest/md5/md5.h"
# include "../src/digest/sha256/sha256.h"
# include "../src/cipher/base64/base64.h"
# include "../src/cipher/des/ecb/ecb.h"

# define ARRAY_CMD { \
	{"sha256", digest_parser, digest_init_conf, sha256, digest_helper },\
	{"md5", digest_parser, digest_init_conf, md5, NULL},\
	{"base64", base64_parser, base64_init_conf, base64, base64_helper},\
	{"des", des_parser, des_init_conf, ecb, NULL},\
	{"des-ecb", des_parser, des_init_conf, ecb, NULL},\
	{NULL, NULL, NULL, NULL, NULL}}

typedef union {
	t_digest_args		digest_args;
	t_base64_args		base64_args;
	t_des_args			des_args;
} t_args;

typedef union {
	t_digest_conf		digest_conf;
	t_base64_conf		base64_conf;
	t_des_conf			des_conf;
} t_conf;

typedef struct s_ssl {
	char *name;
	void (*parser)(int, char **, void *);
	void (*init)(void *, void *);
	void (*hash)(void *);
	void (*helper)(void);

} t_ssl;


#endif