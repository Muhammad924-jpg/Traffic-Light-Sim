# Traffic Light Simulation
*A realistic traffic light simulator that behaves like a smart traffic management system. THink of it like a smart traffic pollice or sth on those lines.*

## Features
- Dynamic traffic light timing system
- Traffic density-based timing adjustment
- Pedestrian crossing request system
- Emergency vehicle priority mode
- Real-time status display with emojis
- Non-blocking keyboard input system

## Traffic Light Timing
The light cycles are traffic-density aware:
- Red: 20 seconds
- Yellow: 5 seconds
- Green: Varies based on traffic density
  - Very heavy traffic (>90%): 25 seconds
  - Heavy traffic (>75%): 20 seconds
  - Moderate traffic (>50%): 15 seconds
  - Light traffic (>25%): 12 seconds
  - Very light traffic (≤25%): 10 seconds

## Controls
| Key | Function |
|-----|----------|
| P | Request pedestrian crossing |
| E | Toggle emergency mode |
| T | Increase traffic density |
| R | Reduce traffic density |
| Q | Quit simulation |

## Building and Running
```bash
# Compile the program
gcc -Wall -I./include src/main.c src/traffic_light.c -o traffic_sim

# Run the simulation
./traffic_sim
```

## Display Elements
- 🔴 Red Light
- 🟡 Yellow Light
- 🟢 Green Light
- 🚶 Pedestrian Waiting
- 🚨 Emergency Mode