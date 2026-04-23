#include <am.h>

void print_string(const char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        putch(s[i]);
    }
}

int main(const char *args) {
    ioe_init();

    print_string("OS started! Try to press any key...\n");

    while (1) {
        AM_INPUT_KEYBRD_T event;
        ioe_read(AM_INPUT_KEYBRD, &event);
        
        if (event.keycode != AM_KEY_NONE) {
            // event.keydown 为 1 表示按下，为 0 表示松开
            if (event.keydown) {
                print_string("Key Pressed!\n");
            } else {
                print_string("Key Released!\n");
            }
            // 按下 ESC 键
            if (event.keycode == AM_KEY_ESCAPE && event.keydown) {
                print_string("ESC pressed. Shutting down...\n");
                break; 
            }
        }
    }
    
    halt(0);
    return 0;
}