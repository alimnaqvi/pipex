/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:45:33 by anaqvi            #+#    #+#             */
/*   Updated: 2024/11/21 20:37:42 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_file_access(char **argv)
{
	if (access(argv[1], R_OK) == -1)
	{
		ft_putstr_fd(argv[1], 2);
		perror(": Cannot access file for reading");
		exit(EXIT_FAILURE);
	}
	if (access(argv[4], W_OK) == -1)
	{
		ft_putstr_fd(argv[4], 2);
		perror(": Cannot access file for writing");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmd1;
	char	**cmd2;

	if (argc != 5)
		return (0);
	check_file_access(argv);
	cmd1 = get_cmd(argv[1], envp);
	cmd2 = get_cmd(argv[4], envp);
	pipe_and_fork(cmd1, cmd2, envp);
	free_cmds(&cmd1, &cmd2); // in case execve fails (and/or free right after)
	(void)envp;
	return (0);
}
