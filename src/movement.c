#include "minirt.h"


/**
 * TODO:
 * get current node (sphere, plane cylinder)
 * check type
 * cast to correct struct 
 * make changes 
 */

/**
 * added to scene struct *obj_selected
 * initialized in init scene to null 
 * to track selected object
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!somewhere after parsing need to do:
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!scene->obj_selected = scene->obj_list
 * 
 * 
 */


/**
 * If there is next obj - select it 
 * Otherwise select the first one
 */
void select_object(t_scene *scene)
{
    if(!scene->obj_selected)
        return ;
    if(scene->obj_selected->next)
        scene->obj_selected = scene->obj_selected->next;
    else
        scene->obj_selected = scene->obj_list;
}



// need to create move bector with new_vec
void translate_object(t_olist *node, t_vec3 move_vec)
{
    t_sp *sp;
    t_pl *pl;
    t_cy *cy;

    if(!node)
        return ;
    if(node->obj_type == SP)
    {
        sp = (t_sp *)node->obj;
        sp->sp_center = vector_add(sp->sp_center, move_vec);
    }
    else if(node->obj_type == PL)
    {
        pl = (t_pl *)node->obj;
        pl->normal.origin = vector_add(pl->normal.origin, move_vec);
    }
    else if(node->obj_type == CY)
    {
        cy = (t_cy *)node->obj;
        cy->normal.origin = vector_add(cy->normal.origin, move_vec);
    }
}

void    handle_movement(int key, t_scene *scene)
{
    t_vec3 move_vec;

    move_vec = new_vector(0, 0, 0);
    if(key == KEY_W)
        move_vec.z -= 1;
    if(key == KEY_S)
        move_vec.z += 1;
    if(key == KEY_A)
        move_vec.x -= 1;
    if(key == KEY_D)
        move_vec.x += 1;
    if(key == KEY_Q)
        move_vec.y += 1;
    if(key == KEY_E)
        move_vec.y -= 1;
    
    translate_object(scene->obj_selected, move_vec);

}

// not sure about resizing
void    resize_objects(t_olist *node, float value)
{
    t_sp *sp;
    t_cy *cy;

    if(!node)
        return ;
    if(node->obj_type == SP)
    {
        sp = (t_sp *)node->obj;
        sp->diameter += value;
        if(sp->diameter < 0.1f)
            sp->diameter = 0.1f;
    }
    else if(node->obj_type == CY)
    {
        cy = (t_cy *)node->obj;
        cy->diameter += value;
        cy->height += value;
        if(cy->diameter < 0.1f)
            cy->diameter = 0.1f;
        if(cy->height < 0.1f)
            cy->height = 0.1f;
    }
}

// need rotation 
// need camera movement