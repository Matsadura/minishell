/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:20:51 by zzaoui            #+#    #+#             */
/*   Updated: 2025/05/30 15:20:53 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * change_dir_home - Changes the current working directory to the home directory
 * @env_list: The head of the environment list
 * @return: 0 on success, -1 on failure
 */
static int	change_dir_home(t_env **env_list)
{
	char	*home;

	home = get_env(*env_list, "HOME");
	if (home == NULL)
	{
		ft_dprintf(STDERR, "cd: HOME not set\n");
		return (-1);
	}
	if (change_dir(env_list, home) == -1)
		return (-1);
	return (0);
}

/**
 * change_dir_previous - Changes the current working directory
 * 		to the previous directory
 * @env_list: The head of the environment list
 * @return: 0 on success, -1 on failure
 */
static int	change_dir_previous(t_env **env_list)
{
	char	*oldpwd;
	char	*new_oldpwd;

	oldpwd = get_env(*env_list, "OLDPWD");
	if (oldpwd == NULL)
	{
		ft_dprintf(STDERR, "cd: OLDPWD not set\n");
		return (-1);
	}
	if (change_dir(env_list, oldpwd) == -1)
		return (-1);
	new_oldpwd = getcwd(NULL, 0);
	if (new_oldpwd == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	export_var(env_list, "OLDPWD", new_oldpwd);
	gc_free(new_oldpwd);
	return (0);
}

/**
 * change_dir - Changes the current working directory,
 * 		only absolute and relative paths
 * @env_list: The head of the environment list
 * @path: The path to change to
 * @return: 0 on success, -1 on failure
 */
int	change_dir(t_env **env_list, const char *path)
{
	char	*new_pwd;

	if (ft_strcmp(path, "-") == 0)
		return (change_dir_previous(env_list));
	if (ft_strcmp(path, "~") == 0 || *path == '\0')
		return (change_dir_home(env_list));
	if (chdir(path) == -1)
	{
		perror("cd");
		return (-1);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	export_var(env_list, "PWD", new_pwd);
	gc_free(new_pwd);
	return (0);
}
