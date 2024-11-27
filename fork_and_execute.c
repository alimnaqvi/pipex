/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:39:51 by anaqvi            #+#    #+#             */
/*   Updated: 2024/11/27 20:00:17 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_second_cmd(int *fds, char ***cmd2, int *pipefd, char **envp)
{
	if (dup2(fds[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		close(pipefd[0]);
		cleanup_exit(fds, NULL, cmd2, EXIT_FAILURE);
	}
	close(fds[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 failed");
		return (close(fds[0]), close(pipefd[0]), free_splits(cmd2),
			exit(EXIT_FAILURE));
	}
	close(pipefd[0]);
	close(fds[0]);
	if (execve(*cmd2[0], *cmd2, envp) == -1)
	{
		perror(*cmd2[0]);
		return (free_splits(cmd2), exit(127));
	}
}

static void	exec_first_cmd(int *fds, char ***cmd1, int *pipefd, char **envp)
{
	if (dup2(fds[0], STDIN_FILENO) == -1)
	{
		perror("dup2 failed");
		close(pipefd[1]);
		cleanup_exit(fds, cmd1, NULL, EXIT_FAILURE);
	}
	close(fds[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		return (close(fds[1]), close(pipefd[1]), free_splits(cmd1),
			exit(EXIT_FAILURE));
	}
	close(pipefd[1]);
	close(fds[1]);
	if (execve(*cmd1[0], *cmd1, envp) == -1)
	{
		perror(*cmd1[0]);
		return (free_splits(cmd1), exit(127));
	}
}

pid_t	first_fork_execute(int *fds, char ***cmds, int *pipefd, char **envp)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork failed");
		cleanup_exit(fds, cmds, cmds + 1, EXIT_FAILURE);
	}
	else if (pid1 == 0)
	{
		free_splits(cmds + 1);
		close(pipefd[0]);
		exec_first_cmd(fds, cmds, pipefd, envp);
	}
	return (pid1);
}

pid_t	second_fork_execute(int *fds, char ***cmds, int *pipefd, char **envp)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork failed");
		cleanup_exit(fds, cmds, cmds + 1, EXIT_FAILURE);
	}
	else if (pid2 == 0)
	{
		free_splits(cmds);
		close(pipefd[1]);
		exec_second_cmd(fds, cmds + 1, pipefd, envp);
	}
	return (pid2);
}
