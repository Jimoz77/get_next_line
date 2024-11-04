/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:52:09 by jimpa             #+#    #+#             */
/*   Updated: 2024/11/04 20:19:00 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//pour utiliser read : read(fichier,destination, taille)

/* char	*get_next_line(int fd)
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
			{
				free(stash);
				stash = NULL;
			}
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
}  */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}



char	*ft_strdup(const char *str)
{
	int		i;
	char	*copy;

	i = 0;
	while (str[i])
	{
		i++;
	}
	copy = (char *)malloc(sizeof(char) * i + 1);
	if (!copy)
	{
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void	remove_before_newline(char *str)
{
	char	*newline_pos;

	newline_pos = ft_strchr(str, '\n');
	if (newline_pos)
	{
		ft_memmove(str, newline_pos + 1, ft_strlen(newline_pos));
	}
}


void	*ft_calloc(size_t num, size_t size)
{
	unsigned char	*s;
	void			*slot;
	size_t			totalen;

	if (num != 0 && size > SIZE_MAX / num)
	{
		return (NULL);
	}
	slot = malloc(size * num);
	if (!slot)
	{
		return (NULL);
	}
	s = (unsigned char *)slot;
	totalen = num * size;
	while (totalen)
	{
		*s++ = '\0';
		totalen--;
	}
	return (slot);
}

char    *read_and_store(int fd, char **stash, char *buffer)
{
    int     is_end;
    int     i;

    while ((is_end = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[is_end] = '\0';
        *stash = ft_strconc(buffer, *stash);
        i = 0;
        while ((*stash)[i])
        {
            if ((*stash)[i] == '\n')
                return (ft_copy_til_bs(*stash));
            i++;
        }
    }
    return (NULL);
}

char    *get_next_line(int fd)
{
    char        *buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    static char *stash;
    char        *line;

    if (!buffer)
        return (NULL);
    if (stash == NULL && !(stash = ft_calloc(1, sizeof(char))))
        return (free(buffer), NULL);
    line = read_and_store(fd, &stash, buffer);
    free(buffer);
    if (line)
    {
        remove_before_newline(stash);
        return (line);
    }
    if (stash[0])
    {
        line = ft_strdup(stash);
        free(stash);
        stash = NULL;
        return (line);
    }
    free(stash);
    stash = NULL;
    return (NULL);
}
