/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:20:44 by anaqvi            #+#    #+#             */
/*   Updated: 2024/11/24 13:37:23 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_splits(char ***splits)
{
	int	i;

	if (!splits || !*splits)
		return ;
	i = 0;
	while ((*splits)[i])
	{
		free((*splits)[i]);
		i++;
	}
	free(*splits);
	*splits = NULL;
}

void	cleanup_exit(int *fds, char ***cmd1, char ***cmd2, int status)
{
	close(fds[0]);
	close(fds[1]);
	free_splits(cmd1);
	free_splits(cmd2);
	exit(status);
}
