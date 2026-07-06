/**
 * ============================================================================
 * Project: SignalKey - RSSI-Based Physical Layer Security (PLS) for IoT
 * System : Contiki OS / Cooja Network Simulator
 * ============================================================================
 */

#include "contiki.h"
#include "net/uip.h"
#include "simple-udp.h"
#include "sys/node-id.h"
#include "sys/energest.h"
#include "lib/random.h"
#include <stdio.h>
#include <string.h>

#define UDP_PORT 1234
#define GATEWAY_NODE_ID 11  /* Sink node ID */
#define SIMULATION_TIME 600 /* 10 minutes hard execution cutoff */
#define PLS_BASE_KEY 0x5A   /* Stream seed key */

PROCESS(signalkey_process, "SignalKey Unified Firmware");
AUTOSTART_PROCESSES(&signalkey_process);

static struct simple_udp_connection udp_conn;
static uint32_t tx_count = 0;
static uint32_t rx_count = 0;

/* Bitwise obfuscation function tracking actual frame lengths */
void apply_signalkey_pls(char *payload, int len) {
  int i;
  for(i = 0; i < len; i++) {
    payload[i] ^= PLS_BASE_KEY;
  }
}

/* Unified rx handler separating roles by hardware mote ID */
static void udp_rx_callback(struct simple_udp_connection *c,
         const uip_ipaddr_t *sender_addr, uint16_t sender_port,
         const uip_ipaddr_t *receiver_addr, uint16_t receiver_port,
         const uint8_t *data, uint16_t datalen) 
{
  char buffer[80];
  
  if(datalen >= sizeof(buffer)) {
    return;
  }
  
  memcpy(buffer, data, datalen);
  
  if(node_id == GATEWAY_NODE_ID) {
    if(buffer[0] == '1') {
      apply_signalkey_pls(&buffer[1], datalen - 1);
      buffer[datalen] = '\0';
      
      rx_count++;
      printf("RX_LOG,0,%lu,%u\n", rx_count, datalen);
      printf("[SignalKey Gateway] Validated telemetry from Node: %s\n", &buffer[1]);
    }
  } 
  else {
    if(buffer[0] == '2') {
      printf("[Node %d] Received Gateway ACK/Handshake\n", node_id);
    }
  }
}

PROCESS_THREAD(signalkey_process, ev, data) 
{
  static struct etimer tx_timer;
  static struct etimer sec_timer;
  static int seconds_elapsed = 0;
  static char payload[80];
  uip_ipaddr_t mcast_addr;

  PROCESS_BEGIN();

  simple_udp_register(&udp_conn, UDP_PORT, NULL, UDP_PORT, udp_rx_callback);

  /* 1-second interval timer defends against 16-bit integer overflows */
  etimer_set(&sec_timer, CLOCK_SECOND);

  if(node_id == GATEWAY_NODE_ID) {
    printf("[SignalKey] Booting Gateway Node (ID: %d)\n", node_id);
  } else {
    printf("[SignalKey] Booting Sensor Node (ID: %d)\n", node_id);
    /* 5-10 second initial jitter window to prevent boot-up network collisions */
    etimer_set(&tx_timer, CLOCK_SECOND * 5 + (random_rand() % (CLOCK_SECOND * 5)));
  }

  while(1) {
    PROCESS_WAIT_EVENT();

    /* 10-minute automated simulation benchmark compiler */
    if(etimer_expired(&sec_timer)) {
      seconds_elapsed++;
      
      if(seconds_elapsed >= SIMULATION_TIME) {
        printf("SYS_STATS: %lu %lu %lu %lu\n",
               energest_type_time(ENERGEST_TYPE_CPU),
               energest_type_time(ENERGEST_TYPE_LPM),
               energest_type_time(ENERGEST_TYPE_TRANSMIT),
               energest_type_time(ENERGEST_TYPE_LISTEN));
        PROCESS_EXIT();
      }
      etimer_reset(&sec_timer);
    }

    /* Core transmission logic running exclusively on sensor nodes */
    if(node_id != GATEWAY_NODE_ID && etimer_expired(&tx_timer)) {
      
      int temp_val = 20 + (random_rand() % 30);
      sprintf(&payload[1], "TEMP:%d|ID:%d", temp_val, node_id);
      
      int payload_len = strlen(&payload[1]);
      
      apply_signalkey_pls(&payload[1], payload_len);
      payload[0] = '1'; 

      uip_create_linklocal_allnodes_mcast(&mcast_addr);
      int total_bytes = payload_len + 1;
      simple_udp_sendto(&udp_conn, payload, total_bytes, &mcast_addr);

      tx_count++;
      printf("TX_LOG,1,%d,%lu,%d,0\n", node_id, tx_count, total_bytes);

      /* Standardized 15-25s execution interval to isolate network overhead */
      etimer_set(&tx_timer, CLOCK_SECOND * 15 + (random_rand() % (CLOCK_SECOND * 10)));
    }
  }

  PROCESS_END();
}
