/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:38:34 by amedenec          #+#    #+#             */
/*   Updated: 2025/09/03 05:02:00 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct p_list
{
	char			*str_buf;
	struct p_list	*next;
}			t_liste;

char	*get_next_line(int fd);
//void	prep_list(t_list **list);
//void	append(t_list **list, char *buf);
//void	create_list(t_list **list, int fd);
//char	*get_line(t_list *list);

// utils
int		line_detected(t_liste *list);
int		count_line_gnl(t_liste *list);
t_liste	*give_last_node(t_liste *list);
void	copy_line(t_liste *list, char *line);
void	free_list(t_liste **list, t_liste *clean_node, char *buf);

#endif
