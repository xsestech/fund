function(dsym)
    if (APPLE)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND dsymutil $<TARGET_FILE:${PROJECT_NAME}> -o $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.dSYM
                COMMENT "Generating dSYM file for ${PROJECT_NAME}"
                VERBATIM
        )
    endif ()
endfunction()
