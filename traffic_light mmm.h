// File: include/traffic_light.h

#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

// Traffic light states
enum LightState {
    RED,
    YELLOW,
    GREEN
};

// Traffic light structure
struct TrafficLight {
    enum LightState state;
    int timer;
    int traffic_density;
    int pedestrian_waiting;
    int emergency_mode;
};

// Function declarations
void initTrafficLight(struct TrafficLight *light);
void updateTrafficLight(struct TrafficLight *light);
void displayTrafficLight(const struct TrafficLight *light);
void processInput(struct TrafficLight *light, char input);

#endif // TRAFFIC_LIGHT_H
