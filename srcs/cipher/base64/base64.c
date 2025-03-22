#include "base64.h"

static char	get_char_encoded(const uint8_t oc)
{
	if (oc == 63)
		return '/';
	if (oc == 62)
		return '+';
	if (oc >= 52)
		return '0' + oc - 52;
	if (oc >= 26)
		return ('a' + oc - 26);
	return ('A' + oc);
}

static char	get_decoded_char(const uint8_t oc)
{
	if (oc == '=')
		return 0;
	if (oc == '/')
		return 63;
	if (oc <= 'Z' && oc >= 'A')
		return (oc - 'A');
	if (oc <= 'z'&& oc >= 'a')
		return (oc - 'a' + 26);
	if (oc <= '9' && oc >= '0')
		return (oc - '0' + 52);
	
	return 62;
}

static int	bytes_encode_process(const uint8_t *decoded, uint8_t *oc, const int i)
{
	if (i <= 0)
		return (1);
	oc[0] = get_char_encoded(decoded[0] >> 2);
	oc[1] = (decoded[0] & 0x3) << 4;
	if (i == 1)
	{
		oc[1] = get_char_encoded(oc[1]);
		oc[2] = '=';
		oc[3] = '=';
		return (1);
	}
	oc[1] = get_char_encoded(oc[1] + (decoded[1] >> 4));
	oc[2] = (decoded[1] & 0xF) << 2;
	if (i == 2)
	{
		oc[2] = get_char_encoded(oc[2]);
		oc[3] = '=';
		return (2);
	}
	oc[2] = get_char_encoded(oc[2] + (decoded[2] >> 6));
	oc[3] = get_char_encoded(decoded[2] & 0x3F);
	return (3);
}

static int bytes_decode_process( const uint8_t *encoded, uint8_t *oc)
{
	oc[0] = get_decoded_char(encoded[0]) << 2;
	if (!encoded[1])
		return 1;
	oc[0] += (get_decoded_char(encoded[1]) & 0x30) >> 4;
	oc[1] = (get_decoded_char(encoded[1]) & 0xf) << 4;
	if (!encoded[2])
		return 2;
	oc[1] += (get_decoded_char(encoded[2])& 0x3c )>> 2;
	oc[2] = (get_decoded_char(encoded[2]) & 0x3) << 6;
	if (!encoded[3])
		return 3;
	oc[2] += get_decoded_char(encoded[3]);
	return 4;
}

void	base64(void *v_conf)
{
	int rread;
	uint8_t decoded[DECODED_BUFFER_SIZE + 1];
	uint8_t encoded[ENCODED_BUFFER_SIZE + 1];
	t_base64_conf *conf = (t_base64_conf *)v_conf;
	int i;

	if (conf->encode) //encode
	{
		rread = DECODED_BUFFER_SIZE;
		while (rread == DECODED_BUFFER_SIZE)
		{
			i = 0;
			rread = read(conf->input, decoded, DECODED_BUFFER_SIZE);
			if (rread <= 0)
				return ;
			decoded[rread] = '\0';
			while (i < rread)
				i += bytes_encode_process(&(decoded[i]), &encoded[i/3*4], rread - i);
			write(conf->fd_outfile, encoded, (rread / 3 * 4) + (rread % 3 == 0? 0:4));
			write(conf->fd_outfile, "\n", 1);
		}
	}
	else //decode
	{
		rread = ENCODED_BUFFER_SIZE;
		while (rread == ENCODED_BUFFER_SIZE)
		{
			i = 0;
			rread = read(conf->input, encoded, ENCODED_BUFFER_SIZE + 1);
			if (rread <= 0)
				return ;
			if (encoded[rread - 1] == '\n')
				rread--;
			encoded[rread] = '\0';
			while ((i % 4 == 0 || i == 0) && encoded[i])
				i += bytes_decode_process(&(encoded[i]), &decoded[i/4*3]);
			if (i % 4 != 0)
				return ;
			write(conf->fd_outfile, decoded, (rread / 4 * 3) + (rread % 4 == 0? 0:3));
		}
	}
	if (conf->fd_outfile != STDOUT_FILENO)
		close(conf->fd_outfile);
}
