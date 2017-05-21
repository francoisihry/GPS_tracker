#import "gps.h"
#include <stdio.h>
#include <stdlib.h>

void read_coordonate(Coordonate* fixed_position, char* trame)
{
	// +CGNSINF: 1,1,20170520190355.000,50.837443,4.367987,94.900,0.11,313.2,1,,0.8,1.2,1.0,,14,11,,,39,,
	char p;
	char run_status;
	sscanf( trame, " +CGNSINF: %c,%c,%[^','],"
			"%[^','],%[^','],%[^',']"
			",%[^','],%[^','?]", &(run_status),
										&(fixed_position->fix_status),
										fixed_position->utc_date_and_time,
										fixed_position->latitude,
										fixed_position->longitude,
										fixed_position->altitude,
										fixed_position->speed_over_ground,
										fixed_position->course_over_ground);
	fixed_position->run_status = '1';

	//printf(fixed_position->run_status);
}
