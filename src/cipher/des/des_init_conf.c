#include "des.h"

static void handle_error(const char *msg)
{
    perror(msg);
    exit(1);
}

static char *get_password_from_stdin( char *salt)
{
    char *password;
    char *verif_password;
    int rread;
    
    password = getpass(PASSWORD_MESSGAE_DISPALY);
    rread = strlen(password);

    if (rread >= ECB_PASSWORD_LEN || rread <= 0)
        handle_error("bad password read");
    verif_password = getpass(VERIFING_PASSWORD_MESSGAE_DISPALY);
    rread = strlen(password);
    if (rread >= ECB_PASSWORD_LEN || rread <= 0)
        handle_error("bad password read");

    if (strcmp(password, verif_password) != 0)
        handle_error("bad password read");
    verif_password = calloc(rread + SALT_SIZE + 1, 1);
    strncpy(verif_password, password, rread );
    strncpy(verif_password + rread, salt, SALT_SIZE);
    verif_password[rread + SALT_SIZE] = '\0';
    return(verif_password);
}

static int get_hex_value(char c)
{
    if (c >= 'A' && c <= 'F')
        return (c - 'A' + 10);
    else if (c >= 'a' && c <= 'f')
        return (c - 'a' + 10);
    else if (c >= '0' && c <= '9')
        return (c - '0');
    return (0);
}

static void convert_hexa(unsigned char *brut_salt, char *dest_salt)
{
    for (int i = 0; i < SALT_SIZE * 2; i += 2)
        dest_salt[i / 2] = (get_hex_value(brut_salt[i])*16) + get_hex_value(brut_salt[i + 1]);
}

static void generate_key(t_des_args *args)
{
    char salt[SALT_SIZE];

    memset(salt, 0, SALT_SIZE);
    convert_hexa((unsigned char *)args->salt, salt);
    if (!args->password)
        args->password = get_password_from_stdin(salt);
    pbkdf_md5(args->password, salt, strlen(args->password) + SALT_SIZE);
}


void des_init_conf(void *v_args, void *v_conf)
{
    t_des_args *args = (t_des_args *)v_args;
	t_des_conf *conf = (t_des_conf *)v_conf;
    
    if (!args->key)
    {
        generate_key(args);
        strncpy(conf->key, (uint8_t *)args->password, KEY_LEN);
    }
    else
        for (int i = 0; i < KEY_LEN * 2; i += 2)
            conf->key[i / 2] = (get_hex_value(args->key[i])*16) + get_hex_value(args->key[i + 1]);
    if (args->infile)
    {
        conf->fd_input = open(args->infile, O_RDONLY, 0);
        if (conf->fd_input < 0)
            handle_error("input file opening");
        free(args->infile);
    }
    else
        conf->fd_input = STDIN_FILENO;
    if (args->outfile)
    {
        conf->fd_output = open(args->outfile, O_RDWR | O_CREAT | O_TRUNC , 0666);
        if (conf->fd_output < 0)
            handle_error("output file opening");
        free(args->outfile);
    }
    else
        conf->fd_output = STDOUT_FILENO;
}
