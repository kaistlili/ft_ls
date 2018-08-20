# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktlili <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/10 23:32:37 by ktlili            #+#    #+#              #
#    Updated: 2018/08/20 15:24:59 by ktlili           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC_PATH = src

INC = ./

SRC_NAME =	main.c \
			lst_util.c \
		   	parse_opt.c \
			handle_av.c \
			ft_inner_ls.c \
		   	ft_getopt.c \
			formatting.c \
			cmp.c \
			formatting_util.c

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)

LIB = ./libftprintf.a

FLAGS = 

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all:	$(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) $(LIB) -o $@
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(OBJ_PATH)
	gcc -I$(INC) $(FLAGS) -o $@ -c $<

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
