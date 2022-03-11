#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "std_msgs/Int16.h"

using namespace std;
using namespace cv;

// Timer
ros::Timer timer_1s;

class cls_PC
{
    private:
        std_msgs::Int16 vol;

        // Publisher
        ros::Publisher pub_motor;

        // Subscriber
        ros::Subscriber sub_kamera;
        ros::Subscriber sub_pc; 

        // simpan data
        const std_msgs::Int16 *panjang;

        // gambar
        cv::Mat image, img_resized, img_hsv, tresh;

    public:
        cls_PC(ros::NodeHandle *node_h)
        {
            // publisher
            pub_motor = node_h->advertise<std_msgs::Int16>("pergerakan", 16);

            sub_pc = node_h->subscribe("hasil_pc", 16, &cls_PC::panggil_pc, this);
            sub_kamera = node_h->subscribe("hasil_pc", 16, &cls_PC::panggil_kamera, this);
        }

        void ini_timer(const ros::TimerEvent &tim_e)
        {
            vol.data = 0;
            pub_motor.publish(vol);
        }

        void panggil_pc(const std_msgs::Int16 &data_pc)
        {
            ROS_INFO("Data dari PC: [%d]", data_pc.data);
            ROS_INFO("Data dari PC: [%d]", data_pc.data);
            ROS_INFO("Data dari PC: [%d]", data_pc.data);
            ROS_INFO("Data dari PC: [%d]", data_pc.data);
        }

        void panggil_kamera(const std_msgs::Int16 &data_pc)
        {
            ROS_INFO("Data dari PC: [%d]", data_pc.data);
            ROS_INFO("Data dari PC: [%d]", data_pc.data);
        }
};


int main(int argc, char** argv)
{
    // inisialisasi cls_PC
    ros::init(argc, argv, "cls_PC");

    ros::NodeHandle node_h;
    ros::MultiThreadedSpinner ini_spin;

    cls_PC cls_PC_balok = cls_PC (&node_h);
    
    // timer
    // timer_1s = node_h.createTimer(ros::Duration(1), &cls_PC::ini_timer, &cls_PC_balok);

    ini_spin.spin();
}
