AR = ar rcs
CFLAGS = -Wall -Wextra -Werror -MD -g3
RM = rm -f
CC = gcc
SRC_DIR = src
OBJ_DIR = obj
LIBFT = libft/libft.a
NAME = minishell
LIBFT_DIR = libft
LIBFT_OBJ_DIR = libft/obj

GREEN = \033[0;92m
RESET = \033[0m

SRC = main.c builtins.c ft_strtrim_all.c exec.c         \
      fill_node.c get_params.c ft_cmdtrim.c             \
      expand.c heredoc.c error.c env.c get_user.c     \
      get_next_line.c get_next_line_utils.c get_user_home.c    \
      ft_cmdsubsplit.c signal.c parse_args.c get_cmd.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include $(CFLAGS) $(CDEBUG) $(OBJ) $(LIBFT) -lreadline -o $@
	@echo "$(GREEN)minishell is up to date!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) -I ~/.brew/opt/readline/include -I /usr/local/opt/readline/include $(CFLAGS) $(CDEBUG) -c $< -o $@

$(LIBFT): | $(LIBFT_OBJ_DIR)
	@make -C libft

clean: | $(LIBFT_DIR)
	@make clean -C libft
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) $(LIBFT)
	@$(RM) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT_OBJ_DIR):
	@mkdir -p $(LIBFT_OBJ_DIR)

re: fclean
	@make all

-include $(OBJ_DIR)/*.d

.PHONY: all clean fclean re
