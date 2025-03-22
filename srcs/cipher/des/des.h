#ifndef DES_H
# define DES_H

# include "../cipher.h"


typedef struct s_des_args {
    char *input_str;
    bool encode;
    char *infile;
    char *outfile;
} t_des_args;

typedef struct s_des_conf {
    int input;
    int fd_outfile;
} t_des_conf;

void des_init_conf(void *v_args, void *v_conf);
void des_parser(int argc, char **argv, void *v_des_args);
void des_print(t_des_conf *args, u_int8_t *res, int index);
void des_helper( void );
void des(void *v_conf);


#endif