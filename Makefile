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
CC					= clang

CFLAGS				= -Wall -Wextra -Werror -g3# -fsanitize=address 

NAME				= ft_ssl

SRCS = srcs/md5/md5_parser.c \
	srcs/md5/md5_init_conf.c \
	srcs/md5/md5.c \
	srcs/md5/md5_print.c \
	srcs/main.c \
	srcs/parser.c \
	srcs/init_conf.c \
	srcs/sha256/sha256.c \
	srcs/sha256/sha256_init_conf.c \
	srcs/sha256/sha256_parser.c \
	srcs/sha256/sha256_print.c \

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

objs/%.o: *%.c
	${CC} -o $@ -c $< ${CFLAGS}


$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $@ $(CFLAGS) -g3


clean:
	${RM} $(OBJS)

fclean: clean
	${RM} $(NAME) $(OBJS)

re: fclean all

.PHONY: all clean fclean re
