// File: src/main.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    // for sleep()
#include <termios.h>
#include <fcntl.h>
#include "../include/traffic_light.h"

// Constants for better readability
#define ONE_SECOND_DELAY 1
#define QUIT_KEY 'q'
#define QUIT_KEY_UPPER 'Q'

// Function to check for keyboard input without blocking
int kbhit(void) {
    struct termios original_terminal, modified_terminal;
    int keyboard_char;
    int terminal_flags;

    // Save original terminal settings
    tcgetattr(STDIN_FILENO, &original_terminal);
    modified_terminal = original_terminal;
    modified_terminal.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &modified_terminal);

    // Set up non-blocking input
    terminal_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, terminal_flags | O_NONBLOCK);

    // Try to read a character
    keyboard_char = getchar();

    // Restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal);
    fcntl(STDIN_FILENO, F_SETFL, terminal_flags);

    // If we got a character, put it back and return true
    if(keyboard_char != EOF) {
        ungetc(keyboard_char, stdin);
        return 1;
    }
    return 0;
}

// Function to handle user input
void handleUserInput(struct TrafficLight *light) {
    char input = getchar();
    if (input == QUIT_KEY || input == QUIT_KEY_UPPER) {
        printf("\nSimulation ended.\n");
        exit(0);
    }
    processInput(light, input);
    getchar(); // consume Enter key
}

// Function to update traffic light state
void updateSimulation(struct TrafficLight *light) {
    light->timer--;
    if (light->timer <= 0) {
        updateTrafficLight(light);
    }
}

int main() {
    // Initialize traffic light
    struct TrafficLight traffic_light;
    initTrafficLight(&traffic_light);

    // Main simulation loop
    while (1) {
        // Display current state
        displayTrafficLight(&traffic_light);
        
        // Check for and handle user input
        if (kbhit()) {
            handleUserInput(&traffic_light);
        }

        // Update traffic light state
        updateSimulation(&traffic_light);
        
        // Wait for one second before next update
        sleep(ONE_SECOND_DELAY);
    }

    return 0;
}
