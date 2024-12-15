/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_outils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:16:30 by orhaddao          #+#    #+#             */
/*   Updated: 2024/01/13 17:04:45 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_char(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_error(char *msg, char	*pgname)
{
	char	*buffer;
	char	*tmp;

	buffer = ft_strjoin(msg, pgname);
	tmp = ft_strjoin(buffer, "\n");
	write(2, tmp, ft_strlen(tmp));
	free(tmp);
	free(buffer);
}
