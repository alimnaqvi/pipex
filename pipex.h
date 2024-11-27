/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:16:19 by anaqvi            #+#    #+#             */
/*   Updated: 2024/11/27 19:55:10 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

// functions to check that input/output files are valid, then open them
void	check_and_open_files(int argc, char **argv, int *in_fd, int *out_fd);

// functions to check if given commands are valid, then make them execve ready
int		check_and_init_cmds(char **argv, char **envp, char ***cmd1,
			char ***cmd2);

// functions to create pipe, fork processes, and execute the commands
pid_t	first_fork_execute(int *fds, char ***cmds, int *pipefd, char **envp);
pid_t	second_fork_execute(int *fds, char ***cmds, int *pipefd, char **envp);
// void	fork_and_execute(int *fds, char ***cmd1, char ***cmd2, char **envp);

// alternative to ft_split that considers everything inside quotes as one 'word'
char	**ft_split_with_quotes(char const *s, char c);

// helper functions
void	free_splits(char ***splits);
void	cleanup_exit(int *fds, char ***cmd1, char ***cmd2, int status);
int		trim_quotes(char **splits);

#endif