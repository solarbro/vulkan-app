cmake_minimum_required(VERSION 3.10)
project(VulkanApp)
set(CMAKE_CXX_STANDARD 20)

# Use Vulkan SDK environment variable
find_package(Vulkan REQUIRED)
#if(NOT DEFINED ENV{VULKAN_SDK})
#    message(FATAL_ERROR "VULKAN_SDK environment variable is not set.")
#endif()

#add_library(libvulkan INTERFACE)
#target_include_directories(libvulkan
#	INTERFACE "$ENV{VULKAN_SDK}/Include"
#)
#target_link_libraries(libvulkan 
#	INTERFACE "$ENV{VULKAN_SDK}/Lib/vulkan-1.lib"
#)

add_library(AppSkeleton STATIC
	AppSkeleton/app_skeleton.cpp
	AppSkeleton/app_skeleton.h
)
target_link_libraries(AppSkeleton 
	PRIVATE Vulkan::Vulkan
)

add_library(iAppSkeleton INTERFACE)
target_link_libraries(iAppSkeleton 
	INTERFACE AppSkeleton
	INTERFACE Vulkan::Vulkan
)
target_include_directories(iAppSkeleton
	INTERFACE AppSkeleton
)

add_executable(test main.cpp)
target_link_libraries(test
	PRIVATE iAppSkeleton
)
