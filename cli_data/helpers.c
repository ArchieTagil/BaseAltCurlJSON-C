#include "../main.h"

selected_branches *get_selected_branches() {
    static selected_branches branches;
    return &branches;
}

void perform_show_branches() {
    selected_branches *branches = get_selected_branches();
    printf("branch1 = \"%s\"\n", branches->branch1);
    printf("branch2 = \"%s\"\n", branches->branch2);
}

void selected_branches_init(selected_branches *branches) {
    strcpy(branches->branch1, "empty");
    strcpy(branches->branch2, "empty");
}

void perform_set_branch(int id, char *argument) {
    if (strcmp(argument, "p10") == 0 || strcmp(argument, "p9") == 0 || strcmp(argument, "sisyphus") == 0) {
        selected_branches *branches = get_selected_branches();
        if (id == 1) strcpy(branches->branch1, argument);
        if (id == 2) strcpy(branches->branch2, argument);
    } else {
        printf("There isn't such branch\n");
    }
}

void perform_get_data() {
    
}

void perform_show_branch_data(int id) {

}

void perform_show_highest_version_release() {

}

void perform_compare(int id) {

}