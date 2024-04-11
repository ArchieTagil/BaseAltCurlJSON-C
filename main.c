#include "main.h"

int main() {
    selected_branches *branches = get_selected_branches();
    selected_branches_init(branches);

    data_buffer *buffer = get_data_buffer();
    data_buffer_init(buffer);

    get_user_input();

    for (size_t i = 0; i < 6; i++) {
        free(buffer->buffer1[i].str);
        free(buffer->buffer2[i].str);
    }
    
    return 0;
}