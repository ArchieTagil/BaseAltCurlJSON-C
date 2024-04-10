#include "main.h"

int main() {
    selected_branches *branches = get_selected_branches();
    selected_branches_init(branches);

    data_buffer *buffer = get_data_buffer();
    data_buffer_init(buffer);

    int branch_id = get_user_input();

    free(buffer->buffer1.str);
    free(buffer->buffer2.str);
    return 0;
}

