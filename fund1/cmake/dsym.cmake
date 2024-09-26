function(add_exec_auto)
    file(GLOB sources "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*.c"
            "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*.h"
            "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*/*.h")
    add_executable(${PROJECT_NAME} ${sources})
    target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
    if(APPLE)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND dsymutil $<TARGET_FILE:${PROJECT_NAME}> -o $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.dSYM
                COMMENT "Generating dSYM file for ${PROJECT_NAME}"
                VERBATIM
        )
    endif ()
endfunction()