NAME = miniRT

CC = cc -g

CFLAGS = -Wall -Wextra -Werror
HEADERS = $(addprefix -I, $(LIBFT_DIR) $(MLX_DIR) $(HDR_DIR) /usr/include) -O3
LINKDIR = $(addprefix -L, $(LIBFT_DIR) $(MLX_DIR) /usr/lib)
LINKFLAGS = $(addprefix -l, ft mlx_Linux) -lXext -lX11 -lm -lz

# ------------  LIBFT  ------------------------------------------------------- #
LIBFT_DIR = src/libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

# ------------  MLX  --------------------------------------------------------- #
MLX_DIR = src/libs/minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a

HDR_DIR = inc
HDR = $(addprefix $(HDR_DIR)/, \
	minirt.h \
	structs.h \
	macros.h \
	parsing.h \
	)

PARS_DIR = src/parsing
PARS_SRC = $(addprefix $(PARS_DIR)/, \
	dispatch.c \
	input_validation.c \
	parse_ambient.c \
	parse_camera.c \
	parse_cy.c \
	parse_light.c \
	parse_pl.c \
	parse_sp.c \
	read_file.c \
	utils.c \
	)


SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, \
	mainm.c \
	visuals.c \
	hooks.c \
	) \
	$(PARS_SRC)


OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ------------  RULES  ------------------------------------------------------- #
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LINKDIR) $(LINKFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(LIBFT)
	make clean -C $(MLX_DIR)

re: fclean all

# ------------  EXTRA  ------------------------------------------------------- #
.SECONDARY: $(OBJ_DIR) $(OBJ)
.PHONY: all re clean fclean
