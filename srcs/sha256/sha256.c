#include "sha256.h"
#include <stdio.h>
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

	for(int i = 16; i < 64; i++)
	{
		u_int32_t s2 = SIG0(word->w[i - 15]);
		u_int32_t s3 = SIG1(word->w[i - 2]);
		word->w[i] = word->w[i - 16] + s2 + word->w[i - 7] + s3; 
	}
	for(int i = 0; i < 64; i++)
	{
		u_int32_t ep = EP0(e);
		u_int32_t rv_logic = CH(e, f, g);
		u_int32_t temp1 = h + ep+ rv_logic + konst[i] + word->w[i];
		rv_logic = MAJ(a, b, c);
		ep = EP1(a);
		u_int32_t temp2 = ep + rv_logic;
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

static	void convert_big_endian_msg(const t_sha_msg vars, t_sha_msg* res){
	for(unsigned int i = 0; i < 64; i++){
		res->w[i] = __builtin_bswap32(vars.w[i]);
	}
}

static	void convert_big_endian_hash(const t_sha_buf vars, u_int32_t* res){
	for(unsigned int i = 0; i < 8; i++){
		res[i] = __builtin_bswap32(vars.h[i]);
	}
}
void printBits(unsigned int num){
	unsigned int size = sizeof(unsigned int);
	unsigned int maxPow = 1<<(size*8-1);
	printf("MAX POW : %u\n",maxPow);
	unsigned int i=0;
	for(;i<size*8;++i){
		// print last bit and shift left.
		printf("%u ", !!(num&maxPow));
		num = num<<1;
	}
}
// Parse the fd and build a hash Message by Message (Message <= 512 bit) (Message = 16 word of 32bits)
static	void hash(const int fd, t_sha_buf *mdbuffer)
{
	t_sha_msg	buffer;
	uint64_t	total_read = 0;
	bool		bit_padding_ok = false;

	while (42)
	{
		memset(&buffer, 0, SHA256_BLOCK_LEN);
		// u_int32_t read_buffer = 0;
		// u_int8_t	mybuffer[64];
		// for(int i = 0; i < SHA256_BLOCK_LEN;i++)
		// {
		// 	read(fd, &(mybuffer[i]), 1);
		// }
		// printf("addr[0]: %p : %x\n", &mybuffer[0], mybuffer[0]);
		// printf("addr[1]: %p : %x\n", &mybuffer[1], mybuffer[1]);
		// printf("addr[2]: %p : %x\n", &mybuffer[2], mybuffer[2]);
		// printf("addr[3]: %p : %x\n", &mybuffer[3], mybuffer[3]);
		// printf("addr[4]: %p : %x\n", &mybuffer[4], mybuffer[4]);
		// printf("addr[5]: %p : %x\n", &mybuffer[5], mybuffer[5]);
		// printf("addr[6]: %p : %x\n", &mybuffer[6], mybuffer[6]);
		// printf("addr[7]: %p : %x\n", &mybuffer[7], mybuffer[7]);
		// printf("addr[8]: %p : %x\n", &mybuffer[8], mybuffer[8]);
		// printf("addr[9]: %p : %x\n", &mybuffer[9], mybuffer[9]);
		// printf("addr[10]: %p : %x\n", &mybuffer[10], mybuffer[10]);
		// printf("addr[11]: %p : %x\n", &mybuffer[11], mybuffer[11]);
		// printf("addr[12]: %p : %x\n", &mybuffer[12], mybuffer[12]);
		// printf("addr[13]: %p : %x\n", &mybuffer[13], mybuffer[13]);
		// printBits(*(unsigned int *)mybuffer);
		// printf("\n");
		// return ;
		u_int64_t read_buffer = read(fd, &buffer, SHA256_BLOCK_LEN);
		total_read += (read_buffer * 8);		// Convert the numbers of octets read and add to total numbers of bits read
												// If buffer read is > 56oct, we can't add padding (8oct) but make new bloc message and hash him.
												// Use result of sha256_hash to init next ABCD variables
		if (read_buffer != SHA256_BLOCK_LEN && !bit_padding_ok)
		{
			((u_int8_t *)&buffer.w)[read_buffer] = (char)128;  // add the last 1 bit at end of buffer (128 = 10000000)
			bit_padding_ok = true;
		}
		if (read_buffer == SHA256_BLOCK_LEN)
			sha256_hash(&buffer, mdbuffer);
		else if (read_buffer > SHA256_BLOCK_LEN_WITHOUT_PADDING)
		{
			convert_big_endian_msg(buffer, &buffer);
			sha256_hash(&buffer, mdbuffer);
		}
		else
		{
			// printf("\n*******************\n");
			// printBits(buffer.w[0]);
			// printf("\n*******************\n");
			// total_read = 4831838208;
			convert_big_endian_msg(buffer, &buffer);
			// printBits(buffer.w[0]);
			*(uint32_t *)&(buffer.w[14]) = ((u_int32_t *)&total_read)[1]; // add padding
			*(uint32_t *)&(buffer.w[15]) = ((u_int32_t *)&total_read)[0]; // add padding
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
void hash_sha256(t_sha256_conf *conf)
{
	int			i = 0;
	t_sha_buf	vars;
	u_int32_t	res[8];

	while (conf-> input_fd[i] >= 0)
	{
		memset(res, 0, 8 * sizeof(u_int32_t));
		init_mdbuffers(&vars);
		hash(conf->input_fd[i], &vars);
		close(conf->input_fd[i]);
		// convert_big_endian_hash(vars, res);
		// finalize(conf, res, i);
		print_hash((u_int32_t *)&vars);
		i++;
	}
}
