/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:20:44 by anaqvi            #+#    #+#             */
/*   Updated: 2024/11/22 17:21:09 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_splits(char ***splits)
{
	int	i;

	if (!*splits)
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
