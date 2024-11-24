/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:17:34 by anaqvi            #+#    #+#             */
/*   Updated: 2024/11/24 14:56:42 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	handle_rel_abs_path(char *str)
{
	if (access(str, F_OK) == -1)
	{
		ft_putendl_fd(str, 2);
		perror(": Command not found");
		return (-1);
	}
	if (access(str, X_OK) == -1)
	{
		ft_putendl_fd(str, 2);
		perror(": Command could not be accessed for execution");
		return (-1);
	}
	return (0);
}

static int	find_executable(char ***cmd_arr, char **paths)
{
	char	*current_path;
	size_t	len;

	if (***cmd_arr == '/' || ***cmd_arr == '.')
		return (handle_rel_abs_path(**cmd_arr));
	while (*paths)
	{
		len = sizeof(char) * (ft_strlen(*paths) + ft_strlen(**cmd_arr) + 2);
		current_path = malloc(len);
		if (!current_path)
			return (-1);
		ft_strlcpy(current_path, *paths, len);
		ft_strlcat(current_path, "/", len);
		ft_strlcat(current_path, **cmd_arr, len);
		if (access(current_path, X_OK) == 0)
			break ;
		free(current_path);
		current_path = NULL;
		paths++;
	}
	if (!current_path)
		return (-1);
	free(**cmd_arr);
	**cmd_arr = current_path;
	return (0);
}

static char	**get_cmd(char *cmd_str, char **paths)
{
	char	**cmd_arr;

	cmd_arr = ft_split(cmd_str, ' ');
	if (!cmd_arr)
	{
		perror("malloc failed");
		return (NULL);
	}
	if (find_executable(&cmd_arr, paths) == -1)
	{
		ft_putstr_fd(*cmd_arr, 2);
		ft_putendl_fd(": command not found", 2);
		free_splits(&cmd_arr);
		return (NULL);
	}
	return (cmd_arr);
}

static char	**get_paths(char **envp)
{
	char	**paths;

	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			break ;
		envp++;
	}
	if (!(*envp))
	{
		ft_putendl_fd("PATH variable could not be found in the environment", 2);
		return (NULL);
	}
	paths = ft_split((*envp) + 5, ':');
	if (!paths)
	{
		perror("malloc failed");
		return (NULL);
	}
	return (paths);
}

int	check_and_init_cmds(char **argv, char **envp, char ***cmd1, char ***cmd2)
{
	char	**paths;

	if (!*argv[2] || !*argv[3])
	{
		ft_putendl_fd("Error: Empty command", 2);
		return (-1);
	}
	paths = get_paths(envp);
	if (!paths)
		return (-1);
	*cmd1 = get_cmd(argv[2], paths);
	if (!(*cmd1))
		return (free_splits(&paths), -1);
	*cmd2 = get_cmd(argv[3], paths);
	if (!(*cmd2))
		return (free_splits(cmd1), free_splits(&paths), -1);
	return (free_splits(&paths), 0);
}
