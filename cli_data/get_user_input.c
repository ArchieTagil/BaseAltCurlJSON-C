#include "../main.h"

int get_user_input() {
    int action = 0;
    printf("Select the repository to get data from:\n");
    printf("1 - sisyphus\n");
    printf("2 - P10\n");
    while (action != 1 && action != 2) {
        action = getchar() - 48;
        getchar();
        printf("action is: %d", action);
        if (action !=1 && action != 2) printf("wrong input try again\n");
    }
    return action;
}