#include "md5.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

static void print_hash(u_int8_t *res)
{
	for(int i = 0; i < 16; ++i){
		printf("%02x", res[i]);
	}
}

void finalize(const t_md5_conf *args, u_int8_t *res, int index)
{
	if (args->reverse_mode && args->input_fd[index] != 3)
	{
		print_hash(res);
		printf(" %s\n", args->file_in[index]);
		return ;
	}
	printf("MD5(%s)= ", args->file_in[index]);
	print_hash(res);
	printf("\n");

}


