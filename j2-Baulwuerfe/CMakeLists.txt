file(GLOB J2SOURCES "src/*.c")
file(GLOB ACLSOURCES "../lib/acl/src/*.c")
add_executable(j2 ${J1SOURCES} ${ACLSOURCES})
target_link_libraries(j2 PRIVATE m)
