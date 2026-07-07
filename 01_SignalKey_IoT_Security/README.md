# SignalKey: Secure IoT Data Transmission Using Dynamic Shift and Noise Injection



## 📌 Executive Summary & Introduction
In low-power, resource-constrained Internet of Things (IoT) sensor networks (such as IEEE 802.15.4 / 6LoWPAN), devices are strictly limited by low-frequency microcontrollers (8–32 MHz), minimal RAM (10–64 KB), and battery-powered operation. Running traditional, computation-heavy cryptographic suites continuously depletes battery life and introduces severe processing latency. 

Furthermore, even when payloads are encrypted, wireless broadcasts remain highly vulnerable to **Traffic Analysis Attacks** and **Passive Eavesdropping**. Attackers within RF range can monitor packet lengths, transmission intervals, and communication frequencies to infer sensor behavior or predict critical network events without decrypting the underlying bytes.

**SignalKey** solves these challenges by introducing a lightweight **Physical Layer Security (PLS)** framework coupled with **Dynamic Obfuscation**:
1. **Physical Layer Security (RSSI-Based Dynamic Keying):** Leverages the unique, location-dependent channel reciprocity of Received Signal Strength Indicators (RSSI) between communicating nodes to derive dynamic encryption seeds without interactive exchange overhead.
2. **Dynamic Obfuscation (Scramble & Camouflage):** Combines a Right Circular Shift algorithm to disrupt message structure with randomized alphanumeric noise injection to mask true packet lengths—effectively rendering passive traffic analysis impossible while preserving optimal network stability.

---

## 🌐 Network Topology & RPL DODAG Routing
This project operates over the **Routing Protocol for Low-Power and Lossy Networks (RPL)**, standardized by the IETF for constrained wireless environments. RPL organizes wireless motes into a hierarchical **Destination Oriented Directed Acyclic Graph (DODAG)**, ensuring efficient upward data routing from leaf sensors to the root gateway.

<p align="center">
  <img width="913" height="626" alt="Network Topology Simulation" src="[https://github.com/user-attachments/assets/273031b2-ccc7-46c0-b941-7e543a5d0cab](https://github.com/user-attachments/assets/273031b2-ccc7-46c0-b941-7e543a5d0cab)" />
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
