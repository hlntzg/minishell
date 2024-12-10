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

void    add_tokens(t_token *token, char *str)
{
    lst_add_back(token);
    token->type = str;
}

void    tokenize_characters(char *str, t_token *token)
{
    if (*str == '>')
    {
        if (*(str + 1) == '>')
            add_tokens(token, new_token(APPEND, ">>"));
        else
            add_tokens(token, new_token(REDOUT, ">"));
    }
    else if (*str == '<')
    {
        if (*(str + 1) == '<')
            add_tokens(token, new_token(HEREDOC, "<<"));
        else
            add_tokens(token, new_token(REDIN, "<"));
    }
    else if (*str == '|')
    {
        add_tokens(token, new_token(PIPE, "|"));
    }
    (*str)++;
}

void    tokeinze_words(char **str, t_token **token)
{
    // anything that is not an operator is classified altogether as 
    // a command. The command tokenized, and later the token is 
    // parsed for [arsing errors.

    // what about environment variables? where do I handle those?
}

/* then after this there can be another function: ft_itemize or something that
goes through the entire linked list and adds an enum type to the nodes of the list*/
 /* or a tokenizer that just parses the string and adds items to the 
 linked list straiight from the inut, instead of dividing into nodes first.*/
 t_token *tokenizer(char *str)
 {
    t_token *token;

    while (*str)
    {
        if (lexical_errors(str) == false)
        {
            while (*str == ft_strchr(" \t\n", *str))
                *str++;
            if (*str == "<>|")
                tokenize_characters(str, &token); 
            else
                //tokenize_word
                ;
        }
    }
 }