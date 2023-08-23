# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 16:12:22 by jhesso            #+#    #+#              #
#    Updated: 2023/08/23 17:22:43 by dgerguri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g
READLINE	=	-lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
LIBFT		=	libft.a
LIBFT_DIR	=	libft/
SRC_PATH	=	src/
OBJ_PATH	=	obj/
SRC			=	main.c utils.c cleanup.c \
				lexer/lexing.c lexer/lexing_utils.c lexer/syntax_checking.c \
				lexer/tokenization.c \
				parser/parsing.c parser/expanding.c parser/removing_quotes.c \
				parser/list/list.c parser/list/lst_utils.c \
				execution/execute.c execution/path.c execution/argv.c \
				execution/prepare_execution.c \
				execution/file/file.c \
				builtins/builtin.c builtins/builtin_utils.c builtins/env.c \
				builtins/echo.c builtins/export.c builtins/pwd.c \
				signals/signals.c
SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
OBJ			=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))
INCS		=	-I includes/

# pretty colors for the messages
GREEN			=	\033[0;32m
RED				=	\033[0;31m
BLUE			=	\033[0;34m
RESET			=	\033[0m

all: $(LIBFT) $(OBJ_PATH) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)
	@mkdir $(OBJ_PATH)/lexer
	@mkdir $(OBJ_PATH)/parser
	@mkdir $(OBJ_PATH)/parser/list
	@mkdir $(OBJ_PATH)/builtins
	@mkdir $(OBJ_PATH)/execution
	@mkdir $(OBJ_PATH)/execution/file
	@mkdir $(OBJ_PATH)/signals

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@cc $(CFLAGS) -I ~/.brew/opt/readline/include -c $< -o $@ $(INCS)

$(NAME): $(OBJS)
	@echo "$(BLUE)Compiling $(NAME)$(RESET)"
	@cc $(CFLAGS) $(OBJS) -o $(NAME) -L $(LIBFT_DIR) -lft $(READLINE)
	@echo "$(GREEN)done$(RESET)"

clean:
	@echo "$(RED)removing object files$(RESET)"
	@/bin/rm -rf $(OBJ_PATH)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@echo "$(RED)cleaning all compiled stuff.. :)$(RESET)"
	@/bin/rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)done$(RESET)"

re: fclean all

.PHONY: all libft clean fclean re
