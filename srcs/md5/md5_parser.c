#include "md5.h"
#include <string.h>

static struct argp_option options[] =
{
	{ 0, 'p', 0, 0, "Echo STDIN to STDOUT and append the checksum to STDOUT", 0},
	{ 0, 'q', 0, 0, "Quiet mode", 0},
	{ 0, 'r', 0, 0, "Reverse the format of the output", 0},
	{ 0, 's', "String", 0, "Print the sum of the given string", 0},
	{ 0 }
};

static int parse_opt(int key, char *arg, struct argp_state *state)
{
	t_md5_args *md5_args = state->input;
	switch (key)
	{
		case 'p':
			{
				md5_args->append = true;
				break;
			}
		case 'q':
			{
				md5_args->quiet_mode = true;
				break;
			}
		case 'r':
			{
				md5_args->reverse_mode = true;
				break;
			}
		case 's':
			{
				md5_args->str_in = arg; 
				break;
			}
		case ARGP_KEY_ARG:
			{
				if(state->arg_num < MAX_INPUT_FILE)
				{
					md5_args->file_in[state->arg_num] = arg; 
					break;
				}
				return ARGP_ERR_UNKNOWN;
			}
		default:
			{
				return ARGP_ERR_UNKNOWN;
			}
	}
	return 0;
}


void md5_parser(struct argp_state *state)
{
	((t_md5_args *)state->input)->cmd = MD5;
	struct argp argp = { options, parse_opt, "[files]", 0, 0, 0, 0};
	argp_parse(&argp, --state->argc, ++state->argv, 0, 0, state->input);
}
