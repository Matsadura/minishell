/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:46:28 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/14 18:46:30 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

/**
 * cleanup_and_exit - Cleanup function
 * @exit_code: The exit code to return
 */
void	cleanup_and_exit(int exit_code)
{
	gc_cleanup();
	rl_clear_history();
	exit(exit_code);
}
