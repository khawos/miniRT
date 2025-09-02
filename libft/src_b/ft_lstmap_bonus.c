/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:17:48 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/29 16:15:06 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	*ft_free(t_list *head, void *content, void (*del)(void *))
{
	ft_lstclear(&head, (*del));
	(*del)(content);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*tmp;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	content = (*f)(lst->content);
	tmp = ft_lstnew((content));
	if (!tmp)
		return (ft_free(NULL, content, del));
	head = tmp;
	lst = lst->next;
	while (lst)
	{
		content = (*f)(lst->content);
		tmp->next = ft_lstnew(content);
		if (!tmp->next)
			return (ft_free(head, content, del));
		tmp = tmp->next;
		lst = lst->next;
	}
	tmp = NULL;
	return (head);
}

/*
void	del(void * content)
{
	free(content);
	content = NULL;
}

void	*ft_(void *str)
{
	char *c;
	char ch;

	c = (char *)str;
	ch = *c;
	ch = ft_toupper((int)ch);

	c = &ch;
	return ((void *)c);
}


int main(void)
{
	t_list 	**head;
	t_list	*chips;
	t_list	*chipsboosted;
	char 	*s1;
	char 	*s2;
	char 	*s3;

	s1 = malloc(sizeof(char) * 3);
	if (!s1)
		return 0; 
	s2 = malloc(sizeof(char) * 3);
	if (!s2)
		return 0; 
	s3 = malloc(sizeof(char) * 3);
	if (!s3)
		return 0; 

	s1 = "a\n";
	s2 = "b\n";
	s3 = "c\n";

	chips = ft_lstnew(s1);
	head = &chips;

	ft_lstadd_back(head, ft_lstnew(s2));
	ft_lstadd_back(head, ft_lstnew(s3));

	printf("%s",(char *)(*head)->content);
	printf("%s",(char *)((*head)->next)->content);
	printf("%s\n",(char *)(((*head)->next)->next)->content);

	chipsboosted = ft_lstmap(chips, ft_, (*del));

	printf("%s\n",(char *)chipsboosted->content);
	printf("%s\n",(char *)((chipsboosted->next)->content));
	printf("%s\n",(char *)(((chipsboosted->next)->next)->content));

}*/
