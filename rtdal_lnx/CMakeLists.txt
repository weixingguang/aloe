if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build. This is bad practice.")
endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})


if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
	cmake_minimum_required (VERSION 2.6)
	project (alcore_lnx)

	# The version number.
	set (ALCORE_LNX_VERSION_MAJOR 1)
	set (ALCORE_LNX_VERSION_MINOR 0)
endif()

# find UHD driver
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
find_package(UHD)
if (UHD_FOUND)
		include_directories(${UHD_INCLUDE_DIRS})
		set(COMPILE_DAC "-DHAVE_UHD")
		set(LINK_DAC "${Boost_LIBRARIES}")
		set(DAC_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/dac/uhd/uhd_imp.cpp")
else()
	message("UHD not found. USRP devices won't be supported")
	set(COMPILE_DAC "")
	set(LINK_DAC "")	
	set(DAC_SOURCES "")
	set(UHD_LIBRARIES "")
endif()

# find Xenomai Library
if(XENOMAI_ENABLE)
	find_package(Xenomai)
	if (XENOMAI_DIR) 
		include_directories(${XENOMAI_INCLUDE_DIR} ${XENOMAI_INCLUDE_POSIX_DIR})
		set(COMPILE_XENOMAI "${XENOMAI_CFLAGS}")
		set(LINK_XENOMAI "${XENOMAI_LDFLAGS} ${XENOMAI_LIBRARY_POSIX} ${XENOMAI_LIBRARY_XENOMAI}")
	else()
		set(COMPILE_XENOMAI "")
		set(LINK_XENOMAI "")	
	endif()
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/dac/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/extern/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/dac/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../volk/include")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/../volk/include")

file(GLOB_RECURSE rtdal_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
list(APPEND rtdal_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/extern/message_queue.c" "${CMAKE_CURRENT_SOURCE_DIR}/extern/ring_buff_posix_osal.c" "${CMAKE_CURRENT_SOURCE_DIR}/extern/ring_buff.c"  "${CMAKE_CURRENT_SOURCE_DIR}/extern/rtdal_datafile.c")

# runcf executable
add_executable(runcf ${rtdal_SOURCES} ${DAC_SOURCES})
set_target_properties(runcf PROPERTIES COMPILE_FLAGS "${CFDEB} ${COMPILE_DAC} -Wno-format ${COMPILE_XENOMAI} ${MATFILE_CFLAGS}")

target_link_libraries (runcf "-Wl,--whole-archive" oesr)
target_link_libraries (runcf "-Wl,--no-whole-archive" ${LINK_XENOMAI} pthread volk rt dl m ${LINK_DAC})
target_link_libraries (runcf ${UHD_LIBRARIES})


set(CMAKE_BINARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# install runcf
install(TARGETS runcf DESTINATION bin)
