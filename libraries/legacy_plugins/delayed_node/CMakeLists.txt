file(GLOB HEADERS "include/clout/delayed_node/*.hpp")

add_library( clout_delayed_node
             delayed_node_plugin.cpp
           )

target_link_libraries( clout_delayed_node clout_chain clout_protocol clout_app )
target_include_directories( clout_delayed_node
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

if(MSVC)
  set_source_files_properties( delayed_node_plugin.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

install( TARGETS
   clout_delayed_node

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
