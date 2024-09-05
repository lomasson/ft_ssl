#ifndef COMMANDS_H
# define COMMANDS_H
# include <stdbool.h>
# include <argp.h>
# include <stdint.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

// # include <getopt.h>

enum COMMAND {
	MD5,
	SHA256
};

#endif
