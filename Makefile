# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 16:12:22 by jhesso            #+#    #+#              #
#    Updated: 2023/06/18 15:41:46 by dgerguri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CFLAGS		=	-Wall -Wextra -Werror
READLINE	=	-lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
LIBFT		=	libft.a
LIBFT_DIR	=	libft/
SRC_PATH	=	src/
OBJ_PATH	=	obj/
SRC			=	main.c lexing.c
SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
OBJ			=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))
INCS		=	-I includes/

# pretty colors for the messages
GREEN			=	\033[0;32m
RED				=	\033[0;31m
BLUE			=	\033[0;34m
RESET			=	\033[0m

all: libft $(OBJ_PATH) $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@cc $(CFLAGS) -c $< -o $@ $(INCS)

$(NAME): $(OBJS) libft
	@echo "$(BLUE)Compiling $(NAME)$(RESET)"
	@cc $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft $(READLINE)
	@echo "$(GREEN)done$(RESET)"

clean:
	@echo "$(RED)removing object files$(RESET)"
	@/bin/rm $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@echo "$(RED)cleaning all compiled stuff.. :)$(RESET)"
	@/bin/rm $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@/bin/rm -rf $(OBJ_PATH)
	@echo "$(RED)done$(RESET)"

re: fclean all

.PHONY: all libft clean fclean re
