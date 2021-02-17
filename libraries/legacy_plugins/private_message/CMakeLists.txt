file(GLOB HEADERS "include/clout/private_message/*.hpp")

add_library( clout_private_message
             private_message_plugin.cpp
           )

target_link_libraries( clout_private_message clout_chain clout_protocol clout_app )
target_include_directories( clout_private_message
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   clout_private_message

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
