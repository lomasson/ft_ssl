#include "base64.h"

u_int8_t	get_char_encoded(uint8_t oc)
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

int	bytes_process(uint8_t *array, uint8_t *oc)
{
	if (!array[0])
		return (1);
	oc[0] = get_char_encoded(array[0] >> 2);
	oc[1] = (array[0] % 4) << 4;
	if (!array[1])
	{
		oc[1] = get_char_encoded(oc[1]);
		oc[2] = '=';
		oc[3] = '=';
		return (1);
	}
	oc[1] = get_char_encoded(oc[1] + (array[1] >> 4));
	oc[2] = (array[1] % 16) << 2;
	if (!array[2])
	{
		oc[2] = get_char_encoded(oc[2]);
		oc[3] = '=';
		return (2);
	}
	oc[2] = get_char_encoded(oc[2] + (array[2] >> 6));
	oc[3] = get_char_encoded(array[2] % 64);
	return (3);
}

void	base64(void *v_conf)
{
	int rread = BASE64_R_SIZE;
	uint8_t buffer[BASE64_R_SIZE + 1];
	uint8_t to_send[SEND_SIZE + 1];
	t_base64_conf *conf = (t_base64_conf *)v_conf;
	int i;

	while (rread == BASE64_R_SIZE)
	{
		i = 0;
		rread = read(conf->input, buffer, BASE64_R_SIZE);
		if (rread <= 0)
			return ;
		buffer[rread] = '\0';
		while (i % 3 == 0 || i == 0)
			i += bytes_process(&(buffer[i]), &to_send[i/3*4]);
		to_send[(rread / 3 * 4) + (rread % 3 == 0? 0:4)] = '\0';
		printf("%s\n", to_send);
	}
}
