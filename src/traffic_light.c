//It's the implementation file; the source code.

#include <stdio.h>
#include <unistd.h>
#include "../include/traffic_light.h"

void initTrafficLight(struct TrafficLight *light){
    light -> current_state = RED;
    light -> duration = 50;
}

void updateTrafficLight(struct TrafficLight *light){
    switch (light -> current_state){
        case RED:
            light -> current_state = GREEN;
            light -> duration = 30;
            break;
            
        case GREEN:
            light -> current_state = YELLOW;
            light -> duration = 5;
            break;

        case YELLOW:
            light -> current_state = RED;
            light -> duration = 50;
            break; 

    }
}

void displayTrafficLight(struct TrafficLight *light){
    switch(light -> current_state){
        case RED:
            printf("Traffic Light: RED...(STOP!) Wait for %d seconds.\n", light -> duration );
            break;

        case GREEN:
            printf("Traffic Light: GREEN...(GO!) %d seconds left.\n", light -> duration );
            break;

        case YELLOW:
            printf("Traffic Light: YELLOW...(CAUTION) - %d seconds left.\n", light -> duration);
            break;
        
    }
}