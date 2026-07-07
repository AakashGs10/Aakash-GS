# SignalKey: Secure IoT Data Transmission Using Dynamic Shift and Noise Injection

![Contiki OS](https://img.shields.io/badge/OS-Contiki%202.7-0072C6?style=flat-square&logo=linux)
![Simulator](https://img.shields.io/badge/Simulator-Cooja-4B0082?style=flat-square)
![Routing Protocol](https://img.shields.io/badge/Protocol-RPL%20%2F%206LoWPAN-009688?style=flat-square)
![Transport Protocol](https://img.shields.io/badge/Transport-UDP-009688?style=flat-square)

## Executive Summary & Introduction
In low-power, resource-constrained Internet of Things (IoT) sensor networks, devices are strictly bounded by low-frequency microcontrollers, minimal RAM, and battery-powered operation. **SignalKey** provides a lightweight Physical Layer Security (PLS) framework coupled with Dynamic Obfuscation to protect data confidentiality and prevent traffic analysis without the computational overhead of traditional encryption.

---

## Network Topology & RPL DODAG Routing
This project operates over the Routing Protocol for Low-Power and Lossy Networks (RPL), organizing motes into a hierarchical Destination Oriented Directed Acyclic Graph (DODAG).

<p align="center">
  <img width="913" height="626" alt="Network Topology Simulation" src="https://github.com/user-attachments/assets/273031b2-ccc7-46c0-b941-7e543a5d0cab" />
</p>

```mermaid
graph TD
    Root["Root Gateway Node (Sink / DODAG Root)"]
    R1["Intermediate Router Node A"]
    R2["Intermediate Router Node B"]
    L1["Leaf Sensor Mote 1"]
    L2["Leaf Sensor Mote 2"]
    L3["Leaf Sensor Mote 3"]
    L4["Leaf Sensor Mote 4"]

    L1 -->|UDP / 6LoWPAN| R1
    L2 -->|UDP / 6LoWPAN| R1
    L3 -->|UDP / 6LoWPAN| R2
    L4 -->|UDP / 6LoWPAN| R2
    
    R1 -->|Upward DODAG Routing| Root
    R2 -->|Upward DODAG Routing| Root

    style Root fill:#d9534f,stroke:#333,stroke-width:2px,color:#fff
    style R1 fill:#0275d8,stroke:#333,stroke-width:2px,color:#fff
    style R2 fill:#0275d8,stroke:#333,stroke-width:2px,color:#fff
    style L1 fill:#5cb85c,stroke:#333,stroke-width:2px,color:#fff
    style L2 fill:#5cb85c,stroke:#333,stroke-width:2px,color:#fff
    style L3 fill:#5cb85c,stroke:#333,stroke-width:2px,color:#fff
    style L4 fill:#5cb85c,stroke:#333,stroke-width:2px,color:#fff
