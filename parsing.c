/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:11:44 by nmeintje          #+#    #+#             */
/*   Updated: 2024/12/12 16:11:47 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree_node *parse_redirection(t_tree_node *command, t_token **tokens)
{
	t_tree_node *node;

	if (!tokens || !*tokens)
		return command;
	node = malloc(sizeof(t_tree_node));
	if (!node)
		exit(1);
	node->type = (*tokens)->type; 
	*tokens = (*tokens)->next;  // Move to the next token (the filename)
	if (*tokens && (*tokens)->type == WORD)
	{
		node->value[0] = ft_strdup((*tokens)->content); // Store the filename
		*tokens = (*tokens)->next; // Move past the filename
	}
	else
	{
		fprintf(stderr, "Syntax error: expected file after redirection\n");
		free(node);
		return (command); // Return the original command
	}
	node->left = (command); // Attach the command as the left child
	node->right = NULL;
	return (node);
}

t_tree_node *create_command_node(t_token **tokens)
{
    t_tree_node	*node;
    t_token		*current;
    int			arg_count;

    arg_count = 0;
    node = new_tree_node(*tokens);
    current = *tokens;
    while (current && current->type == WORD) 
    {
        arg_count++;
        current = current->next;
    }
    node->value = malloc(sizeof(char *) * (arg_count + 1)); 
    if (!node->value)
        exit(1);
    arg_count = 0;
    while (*tokens && (*tokens)->type == WORD) 
    {
        node->value[arg_count] = ft_strdup((*tokens)->content);
        if (!node->value[arg_count])
            exit(1); 
        arg_count++;
        *tokens = (*tokens)->next;
    }
    return (node);
}

t_tree_node *parse_command(t_token **tokens)
{
	t_tree_node	*node;

	if (!tokens || !*tokens)
		return (NULL);
	node = create_command_node(tokens);	
	while (*tokens && ((*tokens)->type == REDIN || (*tokens)->type == REDOUT ||
			(*tokens)->type == APPEND || (*tokens)->type == HEREDOC))
			node = parse_redirection(node, tokens);
	return (node);
}

/**
 * parse_pipeline - assigns the tree node the type PIPE
 * 					and the value '|'
 * 
 * it traverses the node until there are no more nodes
 * 
 * Return: returns the node if there are more nodes in the linked list
 *         otherwise it returns the left node
 */
t_tree_node *parse_pipes(t_token **tokens)
{
	t_tree_node *node;
	t_tree_node *left;

	left = parse_command(tokens);
	if (!left)
		return (NULL);
	if (*tokens && (*tokens)->type == PIPE)
	{
		//need to create a new node here probably
		node = malloc(sizeof(t_tree_node));
		if (!node)
			exit(1);
		node->type = PIPE;
		node->left = left;
		*tokens = (*tokens)->next;
		node->right = parse_pipes(tokens); // Parse the rest of the pipeline
		return (node);
	}
	return (left); // No pipe, return the command
}

/**
 * parse_tokens - finds the first pipe in the linked list of tokens
 *                pipes are the highest priority operator
 * 
 * Return: NULL if there are no tokens to parse
 *         else will return the parse_pipeline function
 */
t_tree_node *parse_tokens(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (parse_pipes(tokens));
}