#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* color[2];

void print_color(const char* name, const char* color) {
    int r, g, b;
    sscanf(color, "#%02x%02x%02x", &r, &g, &b);
    printf("\033[38;2;%d;%d;%dm%-20s %-7s  \033[0m\n", r, g, b, name, color);
}

void print_all(const color colors[], int length) {
    for (int i=0; i<length; i++){
        print_color(colors[i][0], colors[i][1]);
    }
}

int main(int argc, char* argv[]) {
        const color colors[] = {
        // Reds
        {"Dark_Red", "#9d0006"},
        {"Neutral_Red", "#cc241d"},
        {"Light_Red", "#fb4934"},
        
        // Greens
        {"Dark_Green", "#79740e"},
        {"Neutral_Green", "#98971a"},
        {"Light_Green", "#b8bb26"},
        
        // Yellows
        {"Dark Yellow", "#b57614"},
        {"Neutral Yellow", "#d79921"},
        {"Light Yellow", "#fabd2f"},
        
        // Blues
        {"Dark Blue", "#076678"},
        {"Neutral Blue", "#458588"},
        {"Light Blue", "#83a598"},
        
        // Purples
        {"Dark Purple", "#8f3f71"},
        {"Neutral Purple", "#b16286"},
        {"Light Purple", "#d3869b"},
        
        // Aquas
        {"Dark Aqua", "#427b58"},
        {"Neutral Aqua", "#689d6a"},
        {"Light Aqua", "#8ec07c"},
        
        // Oranges
        {"Dark Orange", "#af3a03"},
        {"Neutral Orange", "#d65d0e"},
        {"Light Orange", "#fe8019"},
        
        // Neutral Dark Colors
        {"Dark0 Hard", "#1d2021"},
        {"Dark0", "#282828"},
        {"Dark0 Soft", "#32302f"},
        {"Dark1", "#3c3836"},
        {"Dark2", "#504945"},
        {"Dark3", "#665c54"},
        {"Dark4", "#7c6f64"},
        
        // Neutral Dark Colors
        {"Dark0 Hard", "#f9f5d7"},
        {"Dark0", "#fbf1c7"},
        {"Dark0 Soft", "#f2e5bc"},
        {"Dark1", "#ebdbb2"},
        {"Dark2", "#d5c4a1"},
        {"Dark3", "#bdae93"},
        {"Dark4", "#a89984"},
        
        // Gray
        {"Gray", "#928374"}
    };
    int length = sizeof(colors) / sizeof(colors[0]);
    print_all(colors, length);
}
