#include "minishell.h"

void print_tokens(t_token *token)
{
    printf("Generated tokens:\n");
    while (token)
    {
        printf("Type: %d, Content: '%s'\n", token->type, token->content);
        token = token->next;
    }
    printf("\n");
}

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
void test_tokenizer(void)
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
}