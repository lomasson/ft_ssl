#include "sha256.h"

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
	t_sha256_args *sha256_args = state->input;
	switch (key)
	{
		case 'p':
			{
				sha256_args->append = true;
				break;
			}
		case 'q':
			{
				sha256_args->quiet_mode = true;
				break;
 		}
		case 'r':
			{
				sha256_args->reverse_mode = true;
				break;
			}
		case 's':
			{
				sha256_args->str_in = arg; 
				break;
			}
		case ARGP_KEY_ARG:
			{
				if (state->arg_num < MAX_INPUT_FILE)
				{
					sha256_args->file_in[state->arg_num] = arg; 
					break;
				}
			return ARGP_ERR_UNKNOWN;
			}
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}


void sha256_parser(struct argp_state *state)
{
	((t_sha256_args *)state->input)->cmd = SHA256;
	struct argp argp = { options, parse_opt, "[files]", 0, 0, 0, 0};
	argp_parse(&argp, --state->argc, ++state->argv, 0, 0, state->input);
}
