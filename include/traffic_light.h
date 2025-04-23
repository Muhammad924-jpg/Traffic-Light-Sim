#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

enum lightState {
    RED,
    YELLOW,
    GREEN
};

struct TrafficLight{
    enum lightState current_state;
    int duration; // in seconds.
};

void initTrafficLight(struct TrafficLight *light); //Setting the default state i.e. RED 50 seconds.
void updateTrafficLight(struct TrafficLight *light); //Updates traffic light state.
void displayTrafficLight(struct TrafficLight *light); //Displays the realtime state.

#endif
