#include "sha256.h"
static void print_hash(const u_int32_t *res)
{
	for(int i = 0; i < 8; ++i){
		printf("%08x", res[i]);
	}
}

void finalize_sha256(const t_sha256_conf *args, const u_int32_t *res, const int index)
{
	// printf("fd: %s\n", args->file_in[index]);
	if (args->input_fd[index] == STDIN_FILENO)
	{
		if (args->append)
		{
			if (strlen(args->file_in[index]) >= 50)
				printf("SHA2-256(%s...)= ", args->file_in[index]);
			else
				printf("SHA2-256(%s)= ", args->file_in[index]);
		}
		else
			printf("SHA2-256(stdin)= ");
		free(args->file_in[index]);
	}
	else
	{
		if (!args->quiet_mode && !args->reverse_mode)
			printf("SHA2-256(%s)= ", args->file_in[index]);
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
