/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftlist.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 01:10:23 by amerlon-          #+#    #+#             */
/*   Updated: 2020/05/21 20:43:21 by amerlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTLIST_H
# define FTLIST_H

# include <stddef.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **als, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new_hook);
void				ft_lstaddbk(t_list **alst, t_list *new_hook);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstapply(t_list *lst, void (*f)(void *content));
void				ft_lstiteri(t_list *lst, void (*f)(t_list *elem, int idx));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
size_t				ft_lstlen(t_list const *lst);
void				ft_lstrev(t_list **alst);
t_list				*ft_lstlast(t_list *alst);
t_list				*ft_lstat(t_list *alst, unsigned int n);
t_list				*ft_lstget(t_list *alst, int v, int (*cmp)(void *c, int v));
void				*ft_lstgetelt(t_list *alst, int (*cmp)(void *c, void *k),
	void *key);
void				ft_lstpushnew(t_list **alst, const void *data,
	size_t content_size);
void				ft_lstiter_arg(int arg, t_list *lst,
	void (*f)(int arg, t_list *elem));
t_list				*ft_lstgetnode(t_list *alst, int (*cmp)(void *c, void *k),
	void *key);
void				*ft_lstgetelt_by_content_ptr(t_list *alst, void *key);
t_list				*ft_lstgetnode_by_content_ptr(t_list *alst, void *key);
t_list				*ft_lstpop(t_list *lst, t_list *to_del,
	void(*f)(void*, size_t));
void				ft_lstswap(t_list *root, t_list *to_swap1,
	t_list *to_swap2, t_list *next);
void				ft_lstswapfirst(t_list **root, t_list *to_swap1,
	t_list *to_swap2, t_list *next);
void				ft_lstsort(t_list **alst, int (*cmp)(void*, void*));
void				ft_lstaddendnew(t_list **alst, const void *data,
	size_t content_size);
int					ft_lstgetidx(t_list *lst, t_list *to_get);
void				ft_lstmoveup(t_list **alst, t_list *to_move);
void				ft_lstmovedown(t_list **alst, t_list *to_move);

#endif
