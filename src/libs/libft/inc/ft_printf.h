/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:31:35 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/11 13:12:26 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# ifndef BASE_DEC
#  define BASE_DEC "0123456789"
# endif
# ifndef BASE_HEX
#  define BASE_HEX "0123456789abcdef"
# endif
# ifndef BASE_HEX_UPCASE
#  define BASE_HEX_UPCASE "0123456789ABCDEF"
# endif

# include <stdarg.h>
# include <stdbool.h>

typedef struct s_flags
{
	bool	number;
	bool	zero;
	bool	minus;
	bool	space;
	bool	plus;
	bool	is_valid;
	char	type;
	int		width;
	int		precision;
}	t_flags;

int		ft_printf(const char *format, ...);
bool	flags_are_valid(const char *format, int *format_i);
void	fill_flags(t_flags *flags, const char *format);
void	check_flags(t_flags *flags);
int		print_char(int c, t_flags flags);
char	*print_ptr(unsigned long ptr);
char	*print_null(char type);
char	*format_precision(char *str, int precision, char type);
char	*format_width(char *str, int width, bool minus);
char	*format_zero(char *str, bool space);
char	*format_number(char *str, char type);
char	*format_space_plus(char *str, bool plus);

#endif
