cmake_minimum_required(VERSION 3.10)
project(VulkanApp)
set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)

add_library(AppSkeleton STATIC
	AppSkeleton/app_skeleton.cpp
	AppSkeleton/app_skeleton.h
	AppSkeleton/vk_gfx.cpp
	AppSkeleton/vk_gfx.h
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

add_executable(test main.cpp)
target_link_libraries(test
	PRIVATE iAppSkeleton
)
