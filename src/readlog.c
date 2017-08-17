/** ********************************************************************
*
*          @file  ueireadlog.c
*
*    	   @brief  Header for ueireadlog.h
* 
*         @author Kirankumar C
* 
*         @date 2017-07-17
*
**********************************************************************/
#include <stdio.h>
#include <string.h>
#include "readlog.h"

char eventtable[17][25]={
	"INVALID",
	"FIREALERT",
	"FIRECLEAR",
	"FLOODALERT",
	"FLOODCLEAR",
	"FREEZEALERT",
	"FREEZECLEAR",
	"BATTERYLOW",
	"BATTERYNORMAL",
	"SENSOROFFLINE",
	"SENSORONLINE",
	"INTERNET_LOST",
	"INTERNET_ACTIVE",
	"CLOUD_CONNECT",
	"CLOUD_DISCONNECT",
	"FIRMWARE_UPGRADE_START",
	"FIRMWARE_UPGRADED"
};

int GetLogs(){
	struct LogData data;
	FILE *ptr=NULL;
	struct LogHeader header;
	uint16_t max=0,current=0;
	ptr = fopen(EVENT_LOG,"r+b");
	uint8_t arr[16];
	uint8_t time[8];
	int i=0;
	int sensor=0;

	if(ptr == NULL)
	{
		printf("Failed to open file\n");
		return -1;
	}
	fread(&header,sizeof(header),1,ptr);
	max = header.max;
	//	printf("Header Max:%u Cuurent:%u\n",header.max,header.current);
	printf("Event Log:");		
	if(header.current != header.max){
		current = header.current+1;	// setting to oldest log
		fseek(ptr,current*sizeof(data),SEEK_SET);

		do{
			fread(arr,16,1,ptr);
			uint64_t finaltime = (uint64_t)(arr[7] << 24 | arr[6] << 16 | arr[5] << 8 | arr[4])*
				(0x100000000) + (uint64_t)((arr[3] << 24 | arr[2] << 16 | arr[1] << 8 | arr[0])&0xffffffff);

			printf("\nTime: %llu ",finaltime);

			sensor = arr[11]<<24 | arr[10]<<16 | arr[9]<<8 | arr[8];
			if(sensor != 0)
				printf("Sensor:%lu \t",(arr[11]<<24 | arr[10]<<16 | arr[9]<<8 | arr[8]));
			else
				printf("\t\t\t");

			if (arr[12] < 17){
				printf("Event: %s ",eventtable[arr[12]]);
				//printf("Event: %02x ",arr[12]);
			}else{
				printf("Event: %02x ",arr[12]);
			}
			current =current + 1;
		}while((current-1) != max);

		rewind(ptr);

		fread(&header,sizeof(header),1,ptr);
		max = header.max;
	}
	current = 1;

	do{
		fread(arr,16,1,ptr);
		uint64_t finaltime = (uint64_t)(arr[7] << 24 | arr[6] << 16 | arr[5] << 8 | arr[4])*
			(0x100000000) + (uint64_t)((arr[3] << 24 | arr[2] << 16 | arr[1] << 8 | arr[0])&0xffffffff);

		printf("\nTime: %llu ",finaltime);

		sensor = arr[11]<<24 | arr[10]<<16 | arr[9]<<8 | arr[8];
		if(sensor != 0)
			printf("Sensor:%lu \t",(arr[11]<<24 | arr[10]<<16 | arr[9]<<8 | arr[8]));
		else
			printf("\t\t\t");

		if (arr[12] < 17){
			printf("Event: %s ",eventtable[arr[12]]);
			//printf("Event: %02x ",arr[12]);
		}else{
			printf("Event: %02x ",arr[12]);
		}
		current =current + 1;
	}while((current-1) != header.current);

	fclose(ptr);
	printf("\n");

	return 0;
}

int main()
{
	GetLogs();
}

