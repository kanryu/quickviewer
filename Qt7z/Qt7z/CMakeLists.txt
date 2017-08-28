add_definitions(
    -DQT7Z_LIBRARY
)

# set all include directories for in and out of source builds
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

if (WIN32)
    include(7zip.cmake)
else (WIN32)
    include(p7zip.cmake)
endif (WIN32)

set(SRCS ${7Z_SRCS}
    "qt7zfileinfo.cpp"
    "qt7zpackage.cpp"
)

file(GLOB PUBLIC_HEADERS "*.h")

qt_wrap_cpp(MOC_SRCS ${PUBLIC_HEADERS})
set(SRCS ${SRCS} ${MOC_SRCS})

add_library(qt7z ${SRCS})
set_target_properties(qt7z PROPERTIES VERSION 1.0.0 SOVERSION 1)
if(APPLE)
    target_link_libraries(qt7z Qt5::Core ${COREFOUNDATION_LIBRARY})
elseif(UNIX)
    target_link_libraries(qt7z Qt5::Core ${CMAKE_THREAD_LIBS_INIT})
else()
    target_link_libraries(qt7z Qt5::Core)
endif()

if(BUILD_SHARED_LIBS)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/qt7z)
    install(TARGETS qt7z LIBRARY DESTINATION ${LIB_DESTINATION} ARCHIVE DESTINATION ${LIB_DESTINATION} RUNTIME DESTINATION ${LIB_DESTINATION})
endif(BUILD_SHARED_LIBS)
