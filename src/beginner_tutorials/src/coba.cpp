#include "ros/ros.h"
#include "std_msgs/Int16.h"

// Publisher
ros::Publisher pub_1;

// Subscriber
ros::Subscriber sub_2;
ros::Subscriber sub_3;

ros::Timer tim_50_hz;

void clbck_tim_50_hz(const ros::TimerEvent &event)
{
    std_msgs::Int16 msg_1;
    msg_1.data = 10;
    pub_1.publish(msg_1);
}

void clbck_sub_2(const std_msgs::Int16 &msg)
{
    ROS_INFO("Data dari node 2: [%d]", msg.data);
}

void clbck_sub_3(const std_msgs::Int16 &msg)
{
    ROS_INFO("Data dari node 3: [%d]", msg.data);
}

int main(int argc, char** argv)
{
    // inisialisasi
    ros::init(argc, argv, "node_1");

    ros::NodeHandle NH;
    ros::MultiThreadedSpinner MTS;

    // timer
    tim_50_hz = NH.createTimer(ros::Duration(0.02), clbck_tim_50_hz);

    // publisher
    pub_1 = NH.advertise<std_msgs::Int16>("topic_1", 16);

    // subscriber
    sub_2 = NH.subscribe("topic_2", 16,  clbck_sub_2);
    sub_3 = NH.subscribe("topic_3", 16, clbck_sub_3);

    MTS.spin();
}