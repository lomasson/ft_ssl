#ifndef DES_H
# define DES_H
# include "../../../include/commands.h"


typedef struct s_des_args {
    char *input_str;
    bool encrypt;
    bool encode_b64;
    char *infile;
    char *outfile;
    char *key;
    char *password;
    char *salt;
    char *iv;
} t_des_args;

typedef struct s_des_conf {
    bool encrypt;
    bool encode_b64;
    int fd_input;
    int fd_output;
    char *key;
    char *password;
    char *salt;
    char *iv;
} t_des_conf;

void des_init_conf(void *v_args, void *v_conf);
void des_parser(int argc, char **argv, void *v_des_args);
// void des_print(t_des_conf *args, u_int8_t *res, int index);
// void des_helper( void );


#endif