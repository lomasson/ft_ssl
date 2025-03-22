#include "des.h"

static int parse_opt(int key, char *arg, struct argp_state *state)
{
	t_des_args *des_args = state->input;
	switch (key)
	{
		case 'a':
			{
				des_args->encode_b64 = true;
				break;
			}
		case 'd':
			{
				des_args->encrypt = false;
				break;
			}
		case 'e':
			{
				des_args->encrypt = true;
				break;
			}
		case 'i':
			{
				des_args->infile = strdup(arg);
				break;
			}
		case 'k':
			{
				des_args->key = strdup(arg);
				break;
			}
		case 'o':
			{
				des_args->outfile = strdup(arg);
				break;
			}
		case 'p':
			{
				des_args->password = strdup(arg);
				break;
			}
		case 's':
			{
				des_args->salt = strdup(arg);
				break;
			}
		case 'v':
			{
				des_args->iv = strdup(arg);
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
		{ 0, 'a', 0, 0, "Base64 encode/decode, depending on encryption flag", 0},
		{ 0, 'd', 0, 0, "Decrypt", 0},
		{ 0, 'e', 0, 0, "Encrypt (default)", 0},
		{ 0, 'i', "infile", 0, "Input file", 0},
		{ 0, 'k', "val", 0, "Passphrase", 0},
		{ 0, 'o', "outfile", 0, "Output file", 0},
		{ 0, 'p', "val", 0, "Passphrase source", 0},
		{ 0, 's', "val", 0, "Salt, in hex", 0},
		{ 0, 'v', "val", 0, "IV in hex", 0},
		{ 0 }
	};
	memset(des_args, 0, sizeof(t_des_args));
	des_args->encrypt = true;
	struct argp argp = { options, parse_opt, 0, 0, 0, 0, 0};
	argp_parse(&argp, argc, argv, ARGP_IN_ORDER, 0, des_args);
}
