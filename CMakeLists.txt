cmake_minimum_required(VERSION 3.10)
project(RouteProfileExtractor)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files
set(SOURCES
    src/csv_generator.cpp
    src/gradient_calc.cpp
    src/json_parser.cpp
    src/long_lat_to_x_y.cpp
    src/main.cpp
    src/mapbox_request.cpp
)

# Header files (for IDEs and inclusion)
set(HEADERS
    src/csv_generator.hpp
    src/gradient_calc.hpp
    src/json_parser.hpp
    src/long_lat_to_x_y.hpp
    src/mapbox_request.hpp
)

# Find and include the CURL library
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

# Executable
add_executable(RouteProfileExtractor ${SOURCES} ${HEADERS})

# Copy .env file after build
add_custom_command(
    TARGET RouteProfileExtractor
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/.env ${CMAKE_BINARY_DIR}/.env
)

# Link CURL library
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
