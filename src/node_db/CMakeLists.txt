cmake_minimum_required(VERSION 3.5)
project(node_db)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(SYSTEM ../Ybasis)
include_directories(src ${catkin_INCLUDE_DIRS})

SET(SOURCE_FILES
     src/work.cpp
     src/DBYS.cpp
     src/DBconfig.cpp
     src/ocicursor.cpp
     src/ocidatabase.cpp
)
SET(BASIS
 ../Ybasis/Ybasis.cpp
 ../Ybasis/Ywork.cpp
 ../Ybasis/Ylog.cpp
 ../Ybasis/Ytime.cpp
 ../Ybasis/Yconfig.cpp
 ../Ybasis/YS.cpp
 ../Ybasis/Ysocket.cpp
 ../Ybasis/Ymsgtool.cpp
 ../Ybasis/Ypackage.cpp
 ../Ybasis/YSocketClient.cpp
 ../Ybasis/Yuser.cpp
)

#add_executable(node_db src/main.cpp src/work.cpp src/DBYS.cpp src/DBconfig.cpp src/ocicursor.cpp src/ocidatabase.cpp)
add_executable(node_db src/main.cpp ${SOURCE_FILES} ${BASIS})
ament_target_dependencies(node_db rclcpp std_msgs)
target_link_libraries(node_db ${catkin_LIBRARIES})
target_link_libraries(node_db mysqlclient event)

install(TARGETS
  node_db
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
