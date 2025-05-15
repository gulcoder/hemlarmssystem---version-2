#ifndef DATETIME_H
#define DATETIME_H

#include <time.h>


// Initiera och starta NTP-tidssynk
void datetime_init(void);

// Returnerar senaste uppdaterade timestamp
time_t datetime_get_timestamp(void);

// Returnerar pointer till senaste uppdaterade UTC-struktur
struct tm* datetime_get_time(void);

#endif

