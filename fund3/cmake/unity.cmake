function(add_unity)
    message("Adding test for ${PROJECT_NAME}")
    enable_testing()

    add_compile_definitions(UNITY_INCLUDE_DOUBLE)

    message("${CMAKE_HOME_DIRECTORY}")
    if (NOT TARGET unity)

        add_library(unity STATIC
                "${CMAKE_HOME_DIRECTORY}/unity/src/unity.c"
        )
        target_include_directories(unity PUBLIC
                "${CMAKE_HOME_DIRECTORY}/unity/src"
        )
    endif()
    file(GLOB tests "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*/*.test.c"
            "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*.test.c"
            "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*/*/*.test.c")


    message("TESTS: ${tests}")
    message("${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*.c")
    foreach(file ${tests})
        set(name)

        get_filename_component(name ${file} NAME_WE)
        add_executable("${name}_tests"
                ${sources}
                ${file}
        )
        target_link_libraries(unity PUBLIC libconfig)
        target_link_libraries("${name}_tests" PUBLIC unity ${PROJECT_NAME})
        add_test(NAME ${name} COMMAND "${name}_tests")
        message("Adding test ${name}_tests")
    endforeach()
endfunction()