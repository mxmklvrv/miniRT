#ifndef STRUCTS_H
# define STRUCTS_H

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

// ray has starting point and direction
// starting point is a point;
// direction is a vector.
typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_matrix
{
	int		row;
	int		col;
	float	**ptr;
}	t_matrix;

typedef enum e_otype
{
	SP,
	CY,
	PL
}	t_otype;

/* For shapes material assume:
 * ambient = 0.1
 * diffuse = 0.9
 * specular = 0.9
 * shininess = 200.0
 */
typedef struct s_shape
{
	t_otype			obj_type;
	int				obj_id;
	t_vec3			center;//sp
	t_ray			normal;//pl, cy
	float			diameter;//sp, cy
	float			height;//cy
    t_vec3          axis;
    float           radius;
    float           half_h;
	t_matrix		matrix;
	int				color;
}	t_shape;

typedef struct s_olist
{
	t_shape			*shape;
	struct s_olist	*next;
}	t_olist;

typedef struct s_intersection
{
	int		count;
	float	val[4]; // max change 
	t_shape	*shape;
}	t_intersection;

typedef struct s_cam
{
	t_ray			orient;
	float			fov;
	float			pixel_size;
	t_matrix		matrix;
	t_vec3	right; // test
	t_vec3	up; // test
    float yaw;
    float pitch;

}	t_cam;

typedef struct s_ambient
{
	float			amb;
	int				color;
}	t_ambient;

typedef struct s_light
{
	t_vec3			pos;
	float			bright;
	int				color;
	// struct s_light *next;

}	t_light;

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
    int             next_obj_id;
	char			*err_m;
	t_olist			*obj_selected;
}					t_scene;

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
	t_scene *scene;
	void	*move_state;
	int		control_cam;
}	t_data;

typedef enum e_axis
{
	Y_AXIS,
	X_AXIS
}		t_axis;

typedef enum e_exeption
{
	NO_ROT,
	NO_RES,
	NO_HIGHT_RES
}	t_exeption;

typedef struct s_move_state
{
	int	forward;
	int	backward;
	int	left;
	int	right;
	int	up;
	int	down;
	int	rotate_left;
	int	rotate_right;
	int	rotate_up;
	int	rotate_down;
	int	resize_up;
	int	resize_down;
	int	height_up;
	int	height_down;
}		t_move_state;

#endif