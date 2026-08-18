/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datalist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 23:02:21 by rihoy             #+#    #+#             */
/*   Updated: 2026/08/18 23:41:57 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rithylib.h"

void	*list_addback(t_voidlist **list, void *data) {
	t_voidlist	**tracer;
	t_voidlist	*newnode;

	if (!data || !list)
		return (NULL);

	newnode = (t_voidlist *)malloc(sizeof(t_voidlist));
	if (!newnode)
		return (NULL);
	
	tracer = list;
	newnode->data = data;
	newnode->next = NULL;
	while (*tracer) {
		tracer = &(*tracer)->next;
	}
	(*tracer) = newnode;
	return (newnode);
}

void	*list_addcmp(t_voidlist **list,
	void *data,
	void *ref,
	int (cmp_func)(void *, void *, void *)) {
	t_voidlist	**tracer;
	t_voidlist	*newnode;

	if (!data || !list)
		return (NULL);

	newnode = (t_voidlist *)malloc(sizeof(t_voidlist));
	if (!newnode)
		return (NULL);

	tracer = list;
	newnode->data = data;
	newnode->next = NULL;
	while ((*tracer) && cmp_func((*tracer)->data, data, ref) <= 0) {
		tracer = &(*tracer)->next;
	}
	
	newnode->next = *tracer;
	(*tracer) = newnode;

	return (newnode);
}
