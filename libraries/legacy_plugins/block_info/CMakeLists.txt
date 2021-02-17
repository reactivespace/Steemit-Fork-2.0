file(GLOB HEADERS "include/clout/plugins/block_info/*.hpp")

add_library( clout_block_info
             ${HEADERS}
             block_info_plugin.cpp
             block_info_api.cpp
           )

target_link_libraries( clout_block_info clout_app clout_chain clout_protocol fc )
target_include_directories( clout_block_info
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
