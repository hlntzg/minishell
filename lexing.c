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
        if (*(*str + 1) == '>')
        {
            add_tokens(token, new_token(APPEND, ">>"));
            (*str)++;
        }
        else
            add_tokens(token, new_token(REDOUT, ">"));
    }
    else if (**str == '<')
    {
        if (*(*str + 1) == '<')
        {
            add_tokens(token, new_token(HEREDOC, "<<"));
            (*str)++;
        }
        else
            add_tokens(token, new_token(REDIN, "<"));
    }
    else if (**str == '|')
        add_tokens(token, new_token(PIPE, "|"));
    (*str)++;
}

void    tokenize_words(char *str, t_token **token)
{
    int     s_quote;
    int     d_quote;
    char    *temp;
    char    *word;

    temp = str;
    while (*str)
    {
        quote_count(str, &s_quote, &d_quote);
        if (!(s_quote % 2) && !(d_quote % 2)
            && ft_strchr(" \t\n><|", *str))
            break ;
        str++;
    }
    if (*str > *temp)
    {
        word = ft_strndup(temp, *str - *temp);
        if (word)
        {
            add_tokens(token, new_token(WORD, word));
            free(word);
        }
    }
}

 t_token *tokenizer(char *str)
 {
    t_token *token;

    token = NULL;
    while (*str)
    {
        if (lexical_errors(str) == false)
        {
            while (*str && ft_strchr(" \t\n", *str))
                str++;
            if (ft_strchr("><|", *str))
                tokenize_characters(&str, &token); 
            else
                tokenize_words(str, &token);
        }
        printf("%s\n", token->content);
    }
    return (token);
 }