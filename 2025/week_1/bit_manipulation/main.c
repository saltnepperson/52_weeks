#include <stdio.h>
#include <string.h>
#include <stdint.h>


enum CONSOLE_TEXT_COLOR {
    BLACK       = 30,
    RED         = 31,
    GREEN       = 32,
    YELLOW      = 33,
    BLUE        = 34,
    MAGENTA     = 35,
    CYAN        = 36,
    WHITE       = 37,
};

const char * DEFAULT_TEXT_COLOR = "0m";
const char * START_ANSI_ESCAPE = "\033[";

void print_color_text(const int color_code, const char* label, int value) {
    char buffer[128];
    char color_code_str[8];

    snprintf(color_code_str, sizeof(color_code_str), "%s%dm", START_ANSI_ESCAPE, color_code);

    snprintf(buffer, sizeof(buffer), "%s%s%d%s", color_code_str, label, value, START_ANSI_ESCAPE);
    strcat(buffer, DEFAULT_TEXT_COLOR);

    printf("%s", buffer);
}

void view_binary(uint32_t value, const int* highlight, int highlight_count) {
    int total_bits32 = sizeof(uint32_t) * 8;

    printf("Binary of %u: 0b", value);

    for (int ind = total_bits32 - 1; ind >= 0; ind--) {
        int is_highlight = 0;

        for (int h_ind = 0; h_ind < highlight_count; h_ind++) {
            if (highlight[h_ind] == ind) {
                is_highlight = 1;
                break;
            }
        }

        int bit = (value >> ind) & 1;

        if (is_highlight) {
            print_color_text(GREEN, "", bit);
        } else {
            printf("%d", bit);
        }

        if (ind % 4 == 0 && ind != 0) {
            printf(" ");
        }
    }

    printf("\n");
}

int main() {
    uint32_t number = 123;
    const int highlights[] = {7, 6, 5, 4};

    view_binary(number, highlights, sizeof(highlights) - 2);

    return 0;
}