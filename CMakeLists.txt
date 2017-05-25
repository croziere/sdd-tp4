project(TP4)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c hash.c hash.h table.c table.h file.c file.h helpers.h controller.c controller.h)
add_executable(TP4 ${SOURCE_FILES})