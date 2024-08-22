NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = get_next_line.c ft_in.c get_next_line_utils.c \
							ft_strndup.c ft_strcpy.c ft_isdigit.c ft_strcmp.c\
							ft_memcpy.c ft_atoi.c ft_bzero.c ft_calloc.c \
							ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isprint.c\
							ft_itoa.c ft_memchr.c ft_memcmp.c ft_memmove.c ft_memset.c\
							ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c\
							ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c\
							ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c\
							ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c\
							ft_toupper.c
BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
 							ft_lstadd_back.c  ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstdelone.c
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Building $(NAME)..."
	@ar rcs $(NAME) $(OBJS)
	@echo "Done!"

$(OBJS): %.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< successfully!"

bonus: $(OBJS) $(BONUS_OBJS)
	@echo "Building bonus objects..."
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "Bonus objects built successfully!"

$(BONUS_OBJS): %.o: %.c
	@echo "Compiling bonus $<..."
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled bonus $< successfully!"

clean:
	@echo "Cleaning up object files..."
	@rm -f $(OBJS) $(BONUS_OBJS)
	@echo "Cleaned!"

fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)
	@echo "$(NAME) removed!"

re: fclean all

.PHONY: all clean fclean re bonus