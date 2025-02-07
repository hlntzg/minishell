/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:11:44 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/03 13:07:01 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void process_expanded_token(char **value, int *actual_args, int *max_args, char *content)
{
    char	**split_tokens;
	int		i;
	int		j;
	int		total;
	
	(void)max_args;
	split_tokens = ft_split(content, ' ');
	if (!split_tokens)
		return ;
	i = 0;
    while (split_tokens && split_tokens[i])
    {
		//allocate additional memory for extra items. or just for one extra item?
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
}

t_tree_node *parse_command(t_token **tokens)
{
    t_tree_node	*node;
    int			max_args;
    int			actual_args;

    node = new_tree_node(WORD);
	max_args = argument_count(*tokens) * 2;
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
    node->value[actual_args] = NULL;
    return (node);
}

t_tree_node	*parse_redirection(t_token **tokens)
{
	t_token		*temp;
	t_token		*nxt;
	t_tree_node	*node;

	if (!*tokens)
		return (NULL);
	temp = *tokens;
	if ((*tokens)->type >= REDIN && (*tokens)->type <= HEREDOC)
		return (create_redirection(tokens, temp));
	while (*tokens && (*tokens)->next)
	{
		nxt = (*tokens)->next;
		if ((*tokens)->next->type >= REDIN && (*tokens)->next->type <= HEREDOC)
		{
			node = new_tree_node((*tokens)->next->type);
			(*tokens)->next = nxt->next->next;
			node->left = parse_redirection(&temp);
			node->right = create_file_node((nxt->next));
			return (free(nxt->content), free(nxt), node);
		}
		*tokens = nxt;
	}
	return (parse_command(&temp));
}

t_tree_node	*parse_pipes(t_token **tokens)
{
	t_token		*temp;
	t_token		*nxt;
	t_tree_node	*node;

	temp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		nxt = (*tokens)->next;
		if ((*tokens)->next->type == PIPE)
		{
			node = new_tree_node((*tokens)->next->type);
			(*tokens)->next = NULL;
			node->left = parse_redirection(&temp);
			//printf("after parse command: [0] %s [1] %s\n,", node->left->value[0], node->left->value[1]);
			node->right = parse_pipes(&(nxt->next));
			return (free(nxt->content), free(nxt), node);
		}
		*tokens = nxt;
	}
	return (parse_redirection(&temp));
}

t_tree_node	*parse_tokens(t_token **tokens)
{
	t_tree_node	*tree;	

	if (!tokens || !*tokens)
		return (NULL);
	tree = parse_pipes(tokens);
	//printf("after parse command: [0] %s [1] %s [2] %s\n,", tree->value[0], tree->value[1], tree->value[2]);
	return (tree);
}
