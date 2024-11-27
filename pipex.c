/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:45:33 by anaqvi            #+#    #+#             */
/*   Updated: 2024/11/27 12:23:24 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**cmd1;
	char	**cmd2;
	int		infile_fd;
	int		outfile_fd;

	cmd1 = NULL;
	cmd2 = NULL;
	check_and_open_files(argc, argv, &infile_fd, &outfile_fd);
	if (check_and_init_cmds(argv, envp, &cmd1, &cmd2) == -1)
		cleanup_exit((int []){infile_fd, outfile_fd}, &cmd1, &cmd2,
			EXIT_FAILURE);
	fork_and_execute((int []){infile_fd, outfile_fd}, &cmd1, &cmd2, envp);
	cleanup_exit((int []){infile_fd, outfile_fd}, &cmd1, &cmd2, EXIT_SUCCESS);
	return (0);
}
