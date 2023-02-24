file(GLOB CPP CONFIGURE_DEPENDS *.cpp)
file(GLOB H CONFIGURE_DEPENDS *.h)

add_library(network SHARED ${CPP} ${H})
target_include_directories(network PRIVATE ${Boost_INCLUDE_DIRS})

export_headers(network ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_BINARY_DIR}/include/mud/network)
