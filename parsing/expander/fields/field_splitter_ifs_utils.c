#include "../../../includes/minishell.h"

char    *get_ifs_value(char **env)
{
    char    *ifs_value;

    ifs_value = get_env(env, "IFS");
    if (ifs_value == NULL)
        return (" \t");
    if (ifs_value[0] == '\0')
        return ("");
    return (ifs_value);
}

int is_ifs_char(char c, char *ifs)
{
    int i;

    if (ifs == NULL)
        return (0);
    i = 0;
    while (ifs[i] != '\0')
    {
        if (ifs[i] == c)
            return (1);
        i++;
    }
    return (0);
}

int contains_ifs_character(char *str, char *ifs)
{
    int i;

    if (str == NULL || ifs == NULL || ifs[0] == '\0')
        return (0);
    i = 0;
    while (str[i] != '\0')
    {
        if (is_ifs_char(str[i], ifs))
            return (1);
        i++;
    }
    return (0);
}
