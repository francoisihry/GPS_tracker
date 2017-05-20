#import "gps.h"
#include <stdio.h>
#include <stdlib.h>

coordonate* read_coordonate(char* trame){
	//char lat[10], longi[10];
	coordonate* c = malloc(sizeof(coordonate));
	// +CGNSINF: 1,1,20170520190355.000,50.837443,4.367987,94.900,0.11,313.2,1,,0.8,1.2,1.0,,14,11,,,39,,
	char p;
	sscanf( trame, "+CGNSINF: %c,%c,%[^','],"
			"%[^','],%[^','],%[^',']"
			",%[^','],%[^','?]", &(c->run_status),
										&(c->fix_status),
										c->utc_date_and_time,
										c->latitude,
										c->longitude,
										c->altitude,
										c->speed_over_ground,
										c->course_over_ground);
	return c;
}
