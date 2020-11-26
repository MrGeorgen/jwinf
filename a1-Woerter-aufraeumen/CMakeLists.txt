file(GLOB A1SOURCES "src/*.c")
file(GLOB ACLSOURCES "../lib/acl/src/*.c")
add_executable(a1 ${A1SOURCES} ${ACLSOURCES})
target_link_libraries(a1 PRIVATE m)
