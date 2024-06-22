#include "md5.h"
// #include <cstdio>
// #include <cstdio>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// Parse the fd and build a chainned list of Message (=512 bit)
static void	read_input(int fd, t_md5 *md5)
{
	t_M			buffer;
	u_int64_t	total_read = 0;

	memset(&buffer, 0, MD5_BLOCK_LENGHT);
	while (42)
	{
		md5->next = NULL;
		int read_buffer = read(fd, (char *)&buffer, MD5_BLOCK_LENGHT);
		if (read_buffer == 0)
				return ;
		total_read += (read_buffer * 8);		// Convert the numbers of octets read and add to total numbers of bits read
		memcpy(&md5->M, &buffer, 64);
		if (read_buffer > MD5_BLOCK_LENGHT_WIHOUT_PADDING)
		{
			md5->next = malloc(sizeof(t_md5));
			md5 = md5->next;
		}
		else if (read_buffer <= MD5_BLOCK_LENGHT_WIHOUT_PADDING)
		{
			((char *)(&md5->M.w0))[read_buffer] = (char)128;  // add the last 1 bit at end of buffer
			md5->M.w14 = total_read >> MD5_WORD_LEN;
			md5->M.w15 = total_read;
			return;
		}
	}
}

static void md5_hash(t_md5 *md5, char *hash)
{
	while(md5)
	{
		md5 = md5->next;
	}
}


static void algo(t_md5_conf *conf, int fd)
{
	(void)conf;
	char			hash[MD5_HASH_LEN];
	t_md5			*md5 = malloc(sizeof(t_md5));
	unsigned char	buffer[MD5_BLOCK_LENGHT];

	memset(buffer, 0, MD5_BLOCK_LENGHT);
	memset(hash, 0, MD5_HASH_LEN);
	memset(md5, 0, sizeof(t_md5));
	read_input(fd, md5);
	md5_hash(md5, hash);
	printf("THE HASH: %s\n", hash);
}

void md5(t_md5_conf *conf)
{
	t_md5 *md5;

	md5 = malloc(sizeof(t_md5));
	memset(md5, 0, sizeof(t_md5));
	printf("nb fd %d\n", *conf->file_in);
	int i = 0;
	while (conf->file_in[i] >= 0)
	{
		algo(conf, conf->file_in[i]);
		i++;
	}
}
