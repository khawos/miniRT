/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:02:38 by amedenec          #+#    #+#             */
/*   Updated: 2025/09/03 05:02:00 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	line_detected(t_liste *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

int	count_line_gnl(t_liste *list)
{
	int	i;
	int	len;

	len = 0;
	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

t_liste	*give_last_node(t_liste *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	copy_line(t_liste *list, char *line)
{
	int	i;
	int	j;

	j = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			line[j] = list->str_buf[i];
			if (list->str_buf[i] == '\n')
			{
				line[++j] = '\0';
				return ;
			}
			i++;
			j++;
		}
		list = list->next;
	}
	line[j] = '\0';
}

void	free_list(t_liste **list, t_liste *clean_node, char *buf)
{
	t_liste	*tmp;

	if (NULL == *list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str_buf);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node->str_buf[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}
