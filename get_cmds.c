/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:17:34 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/23 19:33:19 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	find_executable(char ***cmd_arr, char **paths)
{
	char	*current_path;
	size_t	len;

	while (*paths)
	{
		len = sizeof(char) * (ft_strlen(*paths) + ft_strlen(**cmd_arr) + 2);
		current_path = malloc(len);
		if (!current_path)
			return (perror("malloc failed"), -1);
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
		return (0);
	free(**cmd_arr);
	**cmd_arr = current_path;
	return (0);
}

static char	**get_cmd(char *cmd_str, char **paths)
{
	char	**cmd_arr;

	cmd_arr = ft_split_with_quotes(cmd_str, ' ');
	if (!cmd_arr)
		return (perror("malloc failed"), NULL);
	if (trim_quotes(cmd_arr) == -1)
		return (free_splits(&cmd_arr), perror("malloc failed"), NULL);
	if (find_executable(&cmd_arr, paths) == -1)
	{
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
		return (perror("malloc failed"), NULL);
	return (paths);
}

int	check_and_init_cmds(char **argv, char **envp, char ***cmd1, char ***cmd2)
{
	char	**paths;

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
