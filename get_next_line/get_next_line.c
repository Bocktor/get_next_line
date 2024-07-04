/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbocktor < jbocktor@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:01:37 by jbocktor          #+#    #+#             */
/*   Updated: 2023/10/26 21:44:54 by jbocktor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*null_free(char *s)
{
	free(s);
	return (NULL);
}

char	*buffer_in_stach(char *old_stach, const char *buffer, size_t byte)
{
	size_t	i;
	size_t	j;
	size_t	stash_size;
	char	*new_stach;

	if (!old_stach)
		stash_size = 0;
	else
		stash_size = ft_strlen(old_stach);
	i = 0;
	j = 0;
	new_stach = (char *)malloc(sizeof(*new_stach) * (stash_size + byte + 1));
	if (!new_stach)
		return (NULL);
	if (old_stach != (NULL))
		while (old_stach[i])
			new_stach[j++] = old_stach[i++];
	i = 0;
	while (i < byte)
		new_stach[j++] = buffer[i++];
	new_stach[j] = '\0';
	free(old_stach);
	return (new_stach);
}

char	*reading(int fd)
{
	long	byte;
	char	*read_buffer;
	char	*stach;

	byte = 1;
	stach = NULL;
	read_buffer = (char *)malloc(sizeof(read_buffer) * BUFFER_SIZE);
	if (!read_buffer)
		return (NULL);
	while (byte != 0)
	{
		byte = read(fd, read_buffer, BUFFER_SIZE);
		if (byte == -1)
		{
			free(stach);
			return (NULL);
		}
		if (byte != 0)
			stach = buffer_in_stach(stach, read_buffer, byte);
	}
	free(read_buffer);
	return (stach);
}

char	*get_next_malloc(char *s)
{
	int		i;
	char	*get_next_malloc;

	get_next_malloc = (char *)malloc(sizeof(get_next_malloc) * len_until_n(s));
	if (!get_next_malloc)
		return (NULL);
	i = 0;
	while (s[i])
	{
		get_next_malloc[i] = s[i];
		i++;
		if (s[0] == '\n' || s[i] == '\n')
		{
			if (s[0] != '\n')
			{
				get_next_malloc[i] = s[i];
				i++;
			}
			break ;
		}
	}
	get_next_malloc[i] = '\0';
	return (get_next_malloc);
}

char	*get_next_line(int fd)
{
	char		*get_next_result;
	static char	*readed;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (readed == NULL)
		readed = reading(fd);
	if (readed == NULL)
		return (null_free(readed));
	get_next_result = get_next_malloc(readed);
	if (readed != NULL)
		readed = ft_slash_n(readed, len_after_n(readed), len_until_n(readed));
	return (get_next_result);
}

/*clear && gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -g3 
get_next_line.c get_next_line_utils.c main.c 
&& valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -s 
./a.out*/

/*
#include "get_next_line.h"

int	main(void)
{
	int fd;
	char *tab;

	fd = open("...", O_RDONLY);
	tab = get_next_line(fd);
	printf("***");
	printf("%s", tab);
	printf("***");
	printf("\n\n");
	free(tab);
	}*/