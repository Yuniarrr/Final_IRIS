#include "ros/ros.h"
#include "std_msgs/Int16.h"

// Timer
ros::Timer timer_1s;

class Tinggi
{
    private:
        std_msgs::Int16 tin;

        // Publisher
        ros::Publisher pub_tinggi;

    public:
        Tinggi(ros::NodeHandle *node_h)
        {
            pub_tinggi = node_h->advertise<std_msgs::Int16>("kirim_tinggi", 16);
        }

        void ini_timer(const ros::TimerEvent &tim_e)
        {
            tin.data = 70;
            pub_tinggi.publish(tin);
        }

        // void panggil_panjang(const std_msgs::Int16 &pan)
        // {
        //     ROS_INFO("Data dari PANJANG: [%d]", pan.data);
        // }

        // void panggil_lebar(const std_msgs::Int16 &leb)
        // {
        //     ROS_INFO("Data dari LEBAR: [%d]", leb.data);
        // }

        // void panggil_volume(const std_msgs::Int16 &vol)
        // {
        //     ROS_INFO("Data dari VOLUME: [%d]", vol.data);
        // }
};


int main(int argc, char** argv)
{
    // inisialisasi tinggi
    ros::init(argc, argv, "tinggi");

    ros::NodeHandle node_h;
    ros::MultiThreadedSpinner ini_spin;

    Tinggi tinggi_balok = Tinggi (&node_h);
    
    // timer
    timer_1s = node_h.createTimer(ros::Duration(1), &Tinggi::ini_timer, &tinggi_balok);

    std::cout << "DATA TINGGI DIKIRIM KE VOLUME" << std::endl;

    // Publisher
    // pub_tinggi = node_h.advertise<std_msgs::Int16>("kirim_tinggi", 16);

    // Subscriber
    // sub_1 = node_h.subscribe("topic_1", 16, &Tinggi::panggil_panjang, &tinggi_balok);
    // sub_2 = node_h.subscribe("topic_2", 16, &Tinggi::panggil_lebar, &tinggi_balok);
    // sub_4 = node_h.subscribe("topic_4", 16, &Tinggi::panggil_volume, &tinggi_balok);

    ini_spin.spin();
}
