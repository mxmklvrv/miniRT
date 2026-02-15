#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	float	aspect_ratio;
}	t_data;

typedef struct s_pixel
{
	int		i;
	int		j;
	int		color;
}	t_pixel;

// Tuple - a vector or a point
// w = 0 for vector;
// w = 1 for point;
// Needed for matrix math.
// Can be used for colors.
typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec3;

typedef struct s_matrix
{
	int		row;
	int		col;
	float	**ptr;
}	t_matrix;

// ray has starting point and direction
typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef enum e_otype
{
	SP,
	CY,
	PL
}	t_otype;

// linked list with objects
typedef struct s_olist
{
	void			*obj;
	t_otype			obj_type;
	int				obj_id;
	int				colour;
	struct s_olist	*next;
}	t_olist;

typedef struct s_sp
{
	t_vec3			sp_center;
	float			diameter;
	int				colour;
}	t_sp;

typedef struct s_pl
{
	t_ray			normal;
	int				colour;
}	t_pl;

typedef struct s_cy
{
	t_ray			normal;
	float			diameter;
	float			height;
	int				colour;
}	t_cy;

typedef struct s_cam
{
	t_ray			orient;
	float			fov;
	t_vec3			vector_i;
	t_vec3			vector_j;
}					t_cam;

typedef struct s_ambient
{
	float			amb;
	int				colour;
}					t_ambient;

typedef struct s_light
{
	t_vec3			pos;
	float			bright;
	int				color;
	// struct s_light *next;

}					t_light;

// main struct
typedef struct s_scene
{
	t_olist			*obj_list;
	t_ambient		ambient;
	t_light			light;
	t_cam			cam;
	int				qt_ambiant;
	int				qt_cam;
	int				qt_light;
	char			*err_m;
}					t_scene;

#endif
