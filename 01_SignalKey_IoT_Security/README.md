# SignalKey: Secure IoT Data Transmission using Dynamic Shift and Noise Injection

## Executive Summary
This project addresses security vulnerabilities in resource-constrained IoT networks. [cite_start]Typical IoT nodes (8-32 MHz, 10-64 KB RAM) are ill-suited for traditional heavy encryption, which significantly reduces device battery life [cite: 8-13]. [cite_start]Furthermore, broadcast-based wireless communication is vulnerable to traffic analysis and passive eavesdropping [cite: 20-25]. [cite_start]**SignalKey** protects data confidentiality and prevents traffic analysis with minimal computational overhead [cite: 26-30].

---

## Network Architecture: RPL Protocol
[cite_start]The system operates over the Routing Protocol for Low-Power and Lossy Networks (RPL), which organizes nodes into a **Destination Oriented Directed Acyclic Graph (DODAG)** [cite: 32-43].

* [cite_start]**Topology**: Data follows an upward routing path: Sensor nodes → Intermediate nodes → Gateway → Cloud [cite: 44-45].
* [cite_start]**Self-Healing**: Nodes dynamically select a Preferred Parent based on signal strength and link reliability; if a parent fails, the child node automatically selects a new parent [cite: 55-64].

---

## Security Architecture & Algorithms

### 1. Physical Layer Security (RSSI)
[cite_start]Rather than relying solely on the Application or Transport layers, SignalKey introduces Physical Layer Security (PLS) [cite: 105-111].
* [cite_start]**RSSI-Based Dynamic Keying**: Received Signal Strength Indicator (RSSI) is used to generate dynamic encryption behavior [cite: 113-114].
* [cite_start]**Channel Reciprocity**: Because the wireless channel is location-dependent, legitimate nodes share similar signal characteristics that distant attackers cannot easily replicate [cite: 115-118].

### 2. The Two-Step Obfuscation Engine
[cite_start]SignalKey manipulates data structure to obfuscate information [cite: 157-161].

#### Step 1: Circular Shift (Scrambling)
[cite_start]A Right Circular Shift rotates the last *k* characters of the ASCII string to the front [cite: 164-166].
* [cite_start]**Logic**: A secret key *k* determines the rotation offset[cite: 167].
* [cite_start]**Example**: `HELLO` (Key k=3) becomes `LLOHE` [cite: 169-171].

#### Step 2: Noise Injection (Camouflage)
[cite_start]Random alphanumeric "garbage" characters are interleaved between every valid data character to mask the true packet length [cite: 173-178].
* [cite_start]**Example**: Scrambled `LLOHE` becomes `L5LbO9H4Ex` [cite: 180-181].

---

## Empirical Results

[cite_start]We evaluated the performance of SignalKey against Normal (unsecured) and Double Encryption modes [cite: 154-156].

### Performance Comparison
| Metric | Normal Mode | RSSI Secure | DoubleEnc |
| :--- | :---: | :---: | :---: |
| **Packet Delivery Ratio (PDR)** | 13.7% | **50.1%** | 32.6% |
| **Packet Loss Rate** | 86.3% | **49.9%** | 67.4% |
| **Avg. Packet Size** | 7 bytes | 7 bytes | 8 bytes |
| **CPU Cost (Energy Ticks)** | 687,322 | 689,358 | 673,834 |

* [cite_start]**PDR Improvement**: RSSI Secure achieved 3.7x better delivery than Normal mode [cite: 229-232].
* [cite_start]**Overhead**: RSSI Secure maintained 7-byte packets with zero size penalty [cite: 245-251].
* [cite_start]**Efficiency**: The extra CPU cost for RSSI is only +0.3%, ensuring battery-powered nodes can easily sustain the security mechanism [cite: 257-262].

---

## Project Structure
```text
├── src/
│   ├── sender_normal.c       # Baseline unencrypted telemetry
│   ├── sender_rssi.c         # SignalKey RSSI PLS sender
│   ├── sender_double.c       # Interactive Double Encryption sender
│   └── receiver_gateway.c    # Universal sink node
├── scripts/
│   └── plot.py               # Log parser & performance visualizer
└── README.md
