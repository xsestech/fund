function(index_tests)
    if (ENABLE_TESTING)
    message("Adding test for ${PROJECT_NAME}")
    enable_testing()


    file(GLOB tests "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*/*.test.cpp"
            "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*/*/*.test.cpp")


    message("TESTS: ${tests}")
    message("${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*.c")
    foreach(file ${tests})
        set(name)

        get_filename_component(name ${file} NAME_WE)
        add_executable("${name}_tests"
                ${sources}
                ${file}
        )
        target_link_libraries("${name}_tests" PUBLIC gtest_main  ${PROJECT_NAME})
        add_test(NAME ${name} COMMAND "${name}_tests")
        message("Adding test ${name}_tests")
    endforeach()
    endif ()
endfunction()