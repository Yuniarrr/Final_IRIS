#include "ros/ros.h"
#include "std_msgs/Int16.h"

// Timer
ros::Timer timer_1s;

class Lebar
{
    private:
        std_msgs::Int16 leb;

        // Publisher
        ros::Publisher pub_lebar;

    public:
        Lebar(ros::NodeHandle *node_h)
        {
            pub_lebar = node_h->advertise<std_msgs::Int16>("kirim_lebar", 16);
        }

        void ini_timer(const ros::TimerEvent &tim_e)
        {
            leb.data = 50;
            pub_lebar.publish(leb);
        }

        void panggil_panjang(const std_msgs::Int16 &pan)
        {
            ROS_INFO("Data dari PANJANG: [%d]", pan.data);
        }

        void panggil_tinggi(const std_msgs::Int16 &tin)
        {
            ROS_INFO("Data dari TINGGI: [%d]", tin.data);
        }

        void panggil_volume(const std_msgs::Int16 &vol)
        {
            ROS_INFO("Data dari VOLUME: [%d]", vol.data);
        }
};


int main(int argc, char** argv)
{
    // inisialisasi lebar
    ros::init(argc, argv, "lebar");

    ros::NodeHandle node_h;
    ros::MultiThreadedSpinner ini_spin;

    Lebar lebar_balok = Lebar (&node_h);
    
    // timer
    timer_1s = node_h.createTimer(ros::Duration(1), &Lebar::ini_timer, &lebar_balok);

    std::cout << "DATA LEBAR DIKIRIM KE VOLUME" << std::endl;
    // Publisher
    // pub_lebar = node_h.advertise<std_msgs::Int16>("kirim_lebar", 16);

    // Subscriber
    // sub_1 = node_h.subscribe("topic_1", 16, &Lebar::panggil_panjang, &lebar_balok);
    // sub_3 = node_h.subscribe("topic_3", 16, &Lebar::panggil_tinggi, &lebar_balok);
    // sub_4 = node_h.subscribe("topic_4", 16, &Lebar::panggil_volume, &lebar_balok);

    ini_spin.spin();
}
