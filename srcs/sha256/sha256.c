#include "sha256.h"
#include <sys/types.h>

// sha256 Algorithm
static void sha256_hash(t_sha_msg *word, t_sha_buf *vars)
{
	u_int32_t	a = vars->h[0];
	u_int32_t	b = vars->h[1];
	u_int32_t	c = vars->h[2];
	u_int32_t	d = vars->h[3];
	u_int32_t	e = vars->h[4];
	u_int32_t	f = vars->h[5];
	u_int32_t	g = vars->h[6];
	u_int32_t	h = vars->h[7];
	u_int32_t	konst[64] = SHA_CONST_K;

	for(int i = 0; i < 64; i++)
	{
		u_int32_t s = SIG1(e);
		u_int32_t rv_logic = CH(e, f, g);
		u_int32_t temp1 = h + s + rv_logic + konst[i] + word->w[i];
		s = SIG0(a);
		rv_logic = MAJ(a, b, c);
		u_int32_t temp2 = s + rv_logic;
		h = g;
		g = f;
		f = e;
		e = d + temp1;
		d = c;
		c = b;
		b = a;
		a = temp1 + temp2;

	}
	vars->h[0] += a;
	vars->h[1] += b;
	vars->h[2] += c;
	vars->h[3] += d;
	vars->h[4] += e;
	vars->h[5] += f;
	vars->h[6] += g;
	vars->h[7] += h;
}

// Parse the fd and build a hash Message by Message (Message <= 512 bit) (Message = 16 word of 32bits)
static void hash(const int fd, t_sha_buf *mdbuffer)
{
	t_sha_msg	buffer;
	uint64_t	total_read = 0;
	bool		bit_padding_ok = false;

	while (42)
	{
		memset(&buffer, 0, SHA256_BLOCK_LEN);
		u_int64_t read_buffer = read(fd, &buffer, SHA256_BLOCK_LEN);
		total_read += (read_buffer * 8);		// Convert the numbers of octets read and add to total numbers of bits read
												// If buffer read is > 56oct, we can't add padding (8oct) but make new bloc message and hash him.
												// Use result of sha256_hash to init next ABCD variables
		if (read_buffer == SHA256_BLOCK_LEN)
			sha256_hash(&buffer, mdbuffer);
		else if (read_buffer > SHA256_BLOCK_LEN_WITHOUT_PADDING)
		{
			if (!bit_padding_ok)
				buffer.w[read_buffer] = (char)128;  // add the last 1 bit at end of buffer (128 = 10000000)
			bit_padding_ok = true;
			sha256_hash(&buffer, mdbuffer);
		}
		else
		{
			if (!bit_padding_ok)
				buffer.w[read_buffer] = (char)128;  // add the last 1 bit at end of buffer (128 = 10000000)
			bit_padding_ok = true;
			*(uint64_t *)&(buffer.w[56]) = (uint64_t)total_read; // add padding
			sha256_hash(&buffer, mdbuffer);
			return ;
		}
	}
}

static void init_mdbuffers(t_sha_buf *vars)
{
	*vars = (t_sha_buf){
		.h[0] = h0,
		.h[1] = h1,
		.h[2] = h2,
		.h[3] = h3,
		.h[4] = h4,
		.h[5] = h5,
		.h[6] = h6,
		.h[7] = h7,
	};
}

static void print_hash(u_int8_t *res)
{
	for(int i = 0; i < 32; ++i){
		printf("%02x", res[i]);
	}
}

// static void convert_big_endian(const t_sha_buf *vars, u_int8_t *res){
// 	for(unsigned int i = 0; i < 8; ++i){
// 		res[(i * 4) + 0] = (uint8_t)(((u_int32_t *)vars)[i] & 0x000000FF);
// 		res[(i * 4) + 1] = (uint8_t)((((u_int32_t *)vars)[i] & 0x0000FF00) >>  8);
// 		res[(i * 4) + 2] = (uint8_t)((((u_int32_t *)vars)[i] & 0x00FF0000) >> 16);
// 		res[(i * 4) + 3] = (uint8_t)((((u_int32_t *)vars)[i] & 0xFF000000) >> 24);
// 	}
// }

void hash_sha256(t_sha256_conf *conf)
{
	int			i = 0;
	t_sha_buf	vars;
	u_int8_t	res[32];

	while (conf-> input_fd[i] >= 0)
	{
		memset(res, 0, 32);
		init_mdbuffers(&vars);
		hash(conf->input_fd[i], &vars);
		close(conf->input_fd[i]);
		// convert_big_endian(&vars, res);
		// finalize(conf, res, i);
		print_hash((u_int8_t *)&vars);
		i++;
	}
}
