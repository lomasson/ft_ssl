#ifndef DES_H
# define DES_H
# include "commands.h"

#define ECB_PASSWORD_LEN 512
#define KEY_LEN 8
# define SALT_SIZE 8
#define PASSWORD_MESSGAE_DISPALY "enter DES-EBC encryption password: "
#define VERIFING_PASSWORD_MESSGAE_DISPALY "Verifying - enter DES-ECB encryption password: "



typedef struct s_des_args {
    char *input_str;
    bool encrypt;
    bool encode_b64;
    char *infile;
    char *outfile;
    uint8_t *key;
    char *password;
    char salt[SALT_SIZE];
    char *iv;
} t_des_args;

typedef struct s_des_conf {
    bool    encrypt;
    bool    encode_b64;
    int     fd_input;
    int     fd_output;
    uint8_t key[KEY_LEN];
    uint64_t key_56;
    char    *iv;
} t_des_conf;

void des_init_conf(void *v_args, void *v_conf);
void des_parser(int argc, char **argv, void *v_des_args);
void pbkdf_md5(char *password, char *salt, int dklen);
// void des_print(t_des_conf *args, u_int8_t *res, int index);
// void des_helper( void );


#endif