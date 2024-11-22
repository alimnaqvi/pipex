/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:16:19 by anaqvi            #+#    #+#             */
/*   Updated: 2024/11/22 17:21:36 by anaqvi           ###   ########.fr       */
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

// helper functions
void	free_splits(char ***splits);

#endif