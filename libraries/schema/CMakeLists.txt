file(GLOB HEADERS "include/clout/schema/*.hpp")
add_library( clout_schema schema.cpp ${HEADERS} )
target_link_libraries( clout_schema fc )
target_include_directories( clout_schema PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   clout_schema

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
install( FILES ${HEADERS} DESTINATION "include/clout/schema" )
