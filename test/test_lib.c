#include "CUnit/Basic.h"
#include <CUnit/CUnit.h>
#include "../src/gps.h"


void test_read_coordonate(void) {
	char trame[100] = "+CGNSINF: 1,1,20170520190355.000,50.837443,4.367987,94.900,0.11,313.2,1,,0.8,1.2,1.0,,14,11,,,39,,";
	coordonate* c =read_coordonate( trame);
	//printf(c->fix_status);
	CU_ASSERT_EQUAL(c->run_status, '1');
	CU_ASSERT_EQUAL(c->fix_status, '1');
	CU_ASSERT_STRING_EQUAL(c->utc_date_and_time, "20170520190355.000");
	CU_ASSERT_STRING_EQUAL(c->latitude, "50.837443");
	CU_ASSERT_STRING_EQUAL(c->longitude, "4.367987");
	CU_ASSERT_STRING_EQUAL(c->altitude, "94.900");
	CU_ASSERT_STRING_EQUAL(c->speed_over_ground, "0.11");
	CU_ASSERT_STRING_EQUAL(c->course_over_ground, "313.2")

	char trame2[100] = "+CGNSINF: 1,1,20170520214256.000,50.837453,4.368082,85.800,0.06,104.6,1,,1.0,1.7,1.4,,12,10,,,32,,";
	coordonate* c2 =read_coordonate( trame2);
	//printf(c->fix_status);
	CU_ASSERT_EQUAL(c2->run_status, '1');
	CU_ASSERT_EQUAL(c2->fix_status, '1');
	CU_ASSERT_STRING_EQUAL(c2->utc_date_and_time, "20170520214256.000");
	CU_ASSERT_STRING_EQUAL(c2->latitude, "50.837453");
	CU_ASSERT_STRING_EQUAL(c2->longitude, "4.368082");
	CU_ASSERT_STRING_EQUAL(c2->altitude, "85.800");
	CU_ASSERT_STRING_EQUAL(c2->speed_over_ground, "0.06");
	CU_ASSERT_STRING_EQUAL(c2->course_over_ground, "104.6")

	char trame3[100] = "+CGNSINF: 1,1,20170520214258.000,50.837453,4.368082,85.800,0.07,53.2,1,,1.0,1.7,1.4,,12,10,,,31,,";
	coordonate* c3 =read_coordonate( trame3);
	//printf(c->fix_status);
	CU_ASSERT_EQUAL(c3->run_status, '1');
	CU_ASSERT_EQUAL(c3->fix_status, '1');
	CU_ASSERT_STRING_EQUAL(c3->utc_date_and_time, "20170520214258.000");
	CU_ASSERT_STRING_EQUAL(c3->latitude, "50.837453");
	CU_ASSERT_STRING_EQUAL(c3->longitude, "4.368082");
	CU_ASSERT_STRING_EQUAL(c3->altitude, "85.800");
	CU_ASSERT_STRING_EQUAL(c3->speed_over_ground, "0.07");
	CU_ASSERT_STRING_EQUAL(c3->course_over_ground, "53.2")

	char trame4[100] = "+CGNSINF: 1,1,20170520214259.000,50.837453,4.368082,85.800,0.00,294.5,1,,1.0,1.7,1.4,,12,10,,,31,,";
	coordonate* c4 =read_coordonate( trame4);
	//printf(c->fix_status);
	CU_ASSERT_EQUAL(c4->run_status, '1');
	CU_ASSERT_EQUAL(c4->fix_status, '1');
	CU_ASSERT_STRING_EQUAL(c4->utc_date_and_time, "20170520214259.000");
	CU_ASSERT_STRING_EQUAL(c4->latitude, "50.837453");
	CU_ASSERT_STRING_EQUAL(c4->longitude, "4.368082");
	CU_ASSERT_STRING_EQUAL(c4->altitude, "85.800");
	CU_ASSERT_STRING_EQUAL(c4->speed_over_ground, "0.00");
	CU_ASSERT_STRING_EQUAL(c4->course_over_ground, "294.5")
}

int main (int argc, char** argv) {

        CU_pSuite pSuite = NULL;

        /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", NULL, NULL);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }


   CU_add_test(pSuite, "read coordonate test", test_read_coordonate);

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
