/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:29:33 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/22 20:29:35 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_HEADER_H
# define GC_HEADER_H

# include "../libft/libft.h"

typedef struct s_gc_node
{
	void				*address;
	struct s_gc_node	*next;
}	t_gc_node;

typedef struct s_gc
{
	t_gc_node	*head;
}	t_gc;

/* garbage collector functions */
void	*gc_alloc(size_t size);
void	gc_free(void *address);
void	gc_cleanup(void);

/* garbage collector string functions */
char	*gc_strldup(const char *str, size_t len);
char	*gc_substr(char const *s, unsigned int start, size_t len);
char	**gc_split(char const *s, char c);
char	*gc_strljoin(char const *s1, char const *s2, size_t len);

/* garbage collector utils */
void	gc_init(t_gc *gc);
t_gc	*get_gc_head(void);
int		gc_add_node(t_gc *gc, void *address);
void	gc_delete_node(t_gc *gc, void *address);
void	free_all(t_gc *gc);

#endif
