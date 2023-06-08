# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 16:03:45 by jhesso            #+#    #+#              #
#    Updated: 2023/04/14 15:09:42 by jhesso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
SRC_PATH		=	src/
OBJ_PATH		=	obj/
SRC				= 	printf/arguments.c printf/ft_itoa_unsigned.c\
					printf/ft_printf.c printf/hex.c\
					ft_absolute.c ft_atoi.c ft_bzero.c ft_calculate_digits.c\
					ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
					ft_isdigit.c ft_isnum.c ft_isprint.c ft_itoa.c\
					ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c\
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c\
					ft_lstnew.c ft_lstsize.c ft_memchr.c ft_memcmp.c\
					ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c\
					ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c\
					ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c\
					ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c\
					ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strrev.c\
					ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c\
					get_next_line.c ft_strcmp.c ft_print_str_arr.c
SRCS			=	$(addprefix $(SRC_PATH), $(SRC))
OBJ				=	$(SRC:.c=.o)
OBJS			=	$(addprefix $(OBJ_PATH), $(OBJ))
INCS			=	-I includes/

# pretty colors for the messages
GREEN			=	\033[0;32m
BLUE			=	\033[0;34m
RESET			=	\033[0m

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)
	@mkdir obj/printf

$(NAME): $(OBJS)
	@echo "$(BLUE)Building library$(RESET)"
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)done$(RESET)"

clean:
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@echo "$(BLUE)Removing library$(RESET)"
	@/bin/rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
