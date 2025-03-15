#ifndef BASE64_H
# define BASE64_H

# include "../cipher.h"

# define BASE64_R_SIZE 48
# define SEND_SIZE BASE64_R_SIZE / 3 * 4
typedef struct s_base64_args {
    char *input_str;
    bool encode;
    char *infile;
    char *outfile;
} t_base64_args;

typedef struct s_base64_conf {
    int input;
    int fd_outfile;
} t_base64_conf;

void base64_init_conf(void *v_args, void *v_conf);
void base64_parser(int argc, char **argv, void *v_base64_args);
void base64_print(t_base64_conf *args, u_int8_t *res, int index);
void base64_helper( void );
void base64(void *v_conf);

#endif
