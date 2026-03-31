#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_pixel
{
	int		i;
	int		j;
	int		color;
}	t_pixel;

/* Tuple - a vector or a point
 * w = 0 for vector;
 * w = 1 for point;
 */
typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec3;

/* Ray has starting point and direction.
 * starting point is a point;
 * direction is a vector.
*/
typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_quad
{
	t_vec3	vec_to_obj;
	float	a;
	float	b;
	float	c;
	float	discriminant;
} t_quad;

typedef enum e_otype
{
	SP,
	CY,
	PL
}	t_otype;

/* Struct for all shapes.
 * Shape-specific parameters:
 * center - SP
 * normal - PL, CY
 * radius - SP, CY
 * half_height - CY
 */
typedef struct s_shape
{
	t_otype			obj_type;
	int				obj_id;
	t_vec3			center;
	t_ray			normal;
	float			radius;
	float			half_height;
	int				color;
}	t_shape;

/* List of shapes.
 */
typedef struct s_olist
{
	t_shape			*shape;
	struct s_olist	*next;
}	t_olist;

// typedef struct s_llist // added new
// {
//     t_light *light;
//     struct  s_llist *next;
// } t_llist;

/* Struct for intersections.
 * Expected intersection count for shapes:
 * PL - 1;
 * SP - 2;
 * CY - 4.
 */
typedef struct s_intersection
{
	int		count;
	float	val[4];
	t_shape	*shape;
}	t_intersection;

typedef struct s_cam
{
	t_ray	orient;
	float	fov;
	float	pixel_size;
	t_vec3	right;
	t_vec3	up;
	float	yaw;
	float	pitch;
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

}	t_light;

// main struct
typedef struct s_scene
{
	t_olist			*obj_list;
    // t_llist         *light_list; // added new
	t_ambient		ambient;
	t_light			light;
	t_cam			cam;
	int				qt_ambiant;
	int				qt_cam;
	int				qt_light;
    int             next_obj_id;
	char			*error_line;
	t_olist			*obj_selected;
    // t_llist         *light_selected; // added new
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
	int		control_light;
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