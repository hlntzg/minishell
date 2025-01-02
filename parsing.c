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
	node->type = (*tokens)->type; // should move to next node and next token
	*tokens = (*tokens)->next;  // Move to the next token (the filename)
	if (*tokens && (*tokens)->type == WORD)
	{
		//node->value[0] = ft_strdup((*tokens)->content); // Store the filename
		node->value = malloc(sizeof(char *) * 2); // Allocate memory for one filename and a NULL terminator
		if (!node->value)
    		exit(1); // Handle memory allocation failure
		node->value[0] = ft_strdup((*tokens)->content); // Store the filename
		if (!node->value[0])
    		exit(1); // Handle strdup failure
		node->value[1] = NULL; // NULL-terminate the value array
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
		//node->type = CMD;
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
	while (*tokens && ((*tokens)->type == REDIN || (*tokens)->type == REDOUT_T ||
			(*tokens)->type == REDOUT_A || (*tokens)->type == HEREDOC))
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
		node->value = malloc(sizeof(char *) * 2);
    if (!node->value)
        exit(1);
    node->value[0] = ft_strdup("|");
    node->value[1] = NULL;
		node->left = left;
		*tokens = (*tokens)->next;
		node->right = parse_pipes(tokens); // Parse the rest of the pipeline
		return (node);
	}
	return (left); // No pipe, return the command
}

/*void print_tree(t_tree_node *tree)
{
    if (!tree)
        return;
    printf("Node type: %d\n", tree->type);
    if (tree->value)
    {
        printf("Node value: ");
        for (int i = 0; tree->value[i]; i++)
            printf("%s ", tree->value[i]);
        printf("\n");
    }
    print_tree(tree->left);
    print_tree(tree->right);
}*/

/**
 * parse_tokens - finds the first pipe in the linked list of tokens
 *                pipes are the highest priority operator
 * 
 * Return: NULL if there are no tokens to parse
 *         else will return the parse_pipeline function
 */
t_tree_node *parse_tokens(t_token **tokens)
{
	t_tree_node	*tree;	
	if (!tokens || !*tokens)
		return (NULL);
	tree = parse_pipes(tokens);
	//print_tree(tree);
	return (tree);
}
