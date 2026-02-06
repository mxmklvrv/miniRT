# ------------  VARS  -------------------------------------------------------- #
NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

CC = cc

HEADERS = libft.h

SRC_DIR = src
SRCS = 	ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
		ft_isprint.c ft_memset.c ft_strlen.c ft_memcmp.c  ft_memmove.c \
		ft_memchr.c ft_strlcpy.c ft_strlcat.c ft_tolower.c ft_toupper.c \
		ft_strchr.c ft_strrchr.c ft_strncmp.c ft_atoi.c ft_strnstr.c \
		ft_calloc.c  ft_strdup.c ft_substr.c ft_memcpy.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
		ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
		$(addprefix math/, ft_max.c ft_abs.c ft_swapf.c) \
		$(addprefix get_next_line/, get_next_line.c get_next_line_utils.c) \
		$(addprefix ft_printf/, ft_printf.c ft_utilities.c)

OBJ_DIR = obj
OBJS =	$(SRCS:%.c=$(OBJ_DIR)/%.o)\

# ------------  RULES  ------------------------------------------------------- #
all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I . -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# ------------  EXTRA  ------------------------------------------------------- #
.PHONY: all re clean fclean
.SECONDARY: $(OBJ_DIR) $(OBJS)
