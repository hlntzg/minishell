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
    if (ft_strequ(node->value[0], "echo"))
        return (ms_echo(data, node));
    /*else
        return (ms_exe_simple_cmd(data, node)); // need some explanation */
    return (SUCCESS);
}

int execute_newline(t_data *data, t_tree_node *node)
{
    return (execute_builtin(data, node));
}