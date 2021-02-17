add_executable( cloutd main.cpp )
if( UNIX AND NOT APPLE )
  set(rt_library rt )
endif()

find_package( Gperftools QUIET )
if( GPERFTOOLS_FOUND )
    message( STATUS "Found gperftools; compiling cloutd with TCMalloc")
    list( APPEND PLATFORM_SPECIFIC_LIBS tcmalloc )
endif()

if( CLOUT_STATIC_BUILD )
   target_link_libraries( cloutd PRIVATE
      "-static-libstdc++ -static-libgcc"
      appbase
      clout_utilities
      clout_plugins
      ${CMAKE_DL_LIBS}
      ${PLATFORM_SPECIFIC_LIBS}
   )
else( CLOUT_STATIC_BUILD )
   target_link_libraries( cloutd PRIVATE
      appbase
      clout_utilities
      clout_plugins
      ${CMAKE_DL_LIBS}
      ${PLATFORM_SPECIFIC_LIBS}
   )
endif( CLOUT_STATIC_BUILD )

if( CLANG_TIDY_EXE )
   set_target_properties(
      cloutd PROPERTIES
      CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
   )
endif( CLANG_TIDY_EXE )

install( TARGETS
   cloutd

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
