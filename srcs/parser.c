#include "../include/ft_ssl.h"

static struct argp_option main_options[] =
	{
		{ 0, 0, 0, 0, "md5", 0},
		{ 0, 0, 0, 0, "sha256", 0},
		{ 0 }
	};


static int parse_command(char *arg, struct argp_state *state){
	if (strcmp(arg, "md5") == 0)
	{
		digest_parser(state, MD5);
		return 0;
	}
	else if (strcmp(arg, "sha256") == 0)
	{
		digest_parser(state, SHA256);
		return 0;
	}
	return 1;
}

static int parse_opt(const int key, char *arg, struct argp_state *state)
{
	switch (key)
	{
		case ARGP_KEY_ARG:
			{
				if (!arg)
					break ;
				state->next -= 2;
				state->argv += state->next;
				state->argc -= state->next;
				if (parse_command(arg, state) == 1)
					return ARGP_ERR_UNKNOWN;
				return 1;
			}
	}
	return 0;
}

void ssl_parser(const int argc, char **argv, t_args *ssl_args) {
	memset(ssl_args, 0, sizeof(t_args));
	struct argp argp = { main_options, parse_opt, "md5\nsha256", 0, 0, 0, 0};
	if (argc <= 1 || argp_parse(&argp, argc, argv, ARGP_IN_ORDER, 0, ssl_args) == 0)
	{
		printf("usage: ft_ssl command [flags] [file/string]\n");
		exit(1);
	}

}
