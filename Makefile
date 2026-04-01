NAME := miniRT

CC := cc -g

CFLAGS := -Wall -Wextra -Werror
HEADERS = $(addprefix -I, $(LIBFT_DIR)/inc $(MLX_DIR) $(HDR_DIR) usr/include) -O3
LINKDIR = $(addprefix -L, $(LIBFT_DIR) $(MLX_DIR) usr/lib)
LINKFLAGS := $(addprefix -l, ft mlx_Linux) -lXext -lX11 -lm -lz

HDR_DIR := inc
HDR := \
	minirt.h \
	structs.h \
	macros.h \
	parsing.h \

SRC_DIR := src

SRC = \
	draw.c \
	hooks.c \
	main.c \
	print.c \
	render_setup.c \
	tracing_color.c \
	tracing_lighting.c \
	visuals.c

PARS_DIR := parsing
PARS_SRC := \
	dispatch.c \
	input_validation.c \
	parse_ambient.c \
	parse_camera.c \
	parse_cy.c \
	parse_light.c \
	parse_pl.c \
	parse_sp.c \
	read_file.c \
	utils_ascii.c\
	utils_digits.c \
	utils_error.c \
	utils_free.c \
	utils_list.c \
	utils.c

MATH_DIR := math
MATH_SRC := \
	color_get_value.c \
	color_operations.c \
	color.c \
	ray.c \
	shapes_hit_cy.c \
	shapes_hit.c \
	shapes_is_inside.c \
	shapes_normal.c \
	math_utils.c \
	vector_operations.c \
	vector_special.c \
	vector.c

MOVE_DIR := movement
MOVE_SRC := \
	move_utils.c \
	move.c \
	resize.c \
	rotation.c \
	set_keys.c \
	switch_modes.c \
	translation.c

SRC += $(PARS_SRC) $(MATH_SRC) $(MOVE_SRC)

OBJ_DIR := obj
OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

# ------------  VPATH  ------------------------------------------------------- #
VPATH := $(addprefix $(SRC_DIR)/, \
	.: \
	$(PARS_DIR): \
	$(MATH_DIR) \
	$(MOVE_DIR) \
	)

LIBS_DIR := $(SRC_DIR)/libs
# ------------  LIBFT  ------------------------------------------------------- #
LIBFT_DIR := $(LIBS_DIR)/libft
LIBFT := $(LIBFT_DIR)/libft.a

# ------------  MLX  --------------------------------------------------------- #
MLX_DIR := $(LIBS_DIR)/minilibx-linux
MLX := $(MLX_DIR)/libmlx_Linux.a

# ------------  RULES  ------------------------------------------------------- #
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LINKDIR) $(LINKFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
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
