/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:51:52 by jimpa             #+#    #+#             */
/*   Updated: 2024/10/28 17:00:34 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// attention ne pas oublier le \0
char	*ft_strconc(const char *source, char *dest)
{
    int		i;
    int		j;
    char	*new_dest;
    int		dest_len;
    int		source_len;

    if (!dest)
        dest_len = 0;
    else
        dest_len = ft_strlen(dest);
    source_len = ft_strlen((char *)source);
    new_dest = (char *)malloc(dest_len + source_len + 1);
    if (!new_dest)
        return (NULL);
    i = 0;
    while (i < dest_len)
    {
        new_dest[i] = dest[i];
        i++;
    }
    j = 0;
    while (j < source_len)
    {
        new_dest[i + j] = source[j];
        j++;
    }
    new_dest[i + j] = '\0';
    return (new_dest);
}

char	*ft_copy_til_bs(char *str)
{
	char	*copy;
	int		i;

	i = 0;
	while (str[i] != '\n')
		i++;
	copy = (char *)malloc(sizeof(char) * i + 2);
	if (!copy)
		return (NULL);
	i = 0;
	while (str[i] != '\n')
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\n';
	copy[i + 1] = '\0';
	return (copy);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*result;
	const unsigned char	*source;

	if (!dest && !src)
		return (NULL);
	result = (unsigned char *)dest;
	source = (const unsigned char *)src;
	while (n--)
	{
		*result++ = *source++;
	}
	return (dest);
}

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

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const char	*tmp;
	char		*dest;

	tmp = (char *)src;
	dest = (char *)dst;
	if (tmp < dest && dest < tmp + n)
	{
		while (n--)
			dest[n] = tmp[n];
	}
	else
	{
		ft_memcpy(dest, tmp, n);
	}
	return (dst);
}
void	remove_before_newline(char *str)
{
	char *newline_pos = ft_strchr(str, '\n');
	if (newline_pos)
	{
		// Déplacez tous les caractères après '\n' au début de la chaîne
		ft_memmove(str, newline_pos + 1, ft_strlen(newline_pos));
	}
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
