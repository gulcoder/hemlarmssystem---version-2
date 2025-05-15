#include "datetime.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/dns.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NTP_SERVER "pool.ntp.org"
#define NTP_MSG_LEN 48
#define NTP_PORT 123
#define NTP_DELTA 2208988800
#define NTP_TIMEOUT_MS 10000

static time_t latest_timestamp = 0;

typedef struct {
    ip_addr_t server_address;
    struct udp_pcb *pcb;
    bool resolved;
} ntp_state_t;

static void ntp_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port) {
    if (p->tot_len == NTP_MSG_LEN) {
        uint8_t buf[4];
        pbuf_copy_partial(p, buf, 4, 40);
        uint32_t seconds = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
        latest_timestamp = seconds - NTP_DELTA;
	struct timeval tv = { .tv_sec = latest_timestamp, .tv_usec = 0};
	settimeofday(&tv, NULL);
        struct tm *t = gmtime(&latest_timestamp);
        printf("[NTP] Tid synkad: %02d-%02d-%04d %02d:%02d:%02d UTC\n",
               t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
               t->tm_hour, t->tm_min, t->tm_sec);
    }
    pbuf_free(p);
}

static void ntp_send(ntp_state_t *state) {
    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, NTP_MSG_LEN, PBUF_RAM);
    memset(p->payload, 0, NTP_MSG_LEN);
    ((uint8_t *)p->payload)[0] = 0x1B; // LI, Version, Mode
    udp_sendto(state->pcb, p, &state->server_address, NTP_PORT);
    pbuf_free(p);
}

static void ntp_dns_cb(const char *name, const ip_addr_t *ipaddr, void *arg) {
    ntp_state_t *state = (ntp_state_t *)arg;
    if (ipaddr) {
        state->server_address = *ipaddr;
        ntp_send(state);
        state->resolved = true;
    } else {
        printf("[NTP] DNS-förfrågan misslyckades\n");
    }
}

void datetime_init(void) {
    ntp_state_t *state = calloc(1, sizeof(ntp_state_t));
    state->pcb = udp_new_ip_type(IPADDR_TYPE_ANY);
    udp_recv(state->pcb, ntp_recv, state);

    cyw43_arch_lwip_begin();
    err_t err = dns_gethostbyname(NTP_SERVER, &state->server_address, ntp_dns_cb, state);
    if (err == ERR_OK) {
        ntp_send(state);
        state->resolved = true;
    } else if (err != ERR_INPROGRESS) {
        printf("[NTP] DNS-fel\n");
    }
    cyw43_arch_lwip_end();
}

time_t datetime_get_timestamp(void) {
    return latest_timestamp;
}

struct tm* datetime_get_time(void) {

	time_t now_raw = time(NULL);
	struct tm *now = localtime(&now_raw);
	if (now){
		now->tm_hour +=2;
		if(now->tm_hour >=24){
			now->tm_hour -=24;
		}
	}



	return now;
}

