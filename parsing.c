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

/* this function will Handle commands and arguments*/
t_tree_node *parse_command(t_token **tokens)
{
    t_tree_node *cmd_node;
    t_token     *current;

    if (*tokens == NULL || (*tokens)->type != CMD)
        return NULL;
    cmd_node = create_tree_node(CMD, (*tokens)->content);
    current = (*tokens)->next;
    while (current != NULL && current->type == ARG)
    {
        add_to_value_array(cmd_node, current->content);
        current = current->next;
    }
    *tokens = current;
    return (cmd_node);
}

//parse_tokens_until

/* This function handles pipes first which 
have the highest precedence in shell syntax
@parse_tokens_until ->  will parse Everything before the pipe*/

t_tree_node *parse_tokens(t_token **tokens)
{
    t_tree_node *node;
    t_token     *current;

    if (*tokens == NULL)
        return NULL;
    current = *tokens;
    while (current != NULL)
    {
        if (current->type == PIPE)
        {
            node = create_tree_node(PIPE, NULL);
            node->left = parse_tokens_until(tokens, PIPE); 
            *tokens = current->next;
            node->right = parse_tokens(tokens);
            return node;
        }
        current = current->next;
    }
    return (parse_command(tokens));
}

