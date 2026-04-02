/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:02:36 by akolupae          #+#    #+#             */
/*   Updated: 2026/04/01 21:02:39 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define FAILURE -1
# define SUCCESS 0
# define WIDTH 700
# define HEIGHT 700

# define ERR_MSG "Error"
# define ERR_AC "Usage: ./miniRT file.rt"
# define ERR_EXT "Wrong file extension, should be file.rt"
# define ERR_ALLOC "Memory allocation failed"
# define ERR_WRONG_CHAR "Unknown char detected in .rt"
# define ERR_OPEN "Failed open file for reading"
# define ERR_NO_OBJ "There is nothing to render"
# define ERR_VEC_ZERO "Vector has length of 0"

# define ERR_PL_SPEC "Invalid specs for plane"
# define ERR_PL_LIST "Failed adding plane to the list"
# define ERR_PL_POINT "Invalid plane point"
# define ERR_PL_NORM "Invalid plane normal"
# define ERR_PL_COLR "Invalid plane color"

# define ERR_SP_SPEC "Invalid specs for sphere"
# define ERR_SP_LIST "Failed adding sphere to the list"
# define ERR_SP_CNTR "Invalid sphere center"
# define ERR_SP_DIAM "Invalid sphere diameter"
# define ERR_SP_COLR "Invalid sphere color"

# define ERR_CY_SPEC "Invalid specs for cylinder"
# define ERR_CY_LIST "Failed adding cylinder to the list"
# define ERR_CY_CNTR "Invalid cylinder center"
# define ERR_CY_AXIS "Invalid cylinder axis"
# define ERR_CY_DIAM "Invalid cylinder diameter"
# define ERR_CY_HGHT "Invalid cylinder height"
# define ERR_CY_COLR "Invalid cylinder color"

# define ERR_CAM_QTY "Only 1 camera is alowed"
# define ERR_CAM_NOCAM "There is no camera"
# define ERR_CAM_SPEC "Invalid specs for camera"
# define ERR_CAM_VIEW "Invalid camera view point"
# define ERR_CAM_ORIT "Invalid camera orientation"
# define ERR_CAM_FOV "Invalid camera FOV"

# define ERR_AMB_QTY "Only 1 Ambient is allowed"
# define ERR_AMB_SPEC "Invalid Ambient specs"
# define ERR_AMB_RATI "Invalid Ambient ratio"
# define ERR_AMB_COLR "Invalid Ambient color"

# define ERR_LIGT_QTY "Only 1 light is allowed"
# define ERR_LIGT_SPEC "Invalid light specs"
# define ERR_LIGT_POS "Invalid light position"
# define ERR_LIGT_BRIT "Invalid light brightness"
# define ERR_LIGT_COLOR "Invalid light color"

# define ESCAPE 0xFF1B
# define ON_PRESS 2
# define ON_RELEASE 3
# define ON_DESTROY 17

# define EPSILON 0.001
# define BACKGROUNG 0x000000

# define MOVE_SPEED 0.5f
# define ROTATE_SPEED 0.1f
# define RESIZE_SPEED 0.2f

/*
 * KEY_W 119		forward
 * KEY_A 97			left
 * KEY_S 115		back
 * KEY_D 100		right
 * KEY_Q 113		up
 * KEY_E 101		down
 * KEY_C 99			cam
 * KEY_L 108		light
 * KEY_TAB 65289	switch obj
 * KEY_LEFT 65361	rotate left
 * KEY_RIGHT 65363	rotate right
 * KEY_UP 65362		rotate up
 * KEY_DOWN 65364	rotate down
 * KEY_PLUS 61		resize up
 * KEY_MINUS 45		resize down
 * KEY_ESC 65307	esc
 * KEY_H 104		height up
 * KEY_J 106		height down
 */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101
# define KEY_C 99
# define KEY_L 108
# define KEY_TAB 65289
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_PLUS 61
# define KEY_MINUS 45
# define KEY_ESC 65307
# define KEY_H 104
# define KEY_J 106

#define KEY_ON 1
#define KEY_OFF 0

#define MIN_RANGE -1000.0f
#define MAX_RANGE 1000.0f

#endif
