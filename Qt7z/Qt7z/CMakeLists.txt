add_definitions(
    -DQT7Z_LIBRARY
)

# set all include directories for in and out of source builds
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

file(GLOB SRCS "*.c" "*.cpp" "7z/*.c")
file(GLOB PUBLIC_HEADERS "*.h")

qt_wrap_cpp(MOC_SRCS ${PUBLIC_HEADERS})
set(SRCS ${SRCS} ${MOC_SRCS})

add_library(qt7z ${SRCS})
set_target_properties(qt7z PROPERTIES VERSION 1.0.0 SOVERSION 1)
# target_link_libraries(qt7z ${QT_QTMAIN_LIBRARY} ${QT_QTCORE_LIBRARY})
target_link_libraries(qt7z Qt5::Core)

install(FILES ${PUBLIC_HEADERS} DESTINATION include/qt7z)
install(TARGETS qt7z LIBRARY DESTINATION ${LIB_DESTINATION} ARCHIVE DESTINATION ${LIB_DESTINATION} RUNTIME DESTINATION ${LIB_DESTINATION})
