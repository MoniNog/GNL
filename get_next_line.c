/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaumann <sbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:05:22 by sbaumann          #+#    #+#             */
/*   Updated: 2023/12/13 14:54:24 by sbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*read_line(int fd, char *txt)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(txt, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		txt = ft_strjoin(txt, buffer);
	}
	free(buffer);
	return (txt);
}

char	*extract_line(char *txt)
{
	char	*res;
	int		count;

	count = 0;
	if (!txt[count])
		return (NULL);
	while (txt[count] && txt[count] != '\n')
		count++;
	res = (char *)malloc(count + 2);
	if (!res)
		return (NULL);
	count = 0;
	while (txt[count] && txt[count] != '\n')
	{
		res[count] = txt[count];
		count++;
	}
	if (txt[count] == '\n')
	{
		res[count] = txt[count];
		count++;
	}
	res[count] = '\0';
	return (res);
}

char	*remove_line(char *txt)
{
	char	*res;
	int		count;
	int		count2;

	count = 0;
	count2 = 0;
	while (txt[count] && txt[count] != '\n')
		count++;
	if (!txt[count])
	{
		free(txt);
		return (NULL);
	}
	res = (char *)malloc(sizeof(char) * (ft_strlen(txt) - count) + 1);
	if (!res)
		return (NULL);
	count++;
	while (txt[count])
		res[count2++] = txt[count++];
	res[count2] = '\0';
	free(txt);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*current_line;
	char		*dest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) == -1)
	{
		free(current_line);
		current_line = NULL;
		return (NULL);
	}
	current_line = read_line(fd, current_line);
	if (!current_line)
		return (NULL);
	dest = extract_line(current_line);
	current_line = remove_line(current_line);
	return (dest);
}
