/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:11:19 by anaqvi            #+#    #+#             */
/*   Updated: 2024/11/26 18:44:12 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	handle_infile(char *infile)
{
	int	fd;

	if (access(infile, F_OK | R_OK) == -1)
	{
		perror(infile);
		infile = "/dev/null";
	}
	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror(infile);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static int	handle_outfile(char *outfile)
{
	int	fd;

	if (access(outfile, F_OK) != -1)
	{
		if (access(outfile, W_OK) == -1)
		{
			perror(outfile);
			return (-1);
		}
	}
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(outfile);
	}
	return (fd);
}

void	check_and_open_files(int argc, char **argv, int *in_fd, int *out_fd)
{
	if (argc != 5)
	{
		ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 file2", 2);
		exit(EXIT_FAILURE);
	}
	*in_fd = handle_infile(argv[1]);
	*out_fd = handle_outfile(argv[4]);
	if (*out_fd == -1)
	{
		close(*in_fd);
		exit(EXIT_FAILURE);
	}
}
