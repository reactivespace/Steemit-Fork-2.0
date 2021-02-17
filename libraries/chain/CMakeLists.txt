file(GLOB HEADERS "include/clout/chain/*.hpp" "include/clout/chain/util/*.hpp" "include/clout/chain/smt_objects/*.hpp" "include/clout/chain/sps_objects/*.hpp")

## SORT .cpp by most likely to change / break compile
add_library( clout_chain

             # As database takes the longest to compile, start it first
             database.cpp
             index.cpp

             smt_evaluator.cpp
             sps_evaluator.cpp

             smt_objects/smt_market_maker.cpp
             smt_objects/nai_pool.cpp
             clout_evaluator.cpp
             clout_objects.cpp
             required_action_evaluator.cpp
             optional_action_evaluator.cpp

             witness_schedule.cpp
             fork_database.cpp
             comment_rewards.cpp

             shared_authority.cpp
             block_log.cpp

             generic_custom_operation_interpreter.cpp

             util/rd.cpp
             util/reward.cpp
             util/impacted.cpp
             util/advanced_benchmark_dumper.cpp
             util/smt_token.cpp
             util/sps_processor.cpp
             util/sps_helper.cpp

             ${HEADERS}
           )

target_link_libraries( clout_chain clout_jsonball clout_protocol fc chainbase clout_schema appbase mira
                       ${PATCH_MERGE_LIB} )
target_include_directories( clout_chain
                            PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include" )

if( CLANG_TIDY_EXE )
   set_target_properties(
      clout_chain PROPERTIES
      CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
   )
endif( CLANG_TIDY_EXE )

if(MSVC)
  set_source_files_properties( database.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

INSTALL( TARGETS
   clout_chain

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
INSTALL( FILES ${HEADERS} DESTINATION "include/clout/chain" )
