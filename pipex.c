/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:45:33 by anaqvi            #+#    #+#             */
/*   Updated: 2024/11/24 13:57:15 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_second_cmd(int *fds, char ***cmd2, int *pipefd, char **envp)
{
	if (dup2(fds[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		close(pipefd[0]);
		close(pipefd[1]);
		cleanup_exit(fds, NULL, cmd2, EXIT_FAILURE);
	}
	close(fds[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 failed");
		return (close(fds[0]), cleanup_exit(pipefd, NULL, cmd2, EXIT_FAILURE));
	}
	close(pipefd[0]);
	close(pipefd[1]);
	close(fds[0]);
	if (execve(*cmd2[0], *cmd2, envp) == -1)
	{
		perror("execve failed");
		return (free(cmd2), exit(EXIT_FAILURE));
	}
}

void	exec_first_cmd(int *fds, char ***cmd1, int *pipefd, char **envp)
{
	if (dup2(fds[0], STDIN_FILENO) == -1)
	{
		perror("dup2 failed");
		close(pipefd[0]);
		close(pipefd[1]);
		cleanup_exit(fds, cmd1, NULL, EXIT_FAILURE);
	}
	close(fds[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		return (close(fds[1]), cleanup_exit(pipefd, cmd1, NULL, EXIT_FAILURE));
	}
	close(pipefd[1]);
	close(pipefd[0]);
	close(fds[1]);
	if (execve(*cmd1[0], *cmd1, envp) == -1)
	{
		perror("execve failed");
		return (free(cmd1), exit(EXIT_FAILURE));
	}
}

static int set_up_pipe(int* pipefd)
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
		free_splits(cmd1);
		exec_second_cmd(fds, cmd2, pipefd, envp);
	}
	else
	{
		free_splits(cmd2);
		exec_first_cmd(fds, cmd1, pipefd, envp);
	}
}

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
		cleanup_exit((int []){infile_fd, outfile_fd}, &cmd1, &cmd2, EXIT_FAILURE);
	fork_and_execute((int []){infile_fd, outfile_fd}, &cmd1, &cmd2, envp);
	cleanup_exit((int []){infile_fd, outfile_fd},  &cmd1, &cmd2, EXIT_SUCCESS);
	return (0);
}
