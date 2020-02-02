cmake_minimum_required (VERSION 3.14)

project ("mandy")

add_executable (mandy "mandy.cpp" "mandy.h")

# Find SFML
# set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS graphics REQUIRED)
if(SFML_FOUND)
  target_link_libraries(mandy sfml-graphics)
endif()