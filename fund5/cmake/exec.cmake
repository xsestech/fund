include(dsym)
function(add_exec_auto)
    file(GLOB sources "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*.c"
            "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*.h"
            "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*/*.h")
    add_executable(${PROJECT_NAME} ${sources})
    target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
    dsym()
endfunction()