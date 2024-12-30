#include "minishell.h"

/*void print_tokens(t_token *token)
{
    printf("Generated tokens:\n");
    while (token)
    {
        printf("Type: %d, Content: '%s'\n", token->type, token->content);
        token = token->next;
    }
    printf("\n");
}*/

void free_tokens(t_token *token)
{
    t_token *temp;

    while (token)
    {
        temp = token->next; // Save the next token
        if (token->content)
            free(token->content); // Free the token's content
        free(token); // Free the token itself
        token = temp; // Move to the next token
    }
}

//tests lexer with predefined inputs
// bypasses main loop
/*void test_tokenizer(void)
{
    t_token *tokens;
    t_token *current;

    char *test_cases[] = {
        "echo hello world",
        "ls -la > output.txt",
        "| cat < input.txt | grep 'test'",
        "echo \"quoted text\" >> append.txt",
        "invalid < > input",
        " export abc=\"\'value\'\"",
        " echo hello << 3",
        NULL // End marker
    };

    for (int i = 0; test_cases[i] != NULL; i++)
    {
        printf("Test case %d: %s\n", i + 1, test_cases[i]);
        tokens = tokenizer(test_cases[i]);
        if (!tokens)
            printf("Error: Lexical error in input.\n");
        else
        {
            printf("Tokens:\n");
            current = tokens;
            while (current)
            {
                printf("  Type: %d, Value: %s\n", current->type, current->content);
                current = current->next;
            }
        }
        //else
          //  free_tokens(tokens); // Free the token list after each test case
        printf("\n");
    }
}*/

void test_parser(void)
{
    t_token *tokens;
    t_tree_node *ast;
    t_token *current;

    char *test_cases[] = {
        "echo hello world",
        "ls -la > output.txt",
        "| cat < input.txt | grep 'test'",
        "echo \"quoted text\" >> append.txt",
        "invalid < > input",
        "export abc=\"\'value\'\"",
        "echo hello << 3",
        NULL // End marker
    };

    for (int i = 0; test_cases[i] != NULL; i++)
    {
        printf("Test case %d: %s\n", i + 1, test_cases[i]);

        // Tokenize the input
        tokens = tokenizer(test_cases[i]);
        if (!tokens)
        {
            printf("Error: Lexical error in input.\n");
            continue;
        }

        // Print tokens for debugging
        printf("Tokens:\n");
        current = tokens;
        while (current)
        {
            printf("  Type: %d, Value: %s\n", current->type, current->content);
            current = current->next;
        }

        // Parse the tokens into an AST
        ast = parse_tokens(&tokens);
        if (!ast)
        {
            printf("Error: Syntax error in input.\n");
        }
        else
        {
            printf("Abstract Syntax Tree:\n");
            print_ast(ast, 0);
        }

        // Clean up
        free_tokens(tokens);
        free_ast(ast);

        printf("\n");
    }
}

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

void free_ast(t_tree_node *node)
{
    if (!node)
        return;

    // Free left and right subtrees
    free_ast(node->left);
    free_ast(node->right);

    // Free node values
    if (node->value)
    {
        for (int i = 0; node->value[i]; i++)
            free(node->value[i]);
        free(node->value);
    }

    // Free the node itself
    free(node);
}

//test main
/*int main(void)
{
    printf("\033[1;1H\033[2J"); // Clear screen
    test_tokenizer();
    return 0;
}*/
//test main #2
/*int main(void)
{
    printf("\033[1;1H\033[2J"); // Clear screen
    test_parser();
    return 0;
} */

int main(void)
{
    printf("\033[1;1H\033[2J"); // Clear screen

    char *test_cases[] = {
        "echo hello world",
        "ls -la > output.txt",
        "| cat < input.txt | grep 'test'",
        "echo \"quoted text\" >> append.txt",
        "invalid < > input",
        "export abc=\"\'value\'\"",
        "echo hello << 3",
        NULL // End marker
    };

    for (int i = 0; test_cases[i] != NULL; i++)
    {
        printf("Test case %d: %s\n", i + 1, test_cases[i]);

        t_token *tokens = tokenizer(test_cases[i]);
        if (!tokens)
        {
            printf("Error: Lexical error in input.\n");
            continue;
        }

        // Print tokens
        printf("Tokens:\n");
        t_token *current = tokens;
        while (current)
        {
            printf("  Type: %d, Value: %s\n", current->type, current->content);
            current = current->next;
        }

        // Parse tokens into an AST
        t_tree_node *ast = parse_tokens(&tokens);
        if (!ast)
        {
            printf("Error: Parsing failed.\n");
            continue;
        }

        // Generate AST diagram
        printf("Generating AST diagram for test case %d...\n", i + 1);
        generate_ast_diagram(ast);

        // Print path to the output file
        printf("AST diagram saved to 'ast.dot'.\n");
        printf("Use the command 'dot -Tpng ast.dot -o ast.png' to convert it to an image.\n");

        // Free memory
        // free_ast(ast); // If you have a function to free the AST
        // free_tokens(tokens); // Free the token list
    }

    return 0;
}

