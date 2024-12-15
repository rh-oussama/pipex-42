/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_outils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 10:20:14 by orhaddao          #+#    #+#             */
/*   Updated: 2024/01/30 08:56:29 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*read_heredoc(char *limiter)
{
	char	*tmp;
	char	*buffer;
	char	*new_buffer;

	write(1, "heredoc > ", 10);
	buffer = NULL;
	tmp = get_next_line(0);
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp, limiter) == 0)
		{
			free(tmp);
			break ;
		}
		new_buffer = ft_strjoin(buffer, tmp);
		free(buffer);
		buffer = new_buffer;
		free(tmp);
		write(1, "heredoc > ", 10);
		tmp = get_next_line(0);
	}
	get_next_line(INT_MAX);
	return (buffer);
}

int	herdoc_handle(char **argv)
{
	char	*limiter;
	char	*buffer;
	int		pi[2];

	limiter = ft_strjoin(argv[2], "\n");
	buffer = read_heredoc(limiter);
	pipe(pi);
	write(pi[1], buffer, ft_strlen(buffer));
	close(pi[1]);
	free(buffer);
	free(limiter);
	return (pi[0]);
}

void	check_permission(int argc, char **argv, int *fd_open)
{
	if (fd_open[0] == -1)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	if (access(argv[argc - 1], W_OK) != 0)
	{
		perror(argv[argc - 1]);
		exit(EXIT_FAILURE);
	}
}
