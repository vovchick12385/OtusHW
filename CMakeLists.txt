cmake_minimum_required (VERSION 3.8)

project ("IPFilter" VERSION 1.2.3)


add_executable (IPFilter "ip_filter.cpp")

if (MSVC)
    target_compile_options(IPFilter PRIVATE
        /W4
    )
    target_compile_options(IPFilter PRIVATE
        /W4
    )
else ()
    target_compile_options(IPFilter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(IPFilter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS IPFilter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)


