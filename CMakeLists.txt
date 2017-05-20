set(AVRCPP   avr-g++)
set(AVRC     avr-gcc)
set(AVRDUDE  avrdude)
set(AVR_PROGRAMMER usbasp)
set(AVR_MCU atmega8)
set(F_CPU 8000000)

set(CMAKE_SYSTEM_NAME  Generic)
set(CMAKE_CXX_COMPILER ${AVRCPP})
set(CMAKE_C_COMPILER   ${AVRC})
set(CMAKE_ASM_COMPILER   ${AVRC})

set(AVR_SIZE_ARGS -C;--mcu=${AVR_MCU})
project (GPS_tracker C CXX C)

# Important project paths
set(BASE_PATH    "${${PROJECT_NAME}_SOURCE_DIR}")
set(INC_PATH     "${BASE_PATH}/include")
set(SRC_PATH     "${BASE_PATH}/src")
set(LIB_DIR_PATH "${BASE_PATH}/lib")

# Files to be compiled
file(GLOB SRC_FILES "${SRC_PATH}/*.cpp"
                    "${SRC_PATH}/*.cc"
                    "${SRC_PATH}/*.c"
                    "${SRC_PATH}/*.cxx"
                    "${SRC_PATH}/*.S"
                    "${SRC_PATH}/*.s"
                    "${SRC_PATH}/*.sx"
                    "${SRC_PATH}/*.asm")

set(LIB_SRC_FILES)
set(LIB_INC_PATH)
file(GLOB LIBRARIES "${LIB_DIR_PATH}/*")
foreach(subdir ${LIBRARIES})
    file(GLOB lib_files "${subdir}/*.cpp"
                        "${subdir}/*.cc"
                        "${subdir}/*.c"
                        "${subdir}/*.cxx"
                        "${subdir}/*.S"
                        "${subdir}/*.s"
                        "${subdir}/*.sx"
                        "${subdir}/*.asm")
    if(IS_DIRECTORY ${subdir})
        list(APPEND LIB_INC_PATH  "${subdir}")
    endif()
    list(APPEND LIB_SRC_FILES "${lib_files}")
endforeach()

# Compiler flags
set(CSTANDARD "-std=gnu99")
set(CDEBUG    "-gstabs -g -ggdb")
set(CWARN     "-Wall -Wstrict-prototypes -Wl,--gc-sections -Wl,--relax")
set(CTUNING   "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ffunction-sections -fdata-sections")
set(COPT      "-Os -lm -lprintf_flt")
set(CMCU      "-mmcu=${AVR_MCU}")
set(CDEFS     "-DF_CPU=${F_CPU}")

set(CFLAGS   "${CMCU} ${CDEBUG} ${CDEFS} ${COPT} ${CWARN} ${CSTANDARD} ${CTUNING}")
set(CXXFLAGS "${CMCU} ${CDEBUG} ${CDEFS} ${COPT} ${CTUNING}")

set(CMAKE_C_FLAGS   "${CFLAGS}")
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")
set(CMAKE_ASM_FLAGS   "${CFLAGS}")

# Project setup
add_executable(${PROJECT_NAME} ${SRC_FILES} ${LIB_SRC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.elf")


# Config logging
message("* ")
message("* Project Name:\t${PROJECT_NAME}")
message("* Project Source:\t${SRC_PATH}")
message("* Project Include:\t${INC_PATH}")
message("* Library Include:\t${LIB_INC_PATH}")
message("* ")
message("* Project Source Files:\t${SRC_FILES}")
message("* Library Source Files:\t${LIB_SRC_FILES}")
message("* ")
message("* C Flags:\t${CMAKE_C_FLAGS}")
message("* ")
message("* CXX Flags:\t${CMAKE_C_FLAGS}")
message("* ")

