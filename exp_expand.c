test;

/*t_tree_node	*parse_command(t_token **tokens)
{
	t_tree_node	*node;
	int			num;
	int			i;
	t_token		*temp;
	char		**split_tokens;

	node = new_tree_node(WORD);
	num = argument_count(*tokens);
	node->value = malloc(sizeof(char *) * (num + 1));
	if (!node->value)
		return (NULL);
	i = 0;
	while (i < num)
	{
		if ((*tokens)->expand)
		{
			split_tokens = ft_split((*tokens)->content, ' ');
			while (split_tokens && split_tokens[0] != NULL)
			{
				node->value[i] = ft_strdup(split_tokens[0]);
				i++;
				split_tokens++;
			}
			//free(split_tokens - i);
		}
		else
			node->value[i] = ft_strdup((*tokens)->content);
		temp = *tokens;
		*tokens = (*tokens)->next;
		free(temp->content);
		free(temp);
		temp = NULL;
		i++;
	}
	node->value[i] = NULL;
	return (node);
}*/

/*t_tree_node	*parse_command(t_token **tokens)
{
	t_tree_node	*node;
	int			max_args;
	int			actual_args;
	int			i, j;
	t_token		*temp;
	char		**split_tokens;

	node = new_tree_node(WORD);
	max_args = argument_count(*tokens) * 2; // Allocate extra space
	node->value = malloc(sizeof(char *) * (max_args + 1));
	if (!node->value)
		return (NULL);
	
	actual_args = 0;
	while (*tokens && actual_args < max_args)
	{
		if ((*tokens)->expand)
		{
			split_tokens = ft_split((*tokens)->content, ' ');
			i = 0;
			while (split_tokens && split_tokens[i] && actual_args < max_args)
			{
				node->value[actual_args] = ft_strdup(split_tokens[i]);
				actual_args++;
				i++;
			}
			// Free split_tokens properly
			if (split_tokens)
			{
				for (j = 0; split_tokens[j]; j++)
					free(split_tokens[j]);
				free(split_tokens);
			}
		}
		else
		{
			node->value[actual_args] = ft_strdup((*tokens)->content);
			actual_args++;
		}
		temp = *tokens;
		*tokens = (*tokens)->next;
		free(temp->content);
		free(temp);
	}
	node->value[actual_args] = NULL;

	return (node);
} */


/*static void process_expanded_token(char **value, int *actual_args, int max_args, char *content)
{
    char **split_tokens = ft_split(content, ' ');
    int i = 0, j;

    while (split_tokens && split_tokens[i] && *actual_args <= max_args)
    {
        value[*actual_args] = ft_strdup(split_tokens[i]);
        (*actual_args)++;
        i++;
    }

    if (split_tokens)
    {
        for (j = 0; split_tokens[j]; j++)
            free(split_tokens[j]);
        free(split_tokens);
    }
} */


/*t_tree_node *parse_command(t_token **tokens)
{
    t_tree_node *node;
    int         max_args;
    int         actual_args;
    int         has_content;  // New flag to track if we have any real content

    if (!tokens || !*tokens)
        return NULL;

    node = new_tree_node(WORD);
    if (!node)
        return NULL;

    max_args = argument_count(*tokens) * 2;
    actual_args = 0;
    has_content = 0;  // Initialize flag

    node->value = malloc(sizeof(char *) * (max_args + 1));
    if (!node->value)
    {
        free(node);
        return NULL;
    }

    while (*tokens && actual_args < max_args)
    {
        // For expanded tokens (like $VARIABLE)
        if ((*tokens)->expand)
        {
            // Skip empty expanded variables
            if (!(*tokens)->content)
            {
                free_token(tokens);
                continue;
            }
            
            if (has_space((*tokens)->content))
            {
				process_expanded_token(node->value, &actual_args, &max_args, (*tokens)->content);

				/*{
                    for (int i = 0; i < actual_args; i++)
                        free(node->value[i]);
                    free(node->value);
                    free(node);
                    return NULL;
                }
            }
            else
            {
                node->value[actual_args] = ft_strdup((*tokens)->content);
                actual_args++;
            }
            has_content = 1;  // We found some content
        }
        // For non-expanded tokens
        else if ((*tokens)->content)
        {
            node->value[actual_args] = ft_strdup((*tokens)->content);
            actual_args++;
            has_content = 1;  // We found some content
        }
        free_token(tokens);
    }
    
    // If we didn't find any real content
    if (!has_content || actual_args == 0)
    {
        for (int i = 0; i < actual_args; i++)
            free(node->value[i]);
        free(node->value);
        free(node);
        return NULL;
    }
    
    node->value[actual_args] = NULL;
    return (node);
}*/





/*static void process_expanded_token(char **value, int *actual_args, int *max_args, char *content)
{
    char	**split_tokens;
	//char	**new_value;
	int		i;
	int		j;
	int		total;
		
	(void)max_args;
	split_tokens = ft_split(content, ' ');
	if (!split_tokens)
		return ;
	total = 0;
	while (split_tokens[total])
		total++;
	i = 0;
    while (split_tokens && split_tokens[i])
    {
		//new_value = malloc(sizeof(char *) * (total + 1));
		//allocate additional memory for extra items. or just for one extra item?
		//value = new_value;
        value[*actual_args] = ft_strdup(split_tokens[i++]);
        (*actual_args)++;
    }
    if (split_tokens)
    {
		j = 0;
        while (split_tokens[j])
            free(split_tokens[j++]);
        free(split_tokens);
    }
}*/

/*t_tree_node *parse_command(t_token **tokens)
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
}*/
