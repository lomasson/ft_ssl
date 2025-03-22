#ifndef BASE64_H
# define BASE64_H

# include "../cipher.h"

# define DECODED_BUFFER_SIZE 48
# define ENCODED_BUFFER_SIZE DECODED_BUFFER_SIZE / 3 * 4

typedef struct uint24_t
{
    uint8_t a[3];
} uint24_t;

typedef struct s_base64_args {
    char *input_str;
    bool encode;
    char *infile;
    char *outfile;
} t_base64_args;

typedef struct s_base64_conf {
    int input;
    bool encode;
    int fd_outfile;
} t_base64_conf;

void base64_init_conf(void *v_args, void *v_conf);
void base64_parser(int argc, char **argv, void *v_base64_args);
void base64_print(t_base64_conf *args, u_int8_t *res, int index);
void base64_helper( void );
void base64(void *v_conf);

#endif
