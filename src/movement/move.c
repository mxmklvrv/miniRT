/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:54:06 by akolupae          #+#    #+#             */
/*   Updated: 2026/04/01 21:54:07 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	apply_movement(t_data *data)
{
	int	need_redraw;

	need_redraw = 0;
	if (handle_translation(data))
		need_redraw = 1;
	if (handle_rotation(data))
		need_redraw = 1;
	if (handle_resize(data))
		need_redraw = 1;
	if (need_redraw)
		draw_scene(data);
}
