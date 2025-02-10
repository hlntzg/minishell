
#include "minishell.h"


t_tree_node *parse_command(t_token **tokens)
{
    t_tree_node	*node;
    int			max_args;
    int			actual_args;

    node = new_tree_node(WORD);
	max_args = argument_count(*tokens) * 2;
	printf("max_args: %d\n", max_args);
	actual_args = 0;
	node->value = malloc(sizeof(char *) * (max_args + 1));
    if (!node->value)
		return (NULL);
    while (*tokens && actual_args < max_args)
    {
        if ((*tokens)->expand && has_space((*tokens)->content))
            process_expanded_token(node->value, &actual_args, &max_args, (*tokens)->content);
        else
        {
            node->value[actual_args] = ft_strdup((*tokens)->content);
            actual_args++;
        }
        free_token(tokens);
    }
	printf("actual_args: %d\n", actual_args);
    node->value[actual_args] = NULL;
    return (node);
}

int expand_count(char *content)
{
    char	**split_tokens;
    int     total;

    split_tokens = ft_split(content, ' ');
    if (!split_tokens)
		return ;
	total = 0;
	while (split_tokens[total])
		total++;
    return (total);
}

char    *split_expansion(char *value, char *content, int *count)
{
    char **split_words;
    int j;

    split_words = ft_split(content, ' ');
    j = 0;
    while (split_words[j])
    {
        value[*count++] = ft_strdup(split_words[j]);
        j++;
    }
    if (split_words)
    {
	    j = 0;
        while (split_words[j])
            free(split_words[j++]);
        free(split_words);
    }
}

t_tree_node *parse_command(t_token **tokens)
{
	t_tree_node	*node;
	int			num;
	int			i;
    t_token		*temp;
    
	node = new_tree_node(WORD);
    if ((*tokens)->expand && has_space((*tokens)->content))
        num = expand_count((*tokens)->content);
    else
    	num = argument_count(*tokens);
	node->value = malloc(sizeof(char *) * (num + 1));
	if (!node->value)
		return (NULL);
	i = 0;
	while (*tokens && i < num)
	{
        if ((*tokens)->expand && has_space((*tokens)->content))
        {
            node->value = split_expansion(node->value, (*tokens)->content, &i);
        }
        else
        	node->value[i++] = ft_strdup((*tokens)->content);
		temp = *tokens;
		*tokens = (*tokens)->next;
		free(temp->content);
		free(temp);
	}
	node->value[i] = NULL;
	return (node);
}
