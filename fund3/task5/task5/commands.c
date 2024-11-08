//
// Created by Alex on 21.04.2024.
//
#include <task5/commands.h>
#include <libinteractive/cli.h>

#define MAX_TOKENS 5



void add_command(char *args, void *command_config) {
    tree_args command_args = to_command_config(tree_args, command_config);
    char* tokens[MAX_TOKENS];
    int parsed_tokens = 0;
    char* path = "\0";
    parse_tokens(args, MAX_TOKENS, tokens, &parsed_tokens);
    double value = 0;
    if(parsed_tokens < 2 || parsed_tokens > 3) {
        fprintf(stderr, "Invalid args\n");
        return;
    }
    if(parsed_tokens >= 3) {
        path = tokens[2];
    }
    if (!parse_double(tokens[1], &value)) {
        fprintf(stderr, "Invalid input\n");
        return;
    }
    if (!tree_add(command_args.tree, value, path)) {
        fprintf(stderr, "Invalid path\n");
        return;
    }
    printf("Node added\n");
}

void delete_command(char *args, void *command_config) {
    tree_args command_args = to_command_config(tree_args, command_config);
    char* tokens[MAX_TOKENS];
    int parsed_tokens = 0;
    char* path = "\0";
    parse_tokens(args, MAX_TOKENS, tokens, &parsed_tokens);
    if(parsed_tokens > 2) {
        fprintf(stderr, "Invalid args\n");
        return;
    }
    if(tree_is_empty(*command_args.tree)) {
        fprintf(stderr, "Can't delete node in empty tree\n");
        return;
    }
    if(parsed_tokens == 2) {
        path = tokens[1];
    }
    if(!tree_delete(command_args.tree, path)) {
        fprintf(stderr, "Invalid path\n");
        return;
    }
    printf("Node deleted\n");

}


void task_command(char* args, void *command_config) {
    tree_args command_args = to_command_config(tree_args, command_config);
    if(*command_args.tree == NULL) {
        fprintf(stderr, "Can't find max value in empty tree\n");
        return;
    }
    double max_value = tree_find_max_non_terminating(command_args.tree);
    if(max_value == DBL_MIN) {
        printf("Max value not found\n");
        return;
    }
    printf("Max value of non-terminating mode %lf\n", max_value);
}

void print_command(char* args, void *command_config) {
    tree_args command_args = to_command_config(tree_args, command_config);
    tree_print(*command_args.tree);
}
command_config_t get_add_command_config(tree_args* tree_command_args) {
    return cli_create_command('a', &add_command, "Add node to tree", tree_command_args);
}

command_config_t get_print_command_config(tree_args* tree_command_args) {
    return cli_create_command('p', &print_command, "Print tree", tree_command_args);
}
command_config_t get_delete_command_config(tree_args* tree_command_args) {
    return cli_create_command('d', &delete_command, "Delete node", tree_command_args);
}
command_config_t get_task_command_config(tree_args* tree_command_args) {
    return cli_create_command('t', &task_command, "Run task", tree_command_args);
}