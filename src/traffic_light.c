// File: src/traffic_light.c in my POP!_OS Linux distro

#include "../include/traffic_light.h"
#include <stdio.h>
#include <unistd.h>  // For sleep()

// Initialize traffic light with default settings, its like a reset button of a sort
void initTrafficLight(struct TrafficLight *light) {
    light->state = RED;
    light->timer = 20;
    light->traffic_density = 50;
    light->pedestrian_waiting = 0;
    light->emergency_mode = 0;
}

// Switch light states based on timer
void updateTrafficLight(struct TrafficLight *light) {
    if (light->emergency_mode) {
        if (light->state != GREEN) {
            light->state = GREEN;
            light->timer = 30;
        } else if (light->timer <= 0) {
            light->timer = 30;  // Reset timer but keep green light
        }
        return;
    }

    if (light->timer <= 0) {
        switch (light->state) {
            case RED:
                light->state = GREEN;
                if (light->traffic_density > 90) {
                    light->timer = 25;        // Very heavy traffic
                } else if (light->traffic_density > 75) {
                    light->timer = 20;        // Heavy traffic
                } else if (light->traffic_density > 50) {
                    light->timer = 15;        // Medium traffic
                } else if (light->traffic_density > 25) {
                    light->timer = 12;        // Light traffic
                } else {
                    light->timer = 10;        // Very light traffic
                }
                break;
            case GREEN:
                light->state = YELLOW;
                light->timer = 5;
                break;
            case YELLOW:
                light->state = RED;
                light->timer = 20;
                light->pedestrian_waiting = 0;  // Reset pedestrian flag
                break;
        }
    }
}

// Modified display function without timing logic
void displayTrafficLight(const struct TrafficLight *light) {
    // Clear screen and move cursor to top-left
    printf("\033[2J\033[H");
    printf("=========================\n");
    printf("  TRAFFIC LIGHT STATUS\n");
    printf("=========================\n\n");

    switch (light->state) {
        case RED: printf("🔴 RED LIGHT\n"); break;
        case GREEN: printf("🟢 GREEN LIGHT\n"); break;
        case YELLOW: printf("🟡 YELLOW LIGHT\n"); break;
    }

    printf("\nTime Remaining: %d seconds\n", light->timer);
    printf("Traffic Density: %d%%\n", light->traffic_density);

    if (light->emergency_mode)    printf("🚨 Emergency Mode Active!\n");
    if (light->pedestrian_waiting)printf("🚶 Pedestrian Waiting!\n");

    printf("\nControls: P - Pedestrian | E - Emergency Mode | T - Traffic Up | R - Traffic Down | Q - Quit\n");
    printf("Consult the README file to understand how to effectively use this project.\n");
    fflush(stdout);  // Force output buffer to flush
}

// Process user commands, Emergency, Traffic Density, Pedestrian navigation. THink of this code as a traffic officer managing it
void processInput(struct TrafficLight *light, char input) {
    switch (input) {
        case 'p': case 'P':
            if (!light->pedestrian_waiting && !light->emergency_mode) {
                light->pedestrian_waiting = 1;
                printf("\n🚶 Pedestrian crossing requested!\n");
            }
            break;
        case 'e': case 'E':
            light->emergency_mode = !light->emergency_mode;
            if (light->emergency_mode) {
                light->state = GREEN;
                if (light->traffic_density > 90) {
                    light->timer = 25;        // Very heavy traffic
                } else if (light->traffic_density > 75) {
                    light->timer = 20;        // Heavy traffic
                } else if (light->traffic_density > 50) {
                    light->timer = 15;        // Moderate traffic
                } else if (light->traffic_density > 25) {
                    light->timer = 12;        // Light traffic
                } else {
                    light->timer = 10;        // Very light traffic
                }
            }
            break;
        case 't': case 'T':
            if (light->traffic_density < 100) {
                light->traffic_density += 10;
                // Adjust current timer if in GREEN state
                if (light->state == GREEN && !light->emergency_mode) {
                    if (light->traffic_density > 90) {
                        light->timer = 25;        // Very heavy traffic
                    } else if (light->traffic_density > 75) {
                        light->timer = 20;        // Heavy traffic
                    } else if (light->traffic_density > 50) {
                        light->timer = 15;        // Moderate traffic
                    } else if (light->traffic_density > 25) {
                        light->timer = 12;        // Light traffic
                    } else {
                        light->timer = 10;        // Very light traffic
                    }
                }
            }
            break;
        case 'r': case 'R':
            if (light->traffic_density > 0) {
                light->traffic_density -= 10;
                // Adjust current timer if in GREEN state
                if (light->state == GREEN && !light->emergency_mode) {
                    if (light->traffic_density > 90) {
                        light->timer = 25;        // Very heavy traffic
                    } else if (light->traffic_density > 75) {
                        light->timer = 20;        // Heavy traffic
                    } else if (light->traffic_density > 50) {
                        light->timer = 15;        // Moderate traffic
                    } else if (light->traffic_density > 25) {
                        light->timer = 12;        // Light traffic
                    } else {
                        light->timer = 10;        // Very light traffic
                    }
                }
            }
            break;
    }
}
