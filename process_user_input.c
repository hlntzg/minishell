/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_user_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:12:08 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/07 11:40:34 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_ast(t_tree_node *node, int depth)
{
    if (!node)
        return;

    // Print indentation for tree structure
    for (int i = 0; i < depth; i++)
        printf("  ");

    // Print node details
    printf("Node type: %d\n", node->type);
    if (node->value)
    {
        for (int i = 0; node->value[i]; i++)
        {
            for (int j = 0; j < depth; j++)
                printf("  "); // Indent values
            printf("  Value[%d]: %s\n", i, node->value[i]);
        }
    }

    // Recursively print left and right children
    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}

int	process_user_input(t_data *data, char *str, int *status)
{
	char	*temp;
	t_token	*token;

	temp = ft_strtrim(str, " \t\n\v\f\r");
	free(str);
	if (!temp)
		return (FAILURE);
	token = tokenizer(data, temp);
	if (!token)
	{
		data->exit_code = 2;
		free(temp);
		return (FAILURE);
	}
	free(temp);
	if (data->count_heredoc > 16)//exit bash with code 2
	{
	//	data->count_heredoc = 0;
		*status = 2;
		ft_putendl_fd("minishell: maximum here-document count exceeded", STDERR_FILENO);
		free_tokens(token);
		free_and_exit_minishell(data, *status);
	}
	expand_variables(token, data->env, data->exit_code);
	//printf("$ exit code: %d\n", data->exit_code);
//	printf("process_user_input: token BEFORE %s\n", token->content);
	data->tree = parse_tokens(&token);
//	if (token)
//		printf("process_user_input: token AFTER\n");//%s\n", token->content);
	if (data->tree == NULL)
	{
		free_tokens(token);
		return (FAILURE);
	}
//	print_ast(data->tree, 5);
	return (SUCCESS);
}
