cmake_minimum_required(VERSION 3.8)
project(drone_core)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#DEPENDENCIES
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(ament_lint_auto REQUIRED)

#EXECUTABLE
add_executable(controller_node src/drone_controller.cpp)
ament_target_dependencies(controller_node rclcpp std_msgs geometry_msgs)

install(TARGETS controller_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  urdf
  DESTINATION share/${PROJECT_NAME}/
)

if(BUILD_TESTING)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
