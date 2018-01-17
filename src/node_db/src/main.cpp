#include "work.h"
#include "rclcpp/rclcpp.hpp"


int main(int argc, const char **argv)
{
    /*
    rclcpp::init(argc, (char **)argv);
    auto node = rclcpp::Node::make_shared("node_db");

    while (rclcpp::ok())
    {
        //sleep();
        rclcpp::spin_some(node);
    }*/
    /////
    ////
    gWORK->Init();
    gWORK->Start();//nei loop
    gWORK->Detach();
    return 0;
}
