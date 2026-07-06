# SignalKey: RSSI-Based Secret Key Generation for Wireless IoT

A unified firmware architecture engineered for low-power, resource-constrained wireless IoT topologies. This module leverages localized channel state variations to establish shared cryptographic secrets without the architectural overhead of a centralized Key Distribution Center (KDC).

##  System Architecture & Mechanics
* **Role-Based Execution:** Dynamically switches between Gateway (Sink) and Sensor (Sender) modes at runtime based on the hardware mote ID.
* **Physical-Layer Security (PLS):** Implements bitwise XOR obfuscation tracking explicit frame lengths to eliminate null-byte string termination bugs.
* **Collision Mitigation:** Employs a standardized 15–25 second randomized transmission jitter interval to minimize IEEE 802.15.4 MAC-layer radio collisions.
* **Hardware Profiling:** Tracks energy consumption natively via continuous Energest CPU and radio power state logging.

##  Environment Stack
* **Operating System:** Contiki OS
* **Simulation Framework:** Cooja Simulator (IEEE 802.15.4 MAC/PHY layers)
* **Languages:** C (Embedded Firmware), Python (Performance Visualization)

## Setup & Deployment
1. Load this `main.c` file into your Cooja simulation environment.
2. Compile your nodes using the appropriate target architecture (e.g., `sky` motes).
3. Assign Mote ID `11` to your designated Gateway/Sink node to initialize the listening and logging services.
