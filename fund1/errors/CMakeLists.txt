project(errors C)
file(GLOB sources "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*.c"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*.h"
        "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*/*.h")
add_library(${PROJECT_NAME} INTERFACE ${sources})
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})
#target_link_libraries(${PROJECT_NAME} PUBLIC errors)