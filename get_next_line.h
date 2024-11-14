/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:51:05 by jimpa             #+#    #+#             */
/*   Updated: 2024/11/14 13:51:57 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define GET_NEXT_LINE_H
#ifdef GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*ft_strconc(const char *source, char *dest, int s_len, int d_len);
char	*ft_copy_til_bs(char *str);
char	*get_next_line(int fd);
int		ft_strlen(char *str);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	remove_before_newline(char *str);
char	*ft_strdup(const char *str);
void	*ft_calloc(size_t num, size_t size);
char	*multifree(char *stash, char *buffer);
#endif