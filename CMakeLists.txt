cmake_minimum_required (VERSION 3.14)

project ("mandy")

file(GLOB SRC_DIR CONFIGURE_DEPENDS "src/*.hpp" "src/*.cpp" "src/**/*.hpp" "src/**/*.cpp")

add_executable (mandy ${SRC_DIR})

# Find SFML
# set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS graphics REQUIRED)
if(SFML_FOUND)
  target_link_libraries(mandy sfml-graphics)
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
