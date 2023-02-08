add_library(symtable SHARED symtable.cpp symtableimpt.cpp)

export_headers(symtable ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_BINARY_DIR}/include/mud/script)
target_include_directories(symtable PUBLIC ${PROJECT_BINARY_DIR}/include)
