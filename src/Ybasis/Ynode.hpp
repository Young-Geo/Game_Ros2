/*
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 *          QQ: 473763733
 *       Email: anxan524@126.com
 */
#ifndef __YNODE_H__
#define __YNODE_H__
#include "Ybasis.h"
#include <rclcpp/rclcpp.hpp>

struct YnodeStruct
{
    std::shared_ptr<rclcpp::Node> nodePtr;
    std::shared_ptr<rclcpp::WallRate> ratePtr;
    //std::list<std::shared_ptr<rclcpp::Publisher>>  pubList;
    //std::list<std::shared_ptr<rclcpp::Subscription>> subList;
    //template <typename T>
    //std::map<Ystring, std::shared_ptr<rclcpp::Publisher<T>>> pubMap;
    std::map<Ystring, std::shared_ptr<void>> pubMap;
    //template <typename T>
    std::map<Ystring, std::shared_ptr<void>> subMap;
    //pubT pubMap;
    //subT subMap;
    YnodeStruct()
    {
        nodePtr.reset();
        //pubList.clear();
        //subList.clear();
        pubMap.clear();
        subMap.clear();
    }
};

class Ynode
{
public:
    Ynode(){}

    bool    Init(Ystring nodeName, Yint hz)
    {
        if (nodeName.size() <= 0)
            return false;
        if (nodeName.size() <= 0|| "" == nodeName)
            return false;
        if (!(m_node.nodePtr = rclcpp::Node::make_shared(nodeName.c_str()))) {
            return false;
        }//need change

        m_node.ratePtr = rclcpp::WallRate::make_shared(hz);
        return true;
    }
    template <typename T>
    bool    AddPub(Ystring pubName, rmw_qos_profile_t rmw = rmw_qos_profile_default)
    {
        if (!m_node.nodePtr)
            return false;
        if (pubName.size() <= 0|| "" == pubName)
            return false;
        if (m_node.pubMap.find(pubName) == m_node.pubMap.end()) {
            return false;
        }
        std::shared_ptr<rclcpp::Publisher<T>> pubPtr = m_node.nodePtr->create_publisher<T>(pubName.c_str(), rmw);
        if (!pubPtr)
            return false;

        m_node.pubMap[pubName] = pubPtr;
        return true;
    }
    template <typename T>
    bool    AddSub(Ystring subName, auto func_Sub, rmw_qos_profile_t rmw = rmw_qos_profile_default)
    {
        if (!m_node.nodePtr)
            return false;
        if (subName.size() <= 0|| "" == subName)
            return false;
        if (m_node.subMap.find(subName) == m_node.subMap.end()) {
            return false;
        }
        std::shared_ptr<rclcpp::Subscription<T>> subPtr = m_node.nodePtr->create_subscription<T>(subName.c_str(), func_Sub, rmw);
        if (!subPtr)
            return false;

        m_node.subMap[subName] = subPtr;
        return true;
    }

    template <typename T>
    bool    Publish(Ystring pubName, T &t, rmw_qos_profile_t rmw = rmw_qos_profile_default)
    {
        if (m_node.pubMap.find(pubName) == m_node.pubMap.end()) {
            if (!AddPub<T>(pubName, rmw))
                return false;
        }

        ((rclcpp::Publisher<T> *)m_node.pubMap[pubName].get())->publish(t);
        return true;
    }

    bool    SpinOnce()
    {
        if (!m_node.nodePtr)
            return false;

        rclcpp::spin_some(m_node.nodePtr);
        return m_node.ratePtr->sleep();
    }

    bool    Spin()
    {
        if (!m_node.nodePtr)
            return false;

        rclcpp::spin(m_node.nodePtr);
        return true;
    }
    std::shared_ptr<rclcpp::Node> GetNode()
    {
        return m_node.nodePtr;
    }
    template <typename T>
    bool        Publish(Ystring pubName, T &t)
    {
        if (m_node.pubMap.find(pubName) == m_node.pubMap.end()) {
            return false;
        }
        ((rclcpp::Publisher<T> *)m_node.pubMap[pubName].get())->publish(t);
        return true;
    }
private:
    YnodeStruct m_node;
};

#endif // __YNODE_H__
