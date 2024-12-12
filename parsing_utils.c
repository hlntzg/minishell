/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:21:20 by nmeintje          #+#    #+#             */
/*   Updated: 2024/12/12 16:21:22 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree_node *create_tree_node(t_type type, char *value)
{
    t_tree_node *node = malloc(sizeof(t_tree_node));
    node->type = type;
    node->value = value ? strdup(value) : NULL;
    node->index = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}