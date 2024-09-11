#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char *input;
    t_token *tokens;
    t_command *command;

    while (1) {
        // Display prompt and read input
        input = readline("minishell> ");
        if (!input) {
            printf("exit\n");
            break;
        }

        // Tokenize input
        tokens = tokenize_input(input);
        if (!tokens) {
            free(input);
            continue;
        }

        // Check syntax
        if (check_syntax(tokens) != 0) {
            print_syntax_error("Syntax error");
            free_tokens(tokens);
            free(input);
            continue;
        }

        // Parse commands
        command = parse_command(tokens);
        if (!command) {
            free_tokens(tokens);
            free(input);
            continue;
        }

        // Here you would handle command execution (not included in parsing step)
        
        // Cleanup
        free_tokens(tokens);
        free_command(command);
        free(input);
    }

    return 0;
}
