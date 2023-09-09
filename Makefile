# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 16:12:22 by jhesso            #+#    #+#              #
#    Updated: 2023/09/09 17:18:59 by jhesso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g
READLINE	=	-lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
LIBFT		=	libft.a
LIBFT_DIR	=	libft/
SRC_PATH	=	src/
OBJ_PATH	=	obj/
SRC			=	main.c utils.c cleanup.c error.c\
				lexer/lexing.c lexer/lexing_utils.c lexer/syntax_checking.c \
				lexer/tokenization.c \
				parser/parsing.c parser/expanding.c parser/removing_quotes.c \
				parser/expanding_utils.c \
				parser/list.c \
				execution/execute.c execution/path.c execution/argv.c \
				execution/prepare_execution.c execution/execute_utils.c \
				execution/file/file.c execution/file/heredoc.c execution/file/heredoc_utils.c \
				builtins/builtin.c builtins/builtin_utils.c builtins/env.c builtins/cd.c\
				builtins/echo.c builtins/export.c builtins/pwd.c builtins/unset.c builtins/exit.c\
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

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/lexer
	@mkdir -p $(OBJ_PATH)/parser
	@mkdir -p $(OBJ_PATH)/builtins
	@mkdir -p $(OBJ_PATH)/execution
	@mkdir -p $(OBJ_PATH)/execution/file
	@mkdir -p $(OBJ_PATH)/signals
	@cc $(CFLAGS) -I ~/.brew/opt/readline/include -c $< -o $@ $(INCS)

$(NAME): $(OBJS)
	@echo "$(BLUE)Compiling $(NAME)$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
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

.PHONY: all clean fclean re
