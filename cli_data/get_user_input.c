#include "../main.h"

void get_user_input() {
    char command[1000] = {0};
    while (strcmp(command, "exit") != 0) {
        printf("baseAlt:");
        fgets(command, 1000, stdin);
        command[strlen(command) - 1] = '\0'; // get rid of enter in the end of string

        if (strcmp(command, "show_branches") == 0) {
            perform_show_branches();
        } else if (strcmp(command, "get_data") == 0) {
            perform_get_data();
        } else {
            char *argument = strchr(command, ' ');
            if (argument != NULL) {
                *argument = 0; //enter of string for command
                argument++; //first pointer to the whitespace but we need a pointer to the string

                if (strcmp(command, "set_branch1") == 0) {
                    perform_set_branch(1, argument);
                } else if (strcmp(command, "set_branch2") == 0) {
                    perform_set_branch(2, argument);
                } else if (strcmp(command, "show") == 0) {
                    if (strcmp(argument, "branch1_data") == 0) {
                        perform_show_branch_data(1);
                    } else if (strcmp(argument, "branch2_data") == 0) {
                        perform_show_branch_data(2);
                    } else if (strcmp(argument, "highest_version_release") == 0) {
                        perform_show_highest_version_release();
                    } else {
                        printf("wrong command\n");
                    }
                } else if (strcmp(command, "compare") == 0) {
                    if (strcmp(argument, "left") == 0) {
                        perform_compare(1); // 1 - left
                    } else if (strcmp(argument, "right") == 0) {
                        perform_compare(2); // 2 - right
                    } else {
                        printf("wrong command\n");
                    }
                } else {
                    printf("wrong command\n");
                }
            }
            else if (strcmp(command, "exit") !=0) printf("wrong command\n");
        }
    }
}

























// int get_user_input() {
//     int action = 0;
//     printf("Select the repository to get data from:\n");
//     printf("1 - sisyphus\n");
//     printf("2 - P10\n");
//     while (action != 1 && action != 2) {
//         action = getchar() - 48;
//         getchar();
//         printf("action is: %d", action);
//         if (action !=1 && action != 2) printf("wrong input try again\n");
//     }
//     return action;
// }