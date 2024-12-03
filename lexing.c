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

//will the "prompt >" be included in the string?
t_token   *ft_tokenize(int num, char **str)
{
    t_token   *token;
    int     i;
    int     j;

    i = 1;
    token = NULL;
    if (num < 2)
        //error
    while (i < num)
    {
        j = str[i];
        // add the type here or in another function
        ft_lstadd_back(&token, ft_lstnew(j));
        i++;
    }
    return (token);
}

/*
//this slit function needs to skkip over all white spaces including tabs.
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
 /* or a tokenizer that just parses the string and adds items to the 
 linked list straiight from the inut, instead of dividing into nodes first.*/
 t_token tokenizer(char *str)
 {
    while (*str)
    {
        while (*str == /* some white space*/)
            *str++;
        if (*str == "<>|")
            //tokenize_special_chars
        else
            //tokenize_word
    }
 }