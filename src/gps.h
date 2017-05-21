
typedef struct coordonate
{
	char run_status;
	char fix_status;
	char utc_date_and_time[19];
	char latitude[11];
	char longitude[12];
	char altitude[9];
	char speed_over_ground[7];
	char course_over_ground[7]
/*
	char fix_mode;
	char hdop[5];
	char pdop[5];
	char vdop[5];
	char gps_satellite_in_view[2];
	char gnss_satellite_used[2];
	char glon_satellite_in_view[2];
	char c_no_max[2];
	char hpa[7];

*/

}Coordonate;



void read_coordonate(Coordonate* fixed_position, char* trame);
