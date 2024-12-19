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
        if (*(*str + 1) && *(*str + 1) == '>')
        {
            add_tokens(token, new_token(APPEND, ">>"));
            //(*str)++;
        }
        else
            add_tokens(token, new_token(REDOUT, ">"));
    }
    else if (**str == '<')
    {
        if (*(*str + 1) && *(*str + 1) == '<')
        {
            add_tokens(token, new_token(HEREDOC, "<<"));
            //(*str)++;
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
    t_token *new;

    temp = str;
    s_quote = 0;
    d_quote = 0;
    while (*str)
    {
        quote_count(str, &s_quote, &d_quote);
        if (!(s_quote % 2) && !(d_quote % 2)
            && ft_strchr(" \t\n><|", *str))
            break ;
        str++;
    }
    printf("temp: '%s', str: '%s'\n", temp, str);
    if (str > temp)
    {
        printf("temp: '%s', str: '%s'\n", temp, str);
        word = ft_strndup(temp, str - temp);
        if (word)
        {
            new = new_token(WORD, word);
            if (new)
                add_tokens(token, new);
            else
                free(word);
        }
    }
}

void print_tokens(t_token *token);


// This function is returning NULL! why?
t_token *tokenizer(char *str)
{
    t_token *token;

    //token = NULL;
    while (*str)
    {
        printf("current string: '%s'\n", str);
        if (no_lexical_errors(str) == false)
            return (NULL);
        while (*str && ft_strchr(" \t\n", *str))
            str++;
        if (ft_strchr("><|", *str))
            tokenize_characters(&str, &token); 
        else
            tokenize_words(str, &token);
        printf("%s\n", token->content);
    }
    print_tokens(token);
    return (token);
 }
