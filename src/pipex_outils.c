/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:23:56 by orhaddao          #+#    #+#             */
/*   Updated: 2024/01/13 16:19:54 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}

char	*get_final_path(char *command, char **envp)
{
	char	**path;
	int		i;
	char	*full_path;
	char	*tmp;

	i = 0;
	path = get_path(envp);
	i = 0;
	if (path == NULL)
		return (NULL);
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			return (free_split(path), full_path);
		free(full_path);
		i++;
	}
	return (free_split(path), NULL);
}

void	dup2_close(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

void	execute_command(char *path, char **args, char **envp)
{
	if (path == NULL && find_char(args[0]) == 1)
	{
		execve(args[0], args, envp);
		ft_error("no such file or directory: ", args[0]);
		free_split(args);
		exit(EXIT_FAILURE);
	}
	execve(path, args, envp);
	ft_error("command not found: ", args[0]);
	free_split(args);
	exit(EXIT_FAILURE);
}
