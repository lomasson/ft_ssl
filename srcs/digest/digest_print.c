#include "digest.h"
static void print_hash(void *res, enum COMMAND cmd, int output_fd)
{
	if (cmd == MD5)
	{
		for(int i = 0; i < 16; ++i){
			dprintf(output_fd, "%02x", ((u_int8_t *)res)[i]);
		}
	}
	if (cmd == SHA256)
	{
		for(int i = 0; i < 8; ++i){
			dprintf(output_fd, "%02x", ((u_int32_t *)res)[i]);
		}
	}
}

void digest_print(t_digest_conf *args, u_int8_t *res, int index)
{
	char *cmd;

	switch (args->cmd)
	{
		case MD5:
			cmd = "MD5";
			break;
		case SHA256:
			cmd = "SHA256";
			break;
	}

	if (args->std_in_fd == args->input_fd[index])
	{
		if (args->append)
		{
			if (strlen(args->file_in[index]) >= 50)
				dprintf(args->output_fd, "%s(\"%s...\")= ", cmd, args->file_in[index]);
			else
				dprintf(args->output_fd, "%s(\"%s\")= ", cmd, args->file_in[index]);
		}
		else
			if (!args->quiet_mode)
				dprintf(args->output_fd, "(stdin)= ");
		free(args->file_in[index]);
	}
	else
	{
		if (!args->quiet_mode && !args->reverse_mode)
			dprintf(args->output_fd, "%s(%s)= ", cmd, args->file_in[index]);
		else if (!args->quiet_mode && args->reverse_mode)
		{
			print_hash(res, args->cmd, args->output_fd);
			dprintf(args->output_fd, " *%s\n", args->file_in[index]);
			return ;
		}
	}
	print_hash(res, args->cmd, args->output_fd);
	dprintf(args->output_fd, "\n");
	close(args->input_fd[index]);
}


void digest_helper( void )
{
	printf("\nMessage Digest commands:\n\nMD5\nSHA256\n\n");
}