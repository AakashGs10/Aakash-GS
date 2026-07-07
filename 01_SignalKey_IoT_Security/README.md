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


# SignalKey: RSSI-Based Physical Layer Security (PLS) for Resource-Constrained IoT Networks

![Contiki OS](https://img.shields.io/badge/OS-Contiki%202.7-0072C6?style=flat-square&logo=linux)
![Simulator](https://img.shields.io/badge/Simulator-Cooja-4B0082?style=flat-square)
![Language](https://img.shields.io/badge/Language-C%20%2F%20Python-A8B9CC?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)

## 📌 Executive Summary
In tactical and defense-grade Internet of Things (IoT) deployments, low-power sensor nodes (IEEE 802.15.4) operate under severe energy and computational constraints. Traditional multi-step cryptographic handshakes (such as Double Encryption protocols) introduce catastrophic MAC-layer radio collisions, high packet loss, and excessive CPU drain when deployed across dense wireless topologies.

**SignalKey** is a lightweight **Physical Layer Security (PLS)** framework that leverages Received Signal Strength Indication (RSSI) and physical channel characteristics to generate dynamic, single-trip encryption keys. This repository provides an empirical stress-test suite comparing standard plaintext telemetry, SignalKey RSSI PLS, and traditional 4-way Double Encryption inside the **Contiki OS / Cooja Network Simulator**.

---

## 📊 Key Empirical Findings
Across standardized 10-minute simulation sessions with 10 concurrent sensor motes and 1 universal sink node, our empirical evaluation reveals the strict engineering tradeoffs of wireless cryptography:

| Security Protocol | Packet Delivery Ratio (PDR) | Rx Network Capacity | Transmission Overhead | CPU Power Cost (M Ticks) | Engineering Verdict |
| :--- | :---: | :---: | :---: | :---: | :--- |
| **Normal (Unsecured)** | **~97.2%** | **100.0% (Base)** | **20.4 Bytes** | **0.88M** | Baseline max throughput; zero confidentiality. |
| **SignalKey (RSSI PLS)** | **~97.7%** | **~77.6%** | **32.9 Bytes** | **0.86M** | **Optimal Tradeoff:** High PDR, single-trip confidentiality, minimal CPU load. |
| **Double Encryption** | **~96.6% (Handshake)**| **~24.8%** | **8.0 Bytes (Per Frame)**| **0.46M (Idle Starve)**| **Severe Bottleneck:** 4-way RF handshake causes massive radio collisions and capacity starvation. |

> **Note on Capacity Starvation:** While Double Encryption appears to consume fewer total CPU ticks, this occurs because the 4-step interactive handshake causes severe MAC-layer RF channel congestion. Sensor motes spend the majority of their time backing off due to radio collisions, destroying ~75% of total network throughput.

---

## 🏗️ Protocol Architecture & Workflows

GitHub natively renders the sequence diagrams below, illustrating the traffic overhead differences between the evaluated methodologies:

# SignalKey: Secure IoT Data Transmission Using Dynamic Shift and Noise Injection

![Contiki OS](https://img.shields.io/badge/OS-Contiki%202.7-0072C6?style=flat-square&logo=linux)
![Simulator](https://img.shields.io/badge/Simulator-Cooja-4B0082?style=flat-square)
![Routing Protocol](https://img.shields.io/badge/Protocol-RPL%20%2F%206LoWPAN-009688?style=flat-square)
![Transport Protocol](https://img.shields.io/badge/Transport-UDP-009688?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)

## 📌 Executive Summary & Introduction
In low-power, resource-constrained Internet of Things (IoT) sensor networks (such as IEEE 802.15.4 / 6LoWPAN), devices are strictly limited by low-frequency microcontrollers (8–32 MHz), minimal RAM (10–64 KB), and battery-powered operation. Running traditional, computation-heavy cryptographic suites continuously depletes battery life and introduces severe processing latency. 

Furthermore, even when payloads are encrypted, wireless broadcasts remain highly vulnerable to **Traffic Analysis Attacks** and **Passive Eavesdropping**. Attackers within RF range can monitor packet lengths, transmission intervals, and communication frequencies to infer sensor behavior or predict critical network events without decrypting the underlying bytes.

**SignalKey** solves these challenges by introducing a lightweight **Physical Layer Security (PLS)** framework coupled with **Dynamic Obfuscation**:
1. **Physical Layer Security (RSSI-Based Dynamic Keying):** Leverages the unique, location-dependent channel reciprocity of Received Signal Strength Indicators (RSSI) between communicating nodes to derive dynamic encryption seeds without interactive exchange overhead.
2. **Dynamic Obfuscation (Scramble & Camouflage):** Combines a Right Circular Shift algorithm to disrupt message structure with randomized alphanumeric noise injection to mask true packet lengths—effectively rendering passive traffic analysis impossible while preserving optimal network stability.

---

## 🌐 Network Topology & RPL DODAG Routing
This project operates over the **Routing Protocol for Low-Power and Lossy Networks (RPL)**, standardized by the IETF for constrained wireless environments. RPL organizes wireless motes into a hierarchical **Destination Oriented Directed Acyclic Graph (DODAG)**, ensuring efficient upward data routing from leaf sensors to the root gateway.

```mermaid
graph TD
    classDef root fill:#d9534f,stroke:#333,stroke-width:2px,color:#fff;
    classDef router fill:#0275d8,stroke:#333,stroke-width:2px,color:#fff;
    classDef leaf fill:#5cb85c,stroke:#333,stroke-width:2px,color:#fff;

    Root["Root Gateway Node (Sink / DODAG Root)"] ::: root
    
    R1["Intermediate Router Node A"] ::: router
    R2["Intermediate Router Node B"] ::: router
    
    L1["Leaf Sensor Mote 1"] ::: leaf
    L2["Leaf Sensor Mote 2"] ::: leaf
    L3["Leaf Sensor Mote 3"] ::: leaf
    L4["Leaf Sensor Mote 4"] ::: leaf

    L1 -->|UDP / 6LoWPAN| R1
    L2 -->|UDP / 6LoWPAN| R1
    L3 -->|UDP / 6LoWPAN| R2
    L4 -->|UDP / 6LoWPAN| R2
    
    R1 -->|Upward DODAG Routing| Root
    R2 -->|Upward DODAG Routing| Root
