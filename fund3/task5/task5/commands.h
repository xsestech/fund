//
// Created by Alex on 21.04.2024.
//

#ifndef COMMANDS_H
#define COMMANDS_H

#include <float.h>

#include <libinteractive/cli.h>


command_config_t get_add_command_config(tree_args* tree_command_args);
command_config_t get_delete_command_config(tree_args* tree_command_args);
command_config_t get_task_command_config(tree_args* tree_command_args);
command_config_t get_print_command_config(tree_args* tree_command_args);


#endif //COMMANDS_H
