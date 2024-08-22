NAME = minishell
MKDIR = mkdir
RM = rm -rf
RMD = rmdir

CC = gcc
LIBFTD = libraries/libft
SRCSD = src/
SRCSLEXERD = src/lexer/
SRCSPARSERD = src/parser/
SRCSUTILSD = src/utils/
BUILDD = build/
OBJSD = $(BUILDD)objs/
HEADERD = includes/
SRCSERRORD = src/error/
SRCSPARSERD = src/parser/
SRCSEXECUTORD = src/executor/
SRCSBUILTINSD = src/builtins/

BUILD_PATH = $(BUILDD) $(OBJSD)

# Define the source files as single-line variables
S_SRCS = main.c signal.c
SL_SRCS = ft_handle_token.c ft_lexer_reader.c ft_lexer_utils.c ft_lexer_clear_utils.c
SU_SRCS = ft_check_backslash.c ft_check_equal_sign_main.c ft_check_explanation_main.c \
										ft_check_if_empty_main.c ft_check_is_directory_main.c ft_check_quotes_in_string_main_utils.c \
										ft_check_quotes_in_string_main.c ft_check_token_start_end_main.c \
										ft_count_quotes_main.c ft_env_utils.c ft_find_path.c ft_find_pwd.c \
										ft_free_data.c ft_initialize_data.c ft_readline_main.c libft_mini_utils.c \
										libft_utils_arr.c lift_mini_modified.c ft_initialize_data_utils.c\
										ft_env_update_main.c ft_check_equal_sign_main_utils.c ft_check_token_lexer_main.c lift_mini_modified_utils.c
SE_SRCS = ft_error.c ft_error_utils.c ft_error_utils_two.c
SP_SRCS = ft_cmd_clear_utils.c ft_parser_utils.c ft_parser.c ft_fill_cmd.c ft_parser_utils_two.c ft_cmd_utils.c
SEXE_SRCS = ft_prepare_executor.c ft_executor.c ft_here_doc_utils.c ft_here_doc.c ft_executor_utils.c ft_prepare_executor_utils.c \
										ft_executor_utils_two.c ft_executor_utils_three.c
SB_SRCS = ft_builtins.c ft_builtins_utils.c ft_mini_cd_utils.c ft_mini_cd.c ft_mini_echo_utils.c \
										ft_mini_echo.c ft_mini_env.c ft_mini_exit.c ft_mini_export_utils_two.c ft_mini_export_utils.c\
										ft_mini_export.c ft_mini_pwd.c ft_mini_unset.c ft_check_heredoc_name.c ft_getpid_main.c\
										ft_mini_cd_utils_two.c ft_mini_cd_utils_three.c

# Combine all source files with their respective directories
SRCS := $(addprefix $(SRCSUTILSD), $(SU_SRCS)) \
								$(addprefix $(SRCSLEXERD), $(SL_SRCS)) \
								$(addprefix $(SRCSERRORD), $(SE_SRCS)) \
								$(addprefix $(SRCSPARSERD), $(SP_SRCS)) \
								$(addprefix $(SRCSEXECUTORD), $(SEXE_SRCS)) \
								$(addprefix $(SRCSBUILTINSD), $(SB_SRCS)) \
								$(addprefix $(SRCSD), $(S_SRCS))
# Generate object file paths from source file paths
OBJS := $(addprefix $(OBJSD), $(notdir $(patsubst %.c, %.o, $(SRCS))))

CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -L/usr/lib -lreadline 

LIBFT = $(LIBFTD)/libft.a

H_HEADER = minishell.h

HEADER = $(addprefix $(HEADERD), $(H_HEADER))

INCLUDES = -I$(HEADERD) -I$(LIBFTD)

all: $(LIBFT) $(BUILD_PATH) $(NAME)

# Compile each source file into object files
$(OBJSD)%.o: $(SRCSD)%.c $(HEADER)
	@echo "Compiling $(notdir $<) in $(SRCSD)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiled $(notdir $<) successfully!"

$(OBJSD)%.o: $(SRCSLEXERD)%.c $(HEADER)
	@echo "Compiling $(notdir $<) in $(SRCSLEXERD)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiled $(notdir $<) successfully!"

$(OBJSD)%.o: $(SRCSPARSERD)%.c $(HEADER)
	@echo "Compiling $(notdir $<) in $(SRCSPARSERD)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiled $(notdir $<) successfully!"

$(OBJSD)%.o: $(SRCSEXECUTORD)%.c $(HEADER)
	@echo "Compiling $(notdir $<) in $(SRCSEXECUTORD)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiled $(notdir $<) successfully!"

$(OBJSD)%.o: $(SRCSUTILSD)%.c $(HEADER)
	@echo "Compiling $(notdir $<) in $(SRCSUTILSD)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiled $(notdir $<) successfully!"

$(OBJSD)%.o: $(SRCSERRORD)%.c $(HEADER)
	@echo "Compiling $(notdir $<) in $(SRCSERRORD)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiled $(notdir $<) successfully!"

$(OBJSD)%.o: $(SRCSBUILTINSD)%.c $(HEADER)
	@echo "Compiling $(notdir $<) in $(SRCSBUILTINSD)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiled $(notdir $<) successfully!"

# Link all object files and libraries into the final executable
$(NAME): $(OBJS) $(HEADER) $(LIBFT)
	@echo "Linking $@..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@echo "$@ is ready!"

# Build the library first before compiling the main program
$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFTD)
	@echo "Libft built!"

# Create necessary directories if they don't exist
$(BUILDD):
	@$(MKDIR) $(BUILDD)

$(OBJSD):
	@$(MKDIR) $(OBJSD)

# Clean up intermediate object files and directories
clean:
	@echo "Cleaning object files..."
	@$(RM) $(OBJS)
	@echo "Removing build directories..."
	@$(RM) $(OBJSD) $(BUILDD)
	@echo "Cleaning libft..."
	@$(MAKE) clean -C $(LIBFTD)

# Remove all compiled files and libraries
fclean: clean
	@echo "Removing $(NAME)..."
	@$(RM) $(NAME)
	@echo "Removing libft.a..."
	@$(MAKE) fclean -C $(LIBFTD)

# Rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re
