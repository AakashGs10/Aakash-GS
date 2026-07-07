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

    # 🏛️ SignalKey: End-to-End Architecture & System Workflow

This document provides a comprehensive, visual breakdown of how **SignalKey** operates from scratch. It details the transformation of raw sensor telemetry through physical layer security (PLS) and dynamic obfuscation, its routing across an RPL mesh network, and why single-trip transmission outperforms traditional multi-stage handshakes.

---

## The Big Picture: Life of a SignalKey Packet

When a leaf sensor node samples an environmental metric (such as temperature), the data undergoes a **3-stage transformation pipeline** before ever touching the wireless radio medium. This ensures that even if an eavesdropper captures every broadcast, they cannot read the payload, infer packet lengths, or perform traffic pattern analysis.

```mermaid
graph TD
    A["1. Raw Telemetry Sampled<br/>(e.g., 'TEMP:28')"] --> B["2. Circular Shift Scrambling<br/>(Rotate structure by Key k)"]
    B --> C["3. Random Noise Injection<br/>(Interleave alphanumeric camouflage)"]
    C --> D["4. RSSI PLS XOR Encryption<br/>(Bind to RF physical channel seed)"]
    D --> E["5. Append Protocol Tag 'R'<br/>(Single-trip frame construction)"]
    E --> F["6. UDP / 6LoWPAN Broadcast<br/>(Upward DODAG routing to Sink)"]
    F --> G["7. Universal Gateway Sink<br/>(XOR Decrypt -> Strip Noise -> Unshift)"]

    style A fill:#4e79a7,stroke:#333,stroke-width:2px,color:#fff
    style B fill:#f28e2b,stroke:#333,stroke-width:2px,color:#fff
    style C fill:#f28e2b,stroke:#333,stroke-width:2px,color:#fff
    style D fill:#e15759,stroke:#333,stroke-width:2px,color:#fff
    style E fill:#76b7b2,stroke:#333,stroke-width:2px,color:#fff
    style F fill:#59a14f,stroke:#333,stroke-width:2px,color:#fff
    style G fill:#af7aa1,stroke:#333,stroke-width:2px,color:#fff
