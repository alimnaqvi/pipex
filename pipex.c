/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:45:33 by anaqvi            #+#    #+#             */
/*   Updated: 2024/11/27 19:58:36 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static int	set_up_pipe(int *pipefd)
// {
// 	if (pipe(pipefd) == -1)
// 	{
// 		perror("pipe failed");
// 		return (-1);
// 	}
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	char	**cmds[2];
	int		fds[2];
	int		pipefd[2];
	pid_t	pids[2];
	int		statuses[2];

	cmds[0] = NULL;
	cmds[1] = NULL;
	check_and_open_files(argc, argv, fds, fds + 1);
	if (check_and_init_cmds(argv, envp, cmds, cmds + 1) == -1)
		cleanup_exit(fds, cmds, cmds + 1, EXIT_FAILURE);
	if (pipe(pipefd) == -1)
		return (perror("pipe failed"), cleanup_exit(fds, cmds, cmds + 1, EXIT_FAILURE), 1);
	// if (set_up_pipe(pipefd) == -1)
	// 	cleanup_exit(fds, cmds, cmds + 1, EXIT_FAILURE);
	pids[0] = first_fork_execute(fds, cmds, pipefd, envp);
	pids[1] = second_fork_execute(fds, cmds, pipefd, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pids[0], statuses, 0);
	waitpid(pids[1], statuses + 1, 0);
	if (((statuses[1]) & 0x7f) == 0)
		cleanup_exit(fds, cmds, cmds + 1, ((statuses[1]) & 0xff00) >> 8);
	cleanup_exit(fds, cmds, cmds + 1, EXIT_FAILURE);
	//
	// fork_and_execute(fds, cmds, cmds + 1, envp);
	// cleanup_exit(fds, cmds, cmds + 1, EXIT_SUCCESS);
	return (0);
}
