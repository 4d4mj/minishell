# Directories
SRCP = ./
LIBFT_DIR = ../libft/
OBJ_DIR = obj

# Source files
SRCS = ft_check.c ft_cprint.c ft_diprint.c ft_num_digits.c ft_num_hex_digits.c ft_unum_digits.c\
            ft_parse.c ft_percentprint.c ft_pprint.c ft_puthex_fd.c ft_xprint.c\
            ft_putptr_fd.c ft_putunbr_fd.c ft_sprint.c ft_uprint.c ft_printf.c\

# Object files
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Library
NAME = libftprintf.a
LIBFT = libft.a
LIBFT_AR = $(LIBFT_DIR)$(LIBFT)

# Compiler
GCC = gcc
AR = ar 
ARFLAGS = rcs
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

# Targets
all: $(NAME)

$(OBJ_DIR)/%.o:%.c | $(OBJ_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT_AR):
	make -C $(LIBFT_DIR) all

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT_AR)
	cp $(LIBFT_AR) $(NAME)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS) 

clean:
	$(RM) $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
