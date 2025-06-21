/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cleanup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:37:35 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/21 11:37:37 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

/**
 * clean_exit - Cleans up resources and exits the program.
 * @exit_code: The exit code to return.
 */
void	clean_exit(int exit_code)
{
	gc_cleanup();
	exit(exit_code);
}
