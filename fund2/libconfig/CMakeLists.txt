project(libconfig C)
set(PATH_TO_CODE "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}")
configure_file (
        "${PATH_TO_CODE}/config.h.in"
        "${PATH_TO_CODE}/config.h"
)
file(GLOB sources "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*.c"
        "${PATH_TO_CODE}/*.h"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*/*.h")
add_library(${PROJECT_NAME} INTERFACE ${sources})
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})
#target_link_libraries(${PROJECT_NAME} PUBLIC liberrors)