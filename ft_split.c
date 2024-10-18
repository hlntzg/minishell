#include <stdlib.h>

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	word_count(char *str)
{
	int	i = 0;

	while (*str)
	{
		while (*str && is_space(*str))
			str++;
		if (*str && !is_space(*str))
		{
			i++;
			while (*str && !is_space(*str))
				str++;
		}
	}
	return (i);
}

char	**ft_split(char *str)
{
	int	i;
	int	j = 0;
	int	k;
	char	**array;

	array = (char **)malloc(sizeof(char *) * (word_count(str) + 1));
	if (!array)
		return (NULL);
	while (*str)
	{
		if (*str && !is_space(*str))
		{
			i = 0;
			while (str[i] && !is_space(str[i]))	// just to get the lenght of string
				i++;
			array[j] = (char *)malloc(sizeof(char) * (i + 1));
			if (!array[j])
			{
				while (j > 0)			// return to previous string
					free(array[--j]);	// free the string and previous strings
				free(array);			// free the array of strings
				return (NULL);
			}
			k = 0;					// needs to be initialize each new string!
			while (*str && !is_space(*str))
				array[j][k++] = *str++;
			array[j][k] = '\0';
			j++;
		}
		else // skip spaces and start in a non-space character
			str++;
	}
	array[j] = NULL;
	return (array);
}
