#include "base64.h"

static int parse_opt(int key, char *arg, struct argp_state *state)
{
	t_base64_args *base64_args = state->input;
	switch (key)
	{
		case 'd':
			{
				base64_args->encode = false;
				break;
			}
		case 'e':
			{
				base64_args->encode = true;
				break;
			}
		case 'i':
			{
				base64_args->infile = strdup(arg);
				break;
			}
		case 'o':
			{
				base64_args->outfile = strdup(arg);
				break;
			}
		case ARGP_KEY_ARG:
			{
				return ARGP_ERR_UNKNOWN;
			}
		default:
			{
				return 0;
			}
	}
	return 0;
}

void base64_parser(int argc, char **argv, void *v_base64_args)
{
	t_base64_args *base64_args = (t_base64_args *)v_base64_args;
	static struct argp_option options[] =
	{
		{ 0, 'd', 0, 0, "decode mode", 0},
		{ 0, 'e', 0, 0, "encode mode (default)", 0},
		{ 0, 'i', "String", 0, "input file", 0},
		{ 0, 'o', 0, 0, "output file", 0},
		{ 0 }
	};
	memset(base64_args, 0, sizeof(t_base64_args));
	struct argp argp = { options, parse_opt, 0, 0, 0, 0, 0};
	argp_parse(&argp, argc, argv, ARGP_IN_ORDER, 0, base64_args);
}
