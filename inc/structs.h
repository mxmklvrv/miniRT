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

typedef enum e_otype
{
    SP,
    CY,
    PL

}t_otype;



// linked list with objects
typedef struct s_olist
{
	void			*obj;
    t_otype         *obj_type;
    int             obj_id;
	struct s_olist	*next;

}					t_olist;


// main struct
typedef struct s_scene
{
	void			*mlx;
	void			*window;
    t_olist         *obj_list;

}					t_scene;




#endif
