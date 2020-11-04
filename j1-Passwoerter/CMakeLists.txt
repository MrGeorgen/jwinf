file(GLOB J1SOURCES "src/*.c")
file(GLOB ACLSOURCES "../lib/acl/src/*.c")
add_executable(j1 ${J1SOURCES} ${ACLSOURCES})
target_link_libraries(j1 PRIVATE m)
