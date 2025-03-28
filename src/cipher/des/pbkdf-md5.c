#include "des.h"
#include "../../digest/md5/md5.h"

#define ITER_PASSWORD 1000

void pbkdf_md5(char *password, char *salt, int dklen)
{
    int fd1 = fileno(tmpfile());
    t_buffers	vars;
    u_int8_t	res[16];

    write(fd1, password, dklen);
    lseek(fd1, 0, SEEK_SET);
	memset(res, 0, 16);
	init_mdbuffers(&vars);
	hash(fd1, &vars);
	convert_big_endian(&vars, res);
    printf("salt=");
    for(int i = 0; i < 8; ++i){
        printf("%02X", ((u_int8_t *)salt)[i]);
    }
    printf("\nkey=");
    for(int i = 0; i < 8; ++i){
        printf("%02X", ((u_int8_t *)res)[i]);
    }
    printf("\n");
    memset(password, 0, dklen - 8);
    strncpy(password, res, 8);
}
