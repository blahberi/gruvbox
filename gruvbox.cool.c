#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* color[2];

void fprint_color(FILE* stream, const char* name, const char* color) {
    int r, g, b;
    sscanf(color, "#%02x%02x%02x", &r, &g, &b);
    fprintf(stream, "\033[38;2;%d;%d;%dm%-20s %-7s  \033[0m\n", r, g, b, name, color);
    fflush(stream);
}

void print_color(const char* name, const char* color) {
    fprint_color(stdout, name, color);
}

int find_color(char* name, const color colors[], int length) {
    for (int i=0; i<length; i++) {
        if (strcmp(name, colors[i][0]) == 0) {
            return i;
        }
    }
    return -1;
}

void copy_to_clipboard(const char *hex) {
    const char *wayland_display = getenv("WAYLAND_DISPLAY");
    const char *x_display = getenv("DISPLAY");

    char command[64];

    if (wayland_display) {
        snprintf(command, sizeof(command), "echo -n '%s' | wl-copy", hex);
    } else if (x_display) {
        snprintf(command, sizeof(command), "echo -n '%s' | xclip -selection clipboard");
    } else {
        printf("Clipboard copy is not supported on this environment.\n");
        return;
    }
    system(command);
}


void fprint_all(FILE* stream, const color colors[], int length) {
    for (int i=0; i<length; i++){
        fprint_color(stream, colors[i][0], colors[i][1]);
    }
}

void print_all(const color colors[], int length) {
    fprint_all(stdout, colors, length);
}

void fzf_select(const color colors[], int length) {
    FILE *temp_file = fopen("/tmp/gruvbox.txt", "w");
    if (!temp_file) {
        perror("failed to open temporary file\n");
        exit(EXIT_FAILURE);
    }

    fprint_all(temp_file, colors, length);
    char selected[256];
    FILE* fzf = popen("fzf --ansi < /tmp/gruvbox.txt", "r");

    if (fgets(selected, sizeof(selected), fzf) != NULL){
        char* selected_name;
        char* hex;
        selected_name = strtok(selected, " ");
        hex = strtok(NULL, " ");
        print_color(selected_name, hex);
        copy_to_clipboard(hex);
    }
    else {
        printf("No selection made.\n");
    }
}

void handle_arguments(char* arg, const color colors[], int length)
{
    if (strcmp(arg, "-f") == 0) {
        fzf_select(colors, length);
        return;
    }
    int index = find_color(arg, colors, length);
    if (index < 0) {
        printf("No such color\n");
        return;
    }
    char* hex = colors[index][1];
    print_color(arg, hex);
    copy_to_clipboard(hex);
}

int main(int argc, char* argv[]) {
        const color colors[] = {
        // Reds
        {"FadedRed", "#9d0006"},
        {"NeutralRed", "#cc241d"},
        {"BrightRed", "#fb4934"},
        
        // Greens
        {"FadedGreen", "#79740e"},
        {"NeutralGreen", "#98971a"},
        {"BrightGreen", "#b8bb26"},
        
        // Yellows
        {"FadedYellow", "#b57614"},
        {"NeutralYellow", "#d79921"},
        {"BrightYellow", "#fabd2f"},
        
        // Blues
        {"FadedBlue", "#076678"},
        {"NeutralBlue", "#458588"},
        {"BrightBlue", "#83a598"},
        
        // Purples
        {"FadedPurple", "#8f3f71"},
        {"NeutralPurple", "#b16286"},
        {"BrightPurple", "#d3869b"},
        
        // Aquas
        {"FadedAqua", "#427b58"},
        {"NeutralAqua", "#689d6a"},
        {"BrightAqua", "#8ec07c"},
        
        // Oranges
        {"FadedOrange", "#af3a03"},
        {"NeutralOrange", "#d65d0e"},
        {"BrightOrange", "#fe8019"},
        
        // Neutral Dark Colors
        {"Dark0_Hard", "#1d2021"},
        {"Dark0", "#282828"},
        {"Dark0_Soft", "#32302f"},
        {"Dark1", "#3c3836"},
        {"Dark2", "#504945"},
        {"Dark3", "#665c54"},
        {"Dark4", "#7c6f64"},
        
        // Neutral Light Colors
        {"Light0_Hard", "#f9f5d7"},
        {"Light0", "#fbf1c7"},
        {"Light0_Soft", "#f2e5bc"},
        {"Light1", "#ebdbb2"},
        {"Light2", "#d5c4a1"},
        {"Light3", "#bdae93"},
        {"Light4", "#a89984"},
        
        // Gray
        {"Gray", "#928374"}
    };
    int length = sizeof(colors) / sizeof(colors[0]);
    if (argc > 1) {
        handle_arguments(argv[1], colors, length);
    }
    else {
        print_all(colors, length);
    }
}
