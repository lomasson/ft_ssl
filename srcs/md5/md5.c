#include "md5.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// MD5 Algorithm
static void md5_hash(t_Message *word, t_buffers *vars)
{
	u_int32_t	A = vars->A;
	u_int32_t	B = vars->B;
	u_int32_t	C = vars->C;
	u_int32_t	D = vars->D;
	u_int32_t	F = 0x0;
	u_int32_t	G = 0;
	u_int32_t	Konst[64] = CONST_K;
	u_int8_t	Shift[64] = CONST_S;

	for(int i = 0; i < 64; i++)
	{
		if (i < 16)
		{
			F = F(B, C, D);
			G = i;
		}
		else if (i < 32)
		{
			F = G(B, C, D);
			G = (5 * i + 1) % 16;
		}
		else if (i < 48)
		{
			F = H(B, C, D);
			G = (3 * i + 5) % 16;
		}
		else
		{
			F = I(B, C, D);
			G  = (7 * i) % 16;
		}
		A += F + Konst[i] + ((u_int32_t *)word)[G];
		A = ROTATE_LEFT(A, Shift[i]);
		A += B;

		u_int32_t Temp_d = D;
		D = C;
		C = B;
		B = A;
		A = Temp_d;
	}
	vars->A += A;
	vars->B += B;
	vars->C += C;
	vars->D += D;
}

/* Encodes input (UINT4) into output (unsigned char). Assumes len is
   a multiple of 4 and print him.
   */
static void convert_big_endian(const t_buffers *vars, u_int8_t *res){

	for(unsigned int i = 0; i < 4; ++i){
		res[(i * 4) + 0] = (uint8_t)(((u_int32_t *)vars)[i] & 0x000000FF);
		res[(i * 4) + 1] = (uint8_t)((((u_int32_t *)vars)[i] & 0x0000FF00) >>  8);
		res[(i * 4) + 2] = (uint8_t)((((u_int32_t *)vars)[i] & 0x00FF0000) >> 16);
		res[(i * 4) + 3] = (uint8_t)((((u_int32_t *)vars)[i] & 0xFF000000) >> 24);
	}
}


// Parse the fd and build a hash Message by Message (Message <= 512 bit) (Message = 16 word of 32bits)
static void hash(const int fd, t_buffers *mdbuffer)
{
	t_Message	buffer;
	uint64_t	total_read = 0;
	bool		bit_padding_ok = false;

	while (42)
	{
		memset(&buffer, 0, MD5_BLOCK_LEN);
		u_int64_t read_buffer = read(fd, &buffer, MD5_BLOCK_LEN);
		total_read += (read_buffer * 8);		// Convert the numbers of octets read and add to total numbers of bits read
												// If buffer read is > 56oct, we can't add padding (8oct) but make new bloc message and hash him.
												// Use result of md5_hash to init next ABCD variables
		if (read_buffer == MD5_BLOCK_LEN)
			md5_hash(&buffer, mdbuffer);
		else if (read_buffer > MD5_BLOCK_LEN_WIHOUT_PADDING)
		{
			if (!bit_padding_ok)
				buffer.w[read_buffer] = (char)128;  // add the last 1 bit at end of buffer (128 = 10000000)
			bit_padding_ok = true;
			md5_hash(&buffer, mdbuffer);
		}
		else
		{
			if (!bit_padding_ok)
				buffer.w[read_buffer] = (char)128;  // add the last 1 bit at end of buffer (128 = 10000000)
			bit_padding_ok = true;
			*(uint64_t *)&(buffer.w[56]) = (uint64_t)total_read; // add padding
			md5_hash(&buffer, mdbuffer);
			return ;
		}
	}
}

static void init_mdbuffers(t_buffers *vars)
{
	vars->A = INIT_A;
	vars->B = INIT_B;
	vars->C = INIT_C;
	vars->D = INIT_D;
}

void md5(t_md5_conf *conf)
{
	int			i = 0;
	t_buffers	vars;
	u_int8_t	res[16];

	while (conf-> input_fd[i] >= 0)
	{
		memset(res, 0, 16);
		init_mdbuffers(&vars);
		hash(conf->input_fd[i], &vars);
		close(conf->input_fd[i]);
		convert_big_endian(&vars, res);
		finalize(conf, res, i);
		i++;
	}
}
