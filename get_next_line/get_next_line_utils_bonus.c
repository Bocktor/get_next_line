/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbocktor < jbocktor@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:25:22 by jbocktor          #+#    #+#             */
/*   Updated: 2023/10/26 19:43:07 by jbocktor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	len_until_n(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			break ;
		i++;
	}
	i++;
	return (i);
}

size_t	len_after_n(const char *s)
{
	size_t	before_backslash;
	size_t	after_backslash;

	before_backslash = 0;
	after_backslash = 0;
	while (s[before_backslash])
	{
		if (s[before_backslash] == '\n')
			break ;
		before_backslash++;
	}
	while (s[before_backslash])
	{
		before_backslash++;
		after_backslash++;
	}
	return (after_backslash);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	i++;
	return (i);
}

char	*ft_slash_n(char *old_stash, size_t size, size_t after_backslash)
{
	char	*new_stash;
	size_t	begin;

	if (ft_strlen(old_stash) == after_backslash
		|| ft_strlen(old_stash) == (after_backslash + 1))
	{
		free(old_stash);
		return (NULL);
	}
	new_stash = (char *)malloc(sizeof(char) * (size));
	if (!new_stash)
		return (NULL);
	begin = 0;
	while (old_stash[after_backslash])
	{
		new_stash[begin] = old_stash[after_backslash];
		after_backslash++;
		begin++;
	}
	new_stash[begin] = '\0';
	free(old_stash);
	return (new_stash);
}
