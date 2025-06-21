/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:14:07 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/13 17:14:09 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

/**
 * get_home_dir - Retrieves the HOME environment variable
 * @env: The current environment variables
 * Return: The HOME directory or NULL if not set
 */
static char	*get_home_dir(char **env)
{
	char	*home = get_env(env, "HOME");

	if (home == NULL)
		ft_dprintf(STDERR, "cd: HOME not set\n");
	return (home);
}

/**
 * get_oldpwd_dir - Retrieves the OLDPWD environment variable
 * @env: The current environment variables
 * Return: The OLDPWD directory or NULL if not set
 */
static char	*get_oldpwd_dir(char **env)
{
	char	*oldpwd = get_env(env, "OLDPWD");

	if (oldpwd == NULL)
		ft_dprintf(STDERR, "cd: OLDPWD not set\n");
	return (oldpwd);
}

/**
 * expand_tilde - Expands the tilde (~) in the given argument
 * 		to the home directory
 * @arg: The argument potentially containing a tilde
 * @env: The current environment variables
 * Return: The expanded path or the original argument if no expansion is needed
 */
static char	*expand_tilde(char *arg, char **env)
{
	static char	buf[4096];
	char		*home;

	home = get_home_dir(env);
	if (home == NULL)
		return (NULL);
	if (arg[1] == '/' || arg[1] == '\0')
	{
		ft_strlcpy(buf, home, sizeof(buf));
		ft_strlcat(buf, arg + 1, sizeof(buf));
		return (buf);
	}
	return (arg);
}

/**
 * get_target_directory - Determines the target directory for the cd command
 * @args: The arguments passed to the cd command
 * @env: The current environment variables
 * Return: The target directory as a string, or NULL on failure
 */
static char	*get_target_directory(char **args, char **env)
{
	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
		return (get_home_dir(env));
	else if (ft_strcmp(args[1], "-") == 0)
		return (get_oldpwd_dir(env));
	else if (args[1][0] == '~')
		return (expand_tilde(args[1], env));
	else
		return (args[1]);
}

/**
 * cd_builtin - Changes the current working directory
 * @args: The arguments passed to the cd command
 * @env: The current environment variables
 * Return: 0 on success, 1 on failure
 */
int	cd_builtin(char **args, char **env)
{
	char	*target;
	char	oldpwd[4096];
	char	pwd[4096];
	int		ret;

	target = get_target_directory(args, env);
	if (target == NULL)
	return (1);
	ft_bzero(&oldpwd, sizeof(oldpwd));
	ft_bzero(&pwd, sizeof(pwd));
	getcwd(oldpwd, sizeof(oldpwd));
	ret = chdir(target);
	if (ret == -1)
	{
		ft_dprintf(STDERR, "cd: %s: %s\n", target, strerror(errno));
		return (1);
	}
	set_custom_var("OLDPWD", oldpwd, env);
	getcwd(pwd, sizeof(pwd));
	set_custom_var("PWD", pwd, env);
	return (0);
}
