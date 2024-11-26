/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:39:51 by anaqvi            #+#    #+#             */
/*   Updated: 2024/11/26 18:18:53 by anaqvi           ###   ########.fr       */
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
		return (close(fds[0]), close(pipefd[0]), free_splits(cmd2), exit(EXIT_FAILURE));
	}
	close(pipefd[0]);
	close(fds[0]);
	if (execve(*cmd2[0], *cmd2, envp) == -1)
	{
		perror("execve failed");
		return (free_splits(cmd2), exit(EXIT_FAILURE));
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
		return (close(fds[1]), close(pipefd[1]), free_splits(cmd1), exit(EXIT_FAILURE));
	}
	close(pipefd[1]);
	close(fds[1]);
	if (execve(*cmd1[0], *cmd1, envp) == -1)
	{
		perror("execve failed");
		return (free_splits(cmd1), exit(EXIT_FAILURE));
	}
}

static int	set_up_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		return (-1);
	}
	return (0);
}

void	fork_and_execute(int *fds, char ***cmd1, char ***cmd2, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (set_up_pipe(pipefd) == -1)
		cleanup_exit(fds, cmd1, cmd2, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		cleanup_exit(fds, cmd1, cmd2, EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		free_splits(cmd2);
		close(pipefd[0]);
		exec_first_cmd(fds, cmd1, pipefd, envp);
	}
	else
	{
		free_splits(cmd1);
		close(pipefd[1]);
		wait(NULL);
		exec_second_cmd(fds, cmd2, pipefd, envp);
	}
}
