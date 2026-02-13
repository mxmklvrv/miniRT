#ifndef STRUCTS_H
# define STRUCTS_H

// typedef struct s_vars
// {
// 	void	*mlx;
// 	void	*win;
// }			t_vars;

// typedef struct s_data
// {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }			t_data;

// typedef struct s_point
// {
// 	int		x;
// 	int		y;
// 	int		color;
// }			t_point;

typedef struct s_vec3
{
	float			x;
	float			y;
	float			z;

}					t_vec3;

typedef enum e_otype
{
	SP,
	CY,
	PL
}					t_otype;

// linked list with objects
typedef struct s_olist
{
	void			*obj;
	t_otype			obj_type;
	int				obj_id;
	int				colour;
	struct s_olist	*next;

}					t_olist;

typedef struct s_sp
{
	t_vec3			sp_center;
	float			diameter;
	//float			radius;
	int				colour;
}					t_sp;

typedef struct s_pl
{
	t_vec3			pl_point;
	t_vec3			normal;
	int				colour;
}					t_pl;

typedef struct s_cy
{
	t_vec3			cy_center;
	t_vec3			normal;
	float			diameter;
	float			height;
	int				colour;
}					t_cy;

typedef struct s_cam
{
	t_vec3			view_point;
	t_vec3			orient;
	float			fov;
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
	void			*mlx;
	void			*window;
	t_olist			*obj_list;
	t_ambient		ambient;
	// t_light         *light;
	t_light			light;
	t_cam			cam;
	int				qt_ambiant;
	int				qt_cam;
	int				qt_light;
	char			*err_m;
    t_olist         *obj_selected;


}					t_scene;

#endif
