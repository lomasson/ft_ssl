# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lomasson <lomasson@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 13:27:28 by lomasson          #+#    #+#              #
#    Updated: 2023/03/24 13:18:22 by lomasson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM					= rm -rf
CC					= gcc

CFLAGS				= -Wall -Wextra -Werror -g3  -I include# -fsanitize=address

NAME				= ft_ssl

SRCS = srcs/main.c \
	srcs/digest/digest_parser.c \
	srcs/digest/digest_init_conf.c \
	srcs/digest/digest_print.c \
	srcs/digest/md5/md5.c \
	srcs/digest/sha256/sha256.c \
	srcs/cipher/base64/base64_init_conf.c \
	srcs/cipher/base64/base64_parser.c \
	srcs/cipher/base64/base64_print.c \
	srcs/cipher/base64/base64.c \
	srcs/cipher/des/des_init_conf.c \
	srcs/cipher/des/des_parser.c \
	srcs/cipher/des/ecb/ecb.c \
	srcs/cipher/des/pbkdf-md5.c \


OBJS		= $(SRCS:.c=.o)

all: $(NAME)

objs/%.o: *%.c
	${CC}  -o $@ -c $< ${CFLAGS}


$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $@ $(CFLAGS)
	@echo "\033[32m\nrun command for test reel openssl: docker pull frapsoft/openssl && docker run -it frapsoft/openssl\n" 


clean:
	${RM} $(OBJS)

fclean: clean
	${RM} $(NAME) $(OBJS)

re: fclean all

.PHONY: all clean fclean re
