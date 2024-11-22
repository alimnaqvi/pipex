/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:45:33 by anaqvi            #+#    #+#             */
/*   Updated: 2024/11/22 17:21:05 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**cmd1;
	char	**cmd2;
	int		infile_fd;
	int		outfile_fd;

	check_and_open_files(argc, argv, &infile_fd, &outfile_fd);
	if (check_and_init_cmds(argv, envp, &cmd1, &cmd2) == -1)
	{
		close(infile_fd);
		close(outfile_fd);
		exit(EXIT_FAILURE);
	}
	// pipe and fork logic to come here;
	free_splits(&cmd1);
	free_splits(&cmd2);
	close(infile_fd);
	close(outfile_fd);
	return (0);
}
