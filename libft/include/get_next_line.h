/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:53:15 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/28 18:12:07 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_free(char *str);
char	*ft_read_update(char *read, char *next_line);
char	*ft_next_line_init(char *read);
size_t	len(char *str);
char	*ft_read_init(char *buffer, char *read, ssize_t i);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif
#endif
