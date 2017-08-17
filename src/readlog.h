#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>

#define EVENT_LOG	"/etc/eventlog.bin"

enum LogTypeEnum{
	LOG_INVALID,
	LOG_FIREALERT,
	LOG_FIRECLEAR,
	LOG_FLOODALERT,
	LOG_FLOODCLEAR,
	LOG_FREEZEALERT,
	LOG_FREEZECLEAR,
	LOG_BATTERYLOW,
	LOG_BATTERYNORMAL,
	LOG_SENSOROFFLINE,
	LOG_SENSORONLINE,
	LOG_CONNLOST,
	LOG_CONNACTIVE,
	LOG_CLOUD_CON,
	LOG_CLOUD_DISCON,
	LOG_FIRMWARE_UPGRADE_START,
	LOG_FIRMWARE_UPGRADE
};

struct LogData{
	uint16_t version1;
	uint16_t event;
	uint32_t sensor;
	uint64_t time;
};

struct LogHeader{
	uint16_t max;
	uint16_t current;
	uint32_t version2;
	uint64_t version1;
};

