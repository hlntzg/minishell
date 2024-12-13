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

void free_ast(t_tree_node *node)
{
    if (!node)
        return;
    free(node->value);
    free_ast(node->left);
    free_ast(node->right);
    free(node);
}
