project(libinteractive VERSION 1.0.0 LANGUAGES C)
include(lib)
add_lib_auto()
target_link_libraries(${PROJECT_NAME} PUBLIC liberrors libstruct)