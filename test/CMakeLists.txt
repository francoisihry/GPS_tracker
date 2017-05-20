
set (SOURCES "../src/gps.c")

enable_testing ()
add_executable (test_lib test_lib.c ${SOURCES})
set_target_properties (test_lib PROPERTIES LINK_FLAGS -Wl,-lcunit)
add_test (test_lib ${EXECUTABLE_OUTPUT_PATH}/test_lib)

