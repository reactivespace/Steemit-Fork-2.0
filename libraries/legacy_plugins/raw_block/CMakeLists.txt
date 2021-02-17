file(GLOB HEADERS "include/clout/plugins/raw_block/*.hpp")

add_library( clout_raw_block
             ${HEADERS}
             raw_block_plugin.cpp
             raw_block_api.cpp
           )

target_link_libraries( clout_raw_block clout_app clout_chain clout_protocol fc )
target_include_directories( clout_raw_block
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
