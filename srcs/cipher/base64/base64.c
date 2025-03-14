#include "base64.h"

#define BASE64_R_SIZE 1024

void base64(void *v_conf)
{
    int rread = BASE64_R_SIZE;
    char buffer[BASE64_R_SIZE + 1];
    t_base64_conf *conf = (t_base64_conf *)v_conf;
    unsigned char saved = 0;
    unsigned char oc;
    int i = 0;
    
    
    while (rread == BASE64_R_SIZE)
    {
        printf("on est la\n");
        rread = read(conf->input, buffer, BASE64_R_SIZE);
        printf("on est la 2\n");
        memset(&(buffer[rread]), 0, BASE64_R_SIZE - rread);
        while (buffer[i])
        {
            if(saved != 0)
            {
                oc = saved << (4 - ((i - 1) % 2));
                saved = 0;
            }
            saved = buffer[i] % (4 * (4 * (i % 3)));
            oc += buffer[i] >> 2 * (i % 3);
            write(conf->fd_outfile, &oc, 1);
            if (i % 3 == 2)
            {
                oc = buffer[i] % 64;
                write(conf->fd_outfile, &oc, 1);
            }
            i++;
            printf("i: %d\n",i);
            oc = 0;
        }
    }
}