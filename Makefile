# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/27 20:29:29 by ajabado           #+#    #+#              #
#    Updated: 2024/07/30 22:06:52 by ajabado          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# color codes
RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m
HIDE	= \033[?25l
SHOW	= \033[?25h
BOLD	= \033[1m

# directories
OBJ_DIR = objs

# builtins
OBJS_BUILT = $(SRCS_BUILT:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)
SRCS_BUILT = $(addprefix $(SRC_DIR)/builtins/, \
ft_builtins_utils.c ft_builtins.c ft_mini_cd.c ft_mini_echo.c \
ft_mini_env.c ft_mini_exit.c ft_mini_export.c ft_mini_pwd.c ft_mini_unset.c \
)

# error
OBJS_ERR = $(SRCS_ERR:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)
SRCS_ERR = $(addprefix $(SRC_DIR)/error/, \
ft_error_utils.c ft_error.c \
)

# executor
OBJS_EXEC = $(SRCS_EXEC:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)
SRCS_EXEC = $(addprefix $(SRC_DIR)/executor/, \
ft_prepare_executor.c ft_here_doc.c ft_executor.c \
)

# expander
OBJS_EXP = $(SRCS_EXP:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)
SRCS_EXP = $(addprefix $(SRC_DIR)/expander/, \
ft_expander_echo.c ft_expander_utils.c ft_expander.c \
)

# lexer
OBJS_LEX = $(SRCS_LEX:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)
SRCS_LEX = $(addprefix $(SRC_DIR)/lexer/, \
ft_handle_token.c ft_lexer_clear_utils.c ft_lexer_reader.c ft_lexer_utils.c \
)

# parser
OBJS_PAR = $(SRCS_PAR:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)
SRCS_PAR = $(addprefix $(SRC_DIR)/parser/, \
ft_cmd_clear_utils.c ft_fill_cmd.c ft_parser_utils.c ft_parser.c \
)

# utils
OBJS_UTI = $(SRCS_UTI:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)
SRCS_UTI = $(addprefix $(SRC_DIR)/utils/, \
ft_arrdup.c ft_count_quotes.c ft_find_path.c ft_find_pwd.c ft_free_arr.c \
ft_free_data.c ft_initialize_data.c \
)

# main
OBJS_MAIN = $(SRCS_MAIN:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)
SRCS_MAIN = $(addprefix $(SRC_DIR), \
signal.c main.c \
)

SRCS = $(SRCS_BUILT) $(SRCS_ERR) $(SRCS_EXEC) $(SRCS_EXP) $(SRCS_LEX) $(SRCS_PAR) $(SRCS_UTI) $(SRCS_MAIN)
OBJS = $(OBJS_BUILT) $(OBJS_ERR) $(OBJS_EXEC) $(OBJS_EXP) $(OBJS_LEX) $(OBJS_PAR) $(OBJS_UTI) $(OBJS_MAIN)

CC = cc
RM = rm -rf
CFLAGS	= -Wall -Wextra -Werror -I $(INC_DIR)
MK		= --no-print-directory

NAME = minishell

INC_DIR			= includes/
HEADER			= $(INC_DIR)/minishell.h
SRC_DIR			= src/
LIBFT_DIR		= libft/
LIBFT			= $(LIBFT_DIR)/libft.a

COUNTER = 0
TOTAL_FILES = $(words $(SRCS))

all: $(LIBFT) $(NAME) $(HEADER)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -lncurses $(LIBFT) -o $(NAME)
	@echo "$(BOLD)${GREEN}\n> Compiled $(NAME) successfully$(RESET)$(SHOW)"

$(LIBFT):
	@make $(MK) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(eval COUNTER=$(shell echo $$(($(COUNTER) + 1))))
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)
	@printf "$(HIDE)$(BOLD)$(YELLOW)\rCompiling $(NAME): $(RESET)["
	@printf "%0.s#" $(shell seq 1 $(COUNTER))
	@if [ $(COUNTER) -lt $(TOTAL_FILES) ]; then \
		printf "%0.s." $(shell seq 1 $$(($(TOTAL_FILES) - $(COUNTER)))); \
	fi
	@printf "] (%d/%d)" $(COUNTER) $(TOTAL_FILES)

clean:
	@make clean $(MK) -C $(LIBFT_DIR)
	@$(RM) $(OBJ_DIR)
	@echo "$(YELLOW)> ALL object files of $(NAME) have been deleted$(RESET)"

fclean:
	@make fclean $(MK) -C $(LIBFT_DIR)
	@$(RM) $(OBJ_DIR)
	@echo "$(YELLOW)> ALL object files of $(NAME) have been deleted$(RESET)"
	@$(RM) $(NAME)
	@echo "$(RED)> $(NAME) has been deleted$(RESET)$(SHOW)"

re: fclean all

.PHONY: all clean fclean re
