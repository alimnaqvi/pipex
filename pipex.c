/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:45:33 by anaqvi            #+#    #+#             */
/*   Updated: 2024/11/22 13:11:43 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	// char	**cmd1;
	// char	**cmd2;
	int		infile_fd;
	int		outfile_fd;

	check_and_open_files(argc, argv, &infile_fd, &outfile_fd);
	// cmd1 = get_cmd(argv[1], envp);
	// cmd2 = get_cmd(argv[4], envp);
	// pipe_and_fork(cmd1, cmd2, envp);
	// free_cmds(&cmd1, &cmd2); // in case execve fails (and/or free right after)
	close(infile_fd);
	close(outfile_fd);
	(void)envp;
	return (0);
}
