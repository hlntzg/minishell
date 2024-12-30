/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:02:53 by nmeintje          #+#    #+#             */
/*   Updated: 2024/12/30 13:02:55 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_builtin(t_data *data, t_tree_node *node)
{
    (void)data;
    if (node->value[0] && ft_strcmp(node->value[0], "echo"))
        printf("here");
        //return (ms_echo(data, node->value));
    return (SUCCESS);
}

int execute_newline(t_data *data, t_tree_node *node)
{
    return (execute_builtin(data, node));
}