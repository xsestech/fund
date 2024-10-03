cmake_minimum_required(VERSION 3.27)
project(fund_lab1 C)

#set(CMAKE_C_STANDARD 17)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
option(LIBCPP "Build with libc++" FALSE)
option(ENABLE_ASAN "Enable address sanitizer" FALSE)
option(ENABLE_CLANG_TIDY "Enable testing with clang-tidy" FALSE)
option(ENABLE_CPPCHECK "Enable testing with cppcheck" FALSE)
option(SIMPLE_BUILD "Build the project as minimally as possible" FALSE)
option(FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." TRUE)
option(DEBUG_LOGGING "Enabling debug logging" FALSE)
option(BUILD_DOC "Build documentation" FALSE)
add_library(project_warnings INTERFACE)
add_library(project_options INTERFACE)

target_compile_features(project_options INTERFACE c_std_23)


if (ENABLE_ASAN)
    target_compile_options(project_options INTERFACE -fsanitize=address)
    target_link_libraries(project_options INTERFACE -fsanitize=address)

endif ()

target_compile_options(project_warnings
        INTERFACE
        -Wall
        -Wextra
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wpedantic
        -Wconversion
#        -Wsign-conversion
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2)

# some GCC specific warnings. These flags are added only if the used compiler is GCC.
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(project_warnings
            INTERFACE
            -Wmisleading-indentation
            -Wduplicated-cond
            -Wlogical-op
            -Wuseless-cast
    )
    target_link_libraries(project_options INTERFACE stdc++fs)
endif ()

if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        target_compile_options(project_options INTERFACE -fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        target_compile_options(project_options INTERFACE -fcolor-diagnostics)
    endif ()
endif ()

if (${DEBUG_LOGGING})
    target_compile_options(project_options INTERFACE -g)
    target_link_libraries(project_options INTERFACE -g)
endif ()

find_program(CCACHE ccache)
if (CCACHE)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif ()

if (ENABLE_CPPCHECK)
    find_program(CPPCHECK cppcheck)
    if (CPPCHECK)
        set(CMAKE_CXX_CPPCHECK
                ${CPPCHECK}
                --suppress=syntaxError
                --suppress=missingIncludeSystem
                --suppress=unusedFunction
                --check-level=exhaustive
                --enable=all
                --inconclusive)
        set(CMAKE_C_CPPCHECK
                ${CPPCHECK}
                --suppress=syntaxError
                --suppress=unusedFunction
                --suppress=missingIncludeSystem
                --check-level=exhaustive
                --enable=all
                --inconclusive)
    else ()
        message(SEND_ERROR "cppcheck requested but executable not found")
    endif ()
endif ()

if (ENABLE_CLANG_TIDY)
    find_program(CLANGTIDY clang-tidy)
    if (CLANGTIDY)
        set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY})
    else ()
        message(SEND_ERROR "clang-tidy requested but executable not found")
    endif ()
endif ()
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    set(DOXYGEN_HTML ${CMAKE_CURRENT_SOURCE_DIR}/docs/html/index.html)
    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target(doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
    ADD_CUSTOM_COMMAND(OUTPUT ${DOXYGEN_HTML}
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
            MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
            COMMENT "Generating Doxygen documentation"
            VERBATIM)
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

message("#########################################")
message("\t \t Summary")
message("#########################################")
message("Build type:       \t ${CMAKE_BUILD_TYPE}")
message("Install prefix:   \t ${CMAKE_INSTALL_PREFIX}")
message("Testing enabled:  \t ${ENABLE_TESTING}")
message("Clang-tidy:       \t ${ENABLE_CLANG_TIDY}")
message("Cppcheck:         \t ${ENABLE_CPPCHECK}")
message("Compiler:         \t ${CMAKE_CXX_COMPILER_ID}")
message("Sanizizers:       \t ${ENABLE_ASAN}")
message("Build libcpp:     \t ${LIBCPP}")
message("CCache executable:\t ${CCACHE}")
message("Building doc:     \t ${BUILD_DOC}")
message("------------------------------------------")
message("Version:          \t ${PROJECT_VERSION}")

add_subdirectory(liberrors)
#add_subdirectory(libcli)
#add_subdirectory(libcli2)
add_subdirectory(libcli3)
add_subdirectory(libtask)
add_subdirectory(libmath)
add_subdirectory(libfiles)
add_subdirectory(libstring)
add_subdirectory(libstruct)
add_subdirectory(libconfig)
add_subdirectory(task1)
add_subdirectory(task2)
add_subdirectory(task3)
add_subdirectory(task4)
add_subdirectory(task5)
add_subdirectory(task6)
add_subdirectory(task7)
add_subdirectory(task8)
add_subdirectory(task9)

#target_link_libraries(libcli PUBLIC liberrors project_options)
target_link_libraries(libmath PUBLIC liberrors libconfig project_options)
target_link_libraries(libstring PUBLIC liberrors libconfig project_options)
target_link_libraries(libstruct PUBLIC liberrors libconfig project_options)
target_link_libraries(libcli3 PUBLIC liberrors libstring project_options)
target_link_libraries(libfiles PUBLIC liberrors libconfig libstring project_options)
target_link_libraries(libtask PUBLIC liberrors libcli3 libmath libfiles libconfig libstruct project_options libstring)
target_link_libraries(task1 PUBLIC liberrors libcli3 libmath libstring libtask project_options
        project_warnings)
target_link_libraries(task2 PUBLIC liberrors libcli3 libtask project_options
        project_warnings)
target_link_libraries(task3 PUBLIC liberrors libcli3 libmath libtask project_options
        project_warnings)
target_link_libraries(task4 PUBLIC liberrors libcli3 libtask project_options
        project_warnings)
target_link_libraries(task5 PUBLIC liberrors libcli3 libmath libtask project_options
        project_warnings)
target_link_libraries(task6 PUBLIC liberrors libcli3 libmath libtask project_options
        project_warnings)
target_link_libraries(task7 PUBLIC liberrors libcli3 libtask project_options
        project_warnings)
target_link_libraries(task8 PUBLIC liberrors libcli3 libstring libtask project_options
        project_warnings)
target_link_libraries(task9 PUBLIC liberrors libcli3 libtask libstruct project_options
        project_warnings)

find_program(DSYMUTIL_PROGRAM dsymutil)
if (APPLE)
    add_custom_command(TARGET ${task_name} POST_BUILD
            COMMAND dsymutil $<TARGET_FILE:${task_name}>
            COMMENT Generate dSYM files for ${task_name}
            OUTPUT $
    )
endif ()
