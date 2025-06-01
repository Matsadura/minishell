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
 * get_target_dir - Determines the target directory for cd command
 * @env_list: The head of the environment list
 * @path: The path to change to
 * return: The target directory or NULL if not found
 */
static char	*get_target_dir(t_env **env_list, const char *path)
{
	char	*home;
	char	*oldpwd;

	if (path == NULL || ft_strcmp(path, "~") == 0 || *path == '\0')
	{
		home = get_env(*env_list, "HOME");
		if (home == NULL)
			ft_dprintf(STDERR, "cd: HOME not set\n");
		return (home);
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		oldpwd = get_env(*env_list, "OLDPWD");
		if (oldpwd == NULL)
			ft_dprintf(STDERR, "cd: OLDPWD not set\n");
		return (oldpwd);
	}
	return ((char *)path);
}

/**
 * update_pwd_vars - Updates PWD and OLDPWD environment variables
 * @env_list: The head of the environment list
 * @old_pwd: The previous working directory
 * @return: 0 on success, -1 on failure
 */
static int	update_pwd_vars(t_env **env_list, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		perror("getcwd");
		gc_free(old_pwd);
		return (-1);
	}
	export_var(env_list, "OLDPWD", old_pwd);
	export_var(env_list, "PWD", new_pwd);
	gc_free(old_pwd);
	gc_free(new_pwd);
	return (0);
}

/**
 * change_dir - Changes the current working directory and updates PWD/OLDPWD
 * @env_list: The head of the environment list
 * @path: The path to change to
 * @return: 0 on success, -1 on failure
 */
int	change_dir(t_env **env_list, const char *path)
{
	char	*old_pwd;
	char	*target;

	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		return (perror("getcwd"), -1);
	target = get_target_dir(env_list, path);
	if (target == NULL)
		return (-1);
	if (chdir(target) == -1)
	{
		perror("cd");
		return (-1);
	}
	return (update_pwd_vars(env_list, old_pwd));
}
