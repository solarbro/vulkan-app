cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file")

project(VulkanApp)
set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)

add_library(AppSkeleton STATIC
	AppSkeleton/vkapp_allocator.cpp
	AppSkeleton/vkapp_allocator.h
	AppSkeleton/vkapp_gfx.cpp
	AppSkeleton/vkapp_gfx.h
	AppSkeleton/vkapp_skeleton.cpp
	AppSkeleton/vkapp_skeleton.h
)
target_link_libraries(AppSkeleton 
	PRIVATE Vulkan::Vulkan
)
target_include_directories(AppSkeleton 
	PRIVATE AppSkeleton
)

add_library(iAppSkeleton INTERFACE)
target_link_libraries(iAppSkeleton 
	INTERFACE AppSkeleton
	INTERFACE Vulkan::Vulkan
)
target_include_directories(iAppSkeleton
	INTERFACE AppSkeleton
)

add_executable(driver main.cpp)
target_link_libraries(driver
	PRIVATE iAppSkeleton
)

find_package(Catch2 REQUIRED)

add_executable(unit_tests unit_tests/unit_tests.cpp)
target_link_libraries(unit_tests 
	PRIVATE Catch2::Catch2WithMain
	PRIVATE iAppSkeleton
)

# clang-format
find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
    message(STATUS "Found clang-format: ${CLANG_FORMAT}")
	file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/AppSkeleton/*.cpp" "${CMAKE_SOURCE_DIR}/AppSkeleton/*.h")
	set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/main.cpp ${CMAKE_SOURCE_DIR}/unit_tests/unit_tests.cpp)
	# Custom target to run clang-format on source files
	add_custom_target(format
		COMMENT "Running clang-format"
		COMMAND ${CLANG_FORMAT} -i ${SOURCE_FILES}
	)

	add_dependencies(AppSkeleton format)
else()
    message(WARNING "clang-format not found")
endif()

