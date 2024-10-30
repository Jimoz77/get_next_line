/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:52:09 by jimpa             #+#    #+#             */
/*   Updated: 2024/10/30 16:49:35 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


//pour utiliser read : read(fichier,destination, taille)

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*stash;
	int			i;
	int			is_end;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (stash == NULL)
	{
		stash = ft_calloc(1, sizeof(char));
		if (!stash)
		{
			free(buffer);
			return (NULL);
		}
	}
	is_end = 1;
	while (is_end != 0)
	{
		i = 0;
		is_end = read(fd, buffer, BUFFER_SIZE);
		if (is_end == -1)
		{
			free(buffer);
			if (stash)
				free(stash);
			return (NULL);
		}
		buffer[is_end] = '\0';
		stash = ft_strconc(buffer, stash);
		while (stash[i])
		{
			if (stash[i] == '\n')
			{
				line = ft_copy_til_bs(stash);
				remove_before_newline(stash);
				free(buffer);
				return (line);
			}
			i++;
		}
	}
	if (stash[0])
	{
		line = ft_strdup(stash);
		free(stash);
		stash = NULL;
		free(buffer);
		return (line);
	}
	free(buffer);
	if (stash)
	{
		free(stash);
		stash = NULL;
	}
	return (NULL);
}
