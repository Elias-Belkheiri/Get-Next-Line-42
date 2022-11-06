/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:15:10 by ebelkhei          #+#    #+#             */
/*   Updated: 2022/11/06 14:38:16 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*line(char *buff)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	if (!buff || !*buff)
		return (NULL);
	if (ft_strchr(buff, '\n'))
		j = 2;
	else
		j = 1;
	res = malloc(get_len(buff) + j);
	if (!res)
		return (NULL);
	while (*buff && *buff != '\n')
	{
		res[i++] = *buff++;
	}
	if (*buff == '\n')
		res[i++] = '\n';
	res[i] = 0;
	return (res);
}

char	*get_lines(int fd, char *store)
{
	char	*buff;
	int		i;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!ft_strchr(store, '\n'))
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 0)
		{
			free(buff);
			free(store);
			return (NULL);
		}
		else if (i == 0)
		{
			free (buff);
			return (store);
		}
		buff[i] = 0;
		store = ft_strjoin(store, buff);
	}
	free(buff);
	return (store);
}

char	*ft_free(char *store)
{
	free(store);
	return (NULL);
}

char	*sub_lines(char *store)
{
	char	*sub;
	int		i;
	int		j;

	if (!store)
		return (NULL);
	i = get_len(store);
	if (i - ft_strlen(store) == 0)
		return (ft_free(store));
	sub = malloc(ft_strlen(store) - i);
	if (!sub)
		return (ft_free(store));
	j = 0;
	if (store[i] == '\n')
		i++;
	while (store[i + j])
	{
		sub[j] = store[i + j];
		j++;
	}
	sub[j] = '\0';
	free(store);
	return (sub);
}

char	*get_next_line(int fd)
{
	static char	*store[OPEN_MAX];
	char		*next_line;

	store[fd] = get_lines(fd, store[fd]);
	next_line = line(store[fd]);
	store[fd] = sub_lines(store[fd]);
	return (next_line);
}
