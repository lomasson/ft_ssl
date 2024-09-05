#include "digest.h"

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
	t_digest_args *digest_args = state->input;
	switch (key)
	{
		case 'p':
			{
				digest_args->append = true;
				break;
			}
		case 'q':
			{
				digest_args->quiet_mode = true;
				break;
			}
		case 'r':
			{
				digest_args->reverse_mode = true;
				break;
			}
		case 's':
			{
				digest_args->str_in = arg; 
				break;
			}
		case ARGP_KEY_ARG:
			{
				if(state->arg_num < MAX_INPUT_FILE)
				{
					digest_args->file_in[state->arg_num] = arg; 
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


void digest_parser(struct argp_state *state, enum COMMAND cmd)
{
	((t_digest_args *)state->input)->cmd = cmd;
	struct argp argp = { options, parse_opt, "[files]", 0, 0, 0, 0};
	argp_parse(&argp, --state->argc, ++state->argv, 0, 0, state->input);
}
