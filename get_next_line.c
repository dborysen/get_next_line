/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:48:29 by dborysen          #+#    #+#             */
/*   Updated: 2017/12/15 13:12:47 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_help	*find_fd(t_help **txt, int fd)
{
	t_help *tmp;
	t_help *new;

	tmp = *txt;
	if (tmp && tmp->fd == fd)
		return (tmp);
	while (tmp && tmp->next != NULL)
	{
		tmp = tmp->next;
		if (tmp->fd == fd)
			return (tmp);
	}
	new = (t_help*)malloc(sizeof(t_help));
	new->entr_str = ft_strdup("");
	new->fd = fd;
	new->next = NULL;
	if (*txt == NULL)
	{
		*txt = new;
		return (new);
	}
	tmp->next = new;
	return (new);
}

char	*ft_str_chr(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (0);
}

size_t	ft_strln(const char *str)
{
	int i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
			i++;
		return (i);
	}
	return (0);
}

int		read_file(char **str, int fd)
{
	char	buf[BUFF_SIZE + 1];
	char	*del_me;
	int		ret;

	ret = 0;
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		del_me = *str;
		*str = ft_strjoin(*str, buf);
		free(del_me);
		if (ft_str_chr(*str, '\n'))
			break ;
	}
	return (ret);
}

int		get_next_line(const int fd, char **line)
{
	static t_help	*txt;
	t_help			*tmp;
	int				ret;
	char			*hlp;
	int				pos;

	pos = 0;
	if (read(fd, "", 0) < 0 || line == NULL)
		return (-1);
	tmp = find_fd(&txt, fd);
	hlp = !tmp->entr_str ? ft_strnew(1) : tmp->entr_str;
	ret = read_file(&hlp, fd);
	if (!ft_strln(hlp) && ret == 0)
	{
		*line = ft_strnew(1);
		return (0);
	}
	(ft_str_chr(hlp, '\n')) ? (pos = (ft_str_chr(hlp, '\n') - hlp)) :
	(pos = ft_strlen(hlp));
	!(ft_str_chr(hlp, '\n')) ? (tmp->entr_str = 0) :
	(tmp->entr_str = ft_strdup(ft_str_chr(hlp, '\n') + 1));
	*line = ft_strsub(hlp, 0, pos);
	free(hlp);
	return (1);
}
