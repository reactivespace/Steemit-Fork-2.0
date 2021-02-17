file(GLOB HEADERS "include/clout/blockchain_statistics/*.hpp")

add_library( clout_blockchain_statistics
             blockchain_statistics_plugin.cpp
             blockchain_statistics_api.cpp
           )

target_link_libraries( clout_blockchain_statistics clout_chain clout_protocol clout_app )
target_include_directories( clout_blockchain_statistics
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   clout_blockchain_statistics

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)