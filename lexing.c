/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:09:26 by nmeintje          #+#    #+#             */
/*   Updated: 2024/11/29 10:10:05 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*necessary helper functions
ft_lstadd_back
ft_lstnew
an error function*/

t_tok   *ft_tokenize(int ac, char **av)
{
    t_tok   *token;
    int     i;
    int     j;

    i = 1;
    token = NULL;
    if (ac < 2)
        //error
    while (i < ac)
    {
        j = av[i];
        // add the type here or in another function
        ft_lstadd_back(&token, ft_lstnew(j));
        i++;
    }
    return (token);
}

/*
t_stack *ft_split_string(char **argv)
{
        t_stack *stack_a;
        char    **temp;
        int             i;
        int             j;

        stack_a = NULL;
        i = 0;
        temp = ft_split(argv[1], ' ');
        while (temp[i])
        {
                j = ft_atoi(temp[i]);
                ft_lstadd_back(&stack_a, ft_lstnew(j));
                i++;
        }
        ft_free_str(temp);
        return (stack_a);
}
*/

/* then after this there can be another function: ft_itemize or something that
goes through the entire linked list and adds an enum type to the nodes of the list*/
