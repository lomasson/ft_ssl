#include "des.h"

static int parse_opt(int key, char *arg, struct argp_state *state)
{
	t_des_args *des_args = state->input;
	switch (key)
	{
		case 'd':
			{
				des_args->encode = false;
				break;
			}
		case 'e':
			{
				des_args->encode = true;
				break;
			}
		case 'i':
			{
				des_args->infile = strdup(arg);
				break;
			}
		case 'o':
			{
				des_args->outfile = strdup(arg);
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

void des_parser(int argc, char **argv, void *v_des_args)
{
	t_des_args *des_args = (t_des_args *)v_des_args;
	static struct argp_option options[] =
	{
		{ 0, 'd', 0, 0, "decode mode", 0},
		{ 0, 'e', 0, 0, "encode mode (default)", 0},
		{ 0, 'i', "String", 0, "input file", 0},
		{ 0, 'o', 0, 0, "output file", 0},
		{ 0 }
	};
	memset(des_args, 0, sizeof(t_des_args));
	struct argp argp = { options, parse_opt, 0, 0, 0, 0, 0};
	argp_parse(&argp, argc, argv, ARGP_IN_ORDER, 0, des_args);
}
