#include "md5.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static void print_hash(u_int8_t *res)
{
	for(int i = 0; i < 16; ++i){
		printf("%02x", res[i]);
	}
}

void finalize_md5(t_md5_conf *args, u_int8_t *res, int index)
{
	// printf("fd: %s\n", args->file_in[index]);
	if (args->input_fd[index] == STDIN_FILENO)
	{
		if (args->append)
		{
			if (strlen(args->file_in[index]) >= 50)
				printf("MD5(%s...)= ", args->file_in[index]);
			else
				printf("MD5(%s)= ", args->file_in[index]);
		}
		else
			printf("MD5(stdin)= ");
		free(args->file_in[index]);
	}
	else
	{
		if (!args->quiet_mode && !args->reverse_mode)
			printf("MD5(%s)= ", args->file_in[index]);
		else if (!args->quiet_mode && args->reverse_mode)
		{
			print_hash(res);
			printf(" %s\n", args->file_in[index]);
			return ;
		}
	}
	print_hash(res);
	printf("\n");
	close(args->input_fd[index]);
}
