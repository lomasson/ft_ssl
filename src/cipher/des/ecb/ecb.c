#include "ecb.h"

static uint64_t expension_block(uint32_t to_expend)
{
  u_int64_t ret;
  int i = 0;
  int j = 1;

  ret = to_expend & 0x1;
  // printf("1 <- 32 (%ld)\n", ret);
  while (j < 47)
  {
    ret <<= 1;
    ret |= ((to_expend >> (31 - i)) & 0x1);

    // printf("%d <- %d (%d)\n",j + 1, i + 1, ((to_expend >> (31 - i)) & 0x1));
    j++;
    i++;
    if (j % 6 == 0)
      i-=2;
  }
  ret <<= 1;
  ret |= (to_expend >> 31) & 0x1;
  // printf("48 <- 1\n");
  // ret <<=16;
  // printf("permuted: 0x%08lX\n", ret);
  return (ret);
}

static void feistel_process(uint64_t permuted, u_int64_t key, const int consts_sboxes[4][16])
{
  uint64_t R_extended = expension_block(((uint32_t *)&permuted)[0]) ^ key;
  u_int8_t part;
  int col;
  int row;
  printf("permuted: 0x%08lX\n", R_extended);
  for (int i = 0; i < 6;i++)
  {
      part = R_extended >> (58 - (6 * i)) & 0x3f;
      printf("6bit: %02x\n", part);
      row = (part >> 4 & 0x2) | (part & 0x1);
      col = (part & 0x1e) >> 1;
      printf("%d. col: %d, row: %d = %d\n", i, col, row, consts_sboxes[row][col]);
  }
  ((uint32_t *)&permuted)[0] = ((uint32_t *)&R_extended)[0];
}

static void delete_bit_of_parity(t_des_conf *conf)
{
  conf->key_56 = 0;

  for (int i = 0; i < KEY_LEN - 1;i++ )
  {
    *(uint8_t *)&conf->key_56 |= conf->key[i];
    conf->key_56 <<= 7;
  }
  conf->key_56 >>= 8;
}

static uint64_t first_permutation(uint64_t prev)
{
  uint64_t permuted;
  int i = 0;
  int index = 0;

  while (i < 64)
  {
    index = abs(index) + 58;
    if (i == 32)
      index--;
    while (index > 0)
    {
      // printf("%d <- %d\n", i + 1, index);
      permuted |= ((prev >> (64 - index)) & 0x1);
      permuted <<= 1;
      i++;
      if (index - 8 < 0)
        break ;
      index -= 8;
    }
  }
  return permuted;
}

static uint64_t rotate_feistel_key(uint64_t *key_56, const int rot_idx, const int pc2_permutation[48])
{
  uint64_t ret;
  uint32_t L = *key_56 >> 36;
  uint32_t R = (*key_56 >> 4) & 0xffffff0;

  *key_56 = (((L >> (28 - rot_idx)) | (L << rot_idx)));
  *key_56 <<= 36;
  *key_56 |= (R >> (28 - rot_idx)) | (R << rot_idx);

  for(int i = 0; i < 48; i++)
  {
    ret |= ((*key_56 >> pc2_permutation[i]) & 0x1);
    ret <<= 1;
  }
  ret <<=16;
  printf("subkey: %08lX\n", ret);
  return (ret);
}

void	ecb(void *v_conf)
{
	t_des_conf *conf = (t_des_conf *)v_conf;
  char  buffer[ECB_READ_SIZE + 1];
  char  buffer_permuted[ECB_READ_SIZE + 1];
  int rread = 1;
  int feistel_idx = 0;
  uint64_t permuted;
  const int ecb_feistel_const[16] = RTOTATE_FEISTEL_SUB_KEY;
  const int consts_pc2_permutations[48] = PC2_PERMUTATION;
  const int consts_sboxes[8][4][16] = S_BOXES;

  delete_bit_of_parity(conf);
  
  buffer[ECB_READ_SIZE] = '\0';
  // while (rread > 0)
  // {
    memset(buffer, 0x8, ECB_READ_SIZE);
    rread = read(conf->fd_input, buffer, ECB_READ_SIZE);
    permuted = first_permutation(__builtin_bswap64((uint64_t)*buffer));
    // for (feistel_idx = 0; feistel_idx < 16;feistel_idx++)
    // {
      uint64_t subkey =  rotate_feistel_key(&conf->key_56, ecb_feistel_const[0], consts_pc2_permutations);
      feistel_process(permuted, subkey, consts_sboxes);
    // }
  // }
  free(conf->iv);
  if (conf->fd_output != STDOUT_FILENO)
		close(conf->fd_output);
	if (conf->fd_input != STDIN_FILENO)
		close(conf->fd_input);
}