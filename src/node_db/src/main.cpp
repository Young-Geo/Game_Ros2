#include "work.h"
#include "rclcpp/rclcpp.hpp"


int main(int argc, const char **argv)
{
    rclcpp::init(argc, (char **)argv);
    /////
    ////
    gWORK->Init();
    gWORK->Start();//nei loop
    gWORK->Join();
    return 0;
}
