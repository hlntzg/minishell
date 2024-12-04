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

void    tokenize_characters(char **str, t_token **token)
{
    if (**str == '>')
    {
        /*use lst_add_back and lst_new for this*/
        /* if another > then APPEND
        else REDOUT*/
    }
    else if (**str == '<')
    {
        /* if another < then HEREDOC
        else REDIN*/
    }
    else if (**str == '|')
    {
        /* PIPE */
    }
    (*str)++;
}

void    tokeinze_words(char **str, t_token **token)
{}

/* then after this there can be another function: ft_itemize or something that
goes through the entire linked list and adds an enum type to the nodes of the list*/
 /* or a tokenizer that just parses the string and adds items to the 
 linked list straiight from the inut, instead of dividing into nodes first.*/
 t_token tokenizer(char *str)
 {
    while (*str)
    {
        while (*str == ft_strchr(" \t\n", *str))
            *str++;
        if (*str == "<>|")
            //tokenize_special_chars
        else
            //tokenize_word
    }
 }