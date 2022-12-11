/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:52:30 by wmessmer          #+#    #+#             */
/*   Updated: 2022/12/10 13:17:20 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	backup = ft_line_read(fd, backup);
	if (!backup)
		return (NULL);
	line = ft_get_line(backup);
	backup = ft_backup(backup);
	return (line);
}

char	*ft_line_read(int fd, char *backup)
{
	char	*buffer;
	int		trigger;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	trigger = 1;
	while (!ft_strchr(backup, '\n') && trigger != 0)
	{
		trigger = read(fd, buffer, BUFFER_SIZE);
		if (trigger == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[trigger] = '\0';
		backup = ft_strjoin(backup, buffer);
	}
	free(buffer);
	return (backup);
}

char	*ft_get_line(char *backup)
{
	int		i;
	char	*line;

	i = 0;
	if (!backup[i])
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (backup[i] && backup[i] != '\n')
	{
		line[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
	{
		line[i] = backup[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_backup(char *backup)
{
	int		i;
	int		c;
	char	*buff;
	int		len;

	len = ft_strlen(backup);
	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	buff = (char *)malloc(sizeof(char) * (len - i + 1));
	if (!buff)
		return (NULL);
	i++;
	c = 0;
	while (backup[i])
		buff[c++] = backup[i++];
	buff[c] = '\0';
	free (backup);
	return (buff);
}
