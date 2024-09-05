#ifndef DIGEST_H
# define DIGEST_H

# include "../../include/commands.h"
# define MAX_INPUT_FILE 8

typedef struct s_digest_args {
	enum COMMAND	cmd;
	bool			quiet_mode;
	bool			reverse_mode;
	bool			append;
	char			*file_in[MAX_INPUT_FILE];
	char			*str_in;
} t_digest_args;

typedef struct s_digest_conf {
	enum COMMAND	cmd;
	bool			quiet_mode;
	bool			reverse_mode;
	bool			append;
	char			*file_in[MAX_INPUT_FILE];
	int				input_fd[MAX_INPUT_FILE + 1];
	int				std_in_fd;
} t_digest_conf;

void digest_init_conf(t_digest_args *args, t_digest_conf *conf);
void digest_parser(struct argp_state *state, enum COMMAND cmd);
void digest_print(t_digest_conf *args, u_int8_t *res, int index);

void hash_sha256(t_digest_conf *conf);

void md5(t_digest_conf *conf);

#endif
