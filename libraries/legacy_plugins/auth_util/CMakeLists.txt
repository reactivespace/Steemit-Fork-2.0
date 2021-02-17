file(GLOB HEADERS "include/clout/plugins/auth_util/*.hpp")

add_library( clout_auth_util
             ${HEADERS}
             auth_util_plugin.cpp
             auth_util_api.cpp
           )

target_link_libraries( clout_auth_util clout_app clout_chain clout_protocol fc )
target_include_directories( clout_auth_util
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
