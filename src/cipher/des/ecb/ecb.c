#include "ecb.h"

#define ECB_READ_SIZE 8

// void feistel_process(uint64_t permuted, u_int64_t key_58)
// {
//   uint32_t L = ((uint32_t *)&permuted)[0];
//   uint32_t R = ((uint32_t *)&permuted)[1];
//   asm("ror");
// }

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

uint64_t first_permutation(uint64_t prev)
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
      permuted += ((prev >> index) & 0x1);
      permuted <<= 1;
      i++;
      if (index - 8 < 0)
        break ;
      index -= 8;
    }
  }
  return permuted;
}

void	ecb(void *v_conf)
{
	t_des_conf *conf = (t_des_conf *)v_conf;
  char  buffer[ECB_READ_SIZE + 1];
  char  buffer_permuted[ECB_READ_SIZE + 1];
  int rread = 1;
  int feistel_idx = 0;
  uint64_t permuted;

  delete_bit_of_parity(conf);
  // while (rread > 0)
  // {
    rread = read(conf->fd_input, buffer, ECB_READ_SIZE);
    buffer[rread] = '\0';
    permuted = first_permutation(__builtin_bswap64((uint64_t)*buffer));
    // for (feistel_idx = 0; feistel_idx < 16;feistel_idx++)
    //   feistel_process(permuted, conf->key_56);
  // }

  free(conf->iv);
  if (conf->fd_output != STDOUT_FILENO)
		close(conf->fd_output);
	if (conf->fd_input != STDIN_FILENO)
		close(conf->fd_input);
}