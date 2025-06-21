#include "../../../includes/minishell.h"

static char    **handle_empty_ifs(char const *s)
{
    char    **result;

    result = (char **)gc_alloc(2 * sizeof(char *));
    if (result == NULL)
        return (NULL);
    result[0] = gc_strdup(s);
    if (result[0] == NULL)
    {
        gc_free(result);
        return (NULL);
    }
    result[1] = NULL;
    return (result);
}

static int wc_ifs(char const *s, char *ifs)
{
    int wc;
    int i;

    if (s == NULL || ifs == NULL || ifs[0] == '\0')
        return (1);
    wc = 0;
    i = 0;
    while (s[i] != '\0')
    {
        while (is_ifs_char(s[i], ifs) == 1
                && s[i] != '\0')
                i++;
        if (is_ifs_char(s[i], ifs) == 0
                && s[i] != '\0')
        {
            wc++;
            while (is_ifs_char(s[i], ifs) == 0
                && s[i] != '\0')
                i++;
        }
    }
    return (wc);
}

static char    **split_words(char const *s, char *ifs, int word_count)
{
    char    **splited;
    size_t  start;
    int     i;
    int     j;

    splited = (char **)gc_alloc((word_count + 1) * sizeof(char *));
    if (splited == NULL)
        return (NULL);
    i = 0;
    j = 0;
    while (s[j] != '\0' && i < word_count)
    {
        while (is_ifs_char(s[j], ifs) == 1
                && s[j] != '\0')
            j++;
        start = j;
        while (is_ifs_char(s[j], ifs) == 0
                && s[j] != '\0')
            j++;
        splited[i] = gc_substr(s, start, j - start);
        if (splited[i] == NULL)
            return (free_fields_array(splited), NULL);
        i++;
    }
    splited[i] = NULL;
    return (splited);
}

char    **split_by_ifs(char const *s, char *ifs)
{
    int word_count;

    if (s == NULL || ifs == NULL)
        return (NULL);
    if (ifs[0] == '\0')
        return (handle_empty_ifs(s));
    word_count = wc_ifs(s, ifs);
    return (split_words(s, ifs, word_count));
}