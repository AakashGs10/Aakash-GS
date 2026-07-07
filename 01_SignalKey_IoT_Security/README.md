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


    <img width="913" height="626" alt="image" src="https://github.com/user-attachments/assets/273031b2-ccc7-46c0-b941-7e543a5d0cab" />


    <img width="902" height="222" alt="image" src="https://github.com/user-attachments/assets/4ae2e9d0-81ac-4d66-a884-a8a13b88bca1" />

    sequenceDiagram
    autonumber
    participant S as Sensor Node (Sender)
    participant RF as Wireless RF Channel (UDGM)
    participant G as Root Gateway (Receiver Sink)
    
    Note over S: Sample Telemetry (e.g., "HELLO")<br/>Apply Right Circular Shift (Key k=3) -> "LLOHE"
    S->>S: Interleave Random Noise -> "L5LbO9H4Ex"
    Note over S: Derive RSSI Physical Channel Seed<br/>Apply Bitwise XOR PLS Obfuscation
    S->>RF: Broadcast Tagged Packet [Flag 'R' | Obfuscated Payload]
    RF->>G: Single-Trip UDP Packet Delivery
    Note over G: Verify Protocol Flag 'R'<br/>Apply XOR PLS Decryption via Channel Seed
    G->>G: Strip Injected Noise ("L5LbO9H4Ex" -> "LLOHE")<br/>Reverse Circular Shift (Key k=3) -> "HELLO"
    Note over G: Log Validated Telemetry & CPU Energest Ticks


    <img width="910" height="176" alt="image" src="https://github.com/user-attachments/assets/c05f1918-a123-4e16-be22-794e9c4890c1" />
    sequenceDiagram
    autonumber
    participant S as Sensor Node (Sender Shift k1 = 3)
    participant RF as RPL / 6LoWPAN Mesh Network
    participant R as Gateway Sink (Receiver Shift k2 = 2)
    
    Note over S: Original: "HELLO" -> Shift: "LLOHE"<br/>Inject Noise: "L5LbO9H4Ex"
    S->>RF: Stage 1 Packet: 1[L5LbO9H4Ex]
    RF->>R: Receive Stage 1
    Note over R: Strip Sender Noise -> Reverse Shift ("HELLO")<br/>Apply Receiver Shift ("LLOHE") -> Inject Noise ("H7E3L9L205")
    R->>RF: Stage 2 Packet: 2[H7E3L9L205]
    RF->>S: Receive Stage 2 (High RF Collision Risk)
    Note over S: Strip Receiver Noise -> Reverse Shift ("HELLO")<br/>Apply Reverse Sender Shift ("LLOHE")
    S->>RF: Stage 3 Packet: 3[LLOHE]
    RF->>R: Receive Stage 3
    Note over R: Reverse Sender Shift: "LLOHE" -> "HELLO"<br/>Final Validated Sensor Output



