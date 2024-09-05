#ifndef SHA256_H
# define SHA256_H
# include <sys/types.h>

# define MAX_INPUT_FILE 8
# define SHA256_BLOCK_LEN 64
# define SHA256_BLOCK_LEN_WITHOUT_PADDING 56
# define h0 0x6a09e667
# define h1 0xbb67ae85
# define h2 0x3c6ef372
# define h3 0xa54ff53a
# define h4 0x510e527f
# define h5 0x9b05688c
# define h6 0x1f83d9ab
# define h7 0x5be0cd19

# define ROTATE_RIGHT(x, n) (((x) >> (n)) | ((x) << (32-(n))))

# define CH(x, y, z) (x & y) ^ (~x & z)
# define MAJ(x, y, z) (x & y) ^ (x & z) ^ (y & z)


# define SIG0(x) (ROTATE_RIGHT(x, 7) ^ ROTATE_RIGHT(x, 18) ^ (x >> 3))
# define SIG1(x) (ROTATE_RIGHT(x, 17) ^ ROTATE_RIGHT(x, 19) ^ (x >> 10))

# define EP0(x) ROTATE_RIGHT(x, 6) ^ ROTATE_RIGHT(x, 11) ^ ROTATE_RIGHT(x, 25)
# define EP1(x) ROTATE_RIGHT(x, 2) ^ ROTATE_RIGHT(x, 13) ^ ROTATE_RIGHT(x, 22)

# define SHA_CONST_K { \
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, \
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, \
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, \
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, \
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, \
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, \
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, \
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 \
}

typedef struct s_sha_buff {
	u_int32_t h[8];
} t_sha_buf;

typedef struct s_sha_msg {
	u_int32_t w[64];
} t_sha_msg;


#endif
