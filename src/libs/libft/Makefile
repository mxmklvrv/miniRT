# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 15:29:34 by akolupae          #+#    #+#              #
#    Updated: 2026/03/26 18:24:36 by akolupae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

CC := cc
CFLAGS := -Wall -Werror -Wextra

INC_DIR := inc
INCFLAGS := -I$(INC_DIR) -MMD -MP

COLOR := \033[1;32m
RESET := \033[0m

HDR := \
	libft.h \
	ft_printf.h \
	get_next_line.h

# ------------  CHAR  -------------------------------------------------------- #
SRC_CHAR_DIR := char
SRC_CHAR := \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c

# ------------  STRING  ------------------------------------------------------ #
SRC_STR_DIR := string
SRC_STR := \
	ft_strlen.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_strmapi.c \
	ft_striteri.c

# ------------  MEMORY  ------------------------------------------------------ #
SRC_MEM_DIR := memory
SRC_MEM := \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_calloc.c

# ------------  MATH  -------------------------------------------------------- #
SRC_MATH_DIR := math
SRC_MATH := \
	ft_atoi.c \
	ft_atoi_base.c \
	ft_itoa.c \
	ft_itoa_base.c \
	ft_max.c \
	ft_min.c \
	ft_swap.c \
	ft_swapf.c \
	ft_abs.c

# ------------  PRINT  ------------------------------------------------------- #
SRC_PUT_DIR := print
SRC_PUT := \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c

# ------------  LIST  -------------------------------------------------------- #
SRC_LIST_DIR := list
SRC_LIST := \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstadd_back.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c

# ------------  FT_PRINTF  --------------------------------------------------- #
PRINTF_DIR := ft_printf
PRINTF_SRC := \
	ft_printf.c \
	ft_printf_flags.c \
	ft_printf_format.c \
	ft_printf_precision.c \
	ft_printf_utils.c

# ------------  GET_NEXT_LINE  ----------------------------------------------- #
NEXT_LINE_DIR = get_next_line
NEXT_LINE_SRC = get_next_line.c

# ------------  VPATH  ------------------------------------------------------- #
SRC_DIR := src
SRC := $(SRC_CHAR) $(SRC_STR) $(SRC_MEM) $(SRC_MATH) $(SRC_PUT) $(SRC_LIST) \
	$(PRINTF_SRC) \
	$(NEXT_LINE_SRC)

OBJ_DIR := obj
OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

VPATH = $(addprefix $(SRC_DIR)/, \
	$(SRC_CHAR_DIR): \
	$(SRC_STR_DIR): \
	$(SRC_MEM_DIR): \
	$(SRC_MATH_DIR): \
	$(SRC_PUT_DIR): \
	$(SRC_LIST_DIR): \
	$(PRINTF_DIR): \
	$(NEXT_LINE_DIR))

# ------------  RULES  ------------------------------------------------------- #
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@ar -rcs $(NAME) $(OBJ)
	@echo "$(COLOR) Building $@$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) $(INCFLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(COLOR) Cleaning $(NAME)$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR) Removing $(NAME)$(RESET)"

re: fclean all

# ------------  EXTRA  ------------------------------------------------------- #
.SECONDARY: $(OBJ_DIR) $(OBJ)
.PHONY: all clean fclean re
