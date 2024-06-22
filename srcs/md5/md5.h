
#ifndef MD5_H
#define MD5_H
# include <argp.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>

# define MAX_INPUT_FILE 8
# define MD5_DIGEST_LEN 32
# define MD5_BLOCK_LENGHT 64 // 64 byte = 512 bit
# define MD5_BLOCK_LENGHT_WIHOUT_PADDING 54 // 64 byte = 512 bit
# define MD5_WORD_LEN 32
# define MD5_HASH_LEN 32
enum COMMAND {
	MD5,
	SHA256
};

typedef struct s_M {
    uint32_t w0;
    uint32_t w1;
    uint32_t w2;
    uint32_t w3;
    uint32_t w4;
    uint32_t w5;
    uint32_t w6;
    uint32_t w7;
    uint32_t w8;
    uint32_t w9;
    uint32_t w10;
    uint32_t w11;
    uint32_t w12;
    uint32_t w13;
    uint32_t w14;
    uint32_t w15;
} t_M;

typedef struct s_md5 {
	t_M M;
	struct s_md5 *next;
} t_md5;

typedef struct s_md5_args {
	enum COMMAND	cmd;
	bool			quiet_mode;
	bool			reverse_mode;
	bool			append;
	char			*file_in[MAX_INPUT_FILE];
	char			*str_in;
} t_md5_args;

typedef struct s_md5_conf {
	enum COMMAND	cmd;
	bool			quiet_mode;
	bool			reverse_mode;
	bool			append;
	int				file_in[MAX_INPUT_FILE + 1];
} t_md5_conf;

void md5_parser(struct argp_state *state);
void md5_init_conf(t_md5_args *args, t_md5_conf *conf);
void md5(t_md5_conf *conf);

#endif
