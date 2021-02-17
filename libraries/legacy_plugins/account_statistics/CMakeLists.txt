file(GLOB HEADERS "include/clout/account_statistics/*.hpp")

add_library( clout_account_statistics
             account_statistics_plugin.cpp
             account_statistics_api.cpp
           )

target_link_libraries( clout_account_statistics clout_chain clout_protocol clout_app )
target_include_directories( clout_account_statistics
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   clout_account_statistics

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)