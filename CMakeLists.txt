cmake_minimum_required(VERSION 3.19)

project(asantest)

if(WIN32)
	set(ASANTEST_COMPILE_OPTIONS
		"/W4"
		"/wd4100"
		"/wd4244"
		"/wd4267"
		"/wd4706"
		"/fsanitize=address"
		"/Zi"
	)

else(WIN32)
	set(ASANTEST_COMPILE_OPTIONS
		"-W"
		"-Wall"
		"-Wno-unused-parameter"
	)
endif()

if(isMultiConfig)
	if(NOT "Asan" IN_LIST CMAKE_CONFIGURATION_TYPES)
		list(APPEND CMAKE_CONFIGURATION_TYPES Asan)
	endif()

else()
	set(allowedBuildTypes Asan Debug Release RelWithDebInfo MinSizeRel)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "${allowedBuildTypes}")

	if(CMAKE_BUILD_TYPE AND NOT CMAKE_BUILD_TYPE IN_LIST allowedBuildTypes)
		message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
	endif()
endif()

set(CMAKE_C_FLAGS_ASAN
	"${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer" CACHE STRING
	"Flags used by the C compiler for Asan build type or configuration." FORCE
)

set(CMAKE_CXX_FLAGS_ASAN
	"${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer" CACHE STRING
	"Flags used by the C++ compiler for Asan build type or configuration." FORCE
)

set(CMAKE_EXE_LINKER_FLAGS_ASAN
	"${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fsanitize=address" CACHE STRING
	"Linker flags to be used to create executables for Asan build type." FORCE
)

set(CMAKE_SHARED_LINKER_FLAGS_ASAN
	"${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fsanitize=address" CACHE STRING
	"Linker lags to be used to create shared libraries for Asan build type." FORCE
)

add_library(testlib "testlib.cpp")
target_compile_options(testlib PRIVATE ${ASANTEST_COMPILE_OPTIONS})

add_executable(test "test.cpp")
target_compile_options(test PRIVATE ${ASANTEST_COMPILE_OPTIONS})
target_link_libraries(test PRIVATE testlib)
