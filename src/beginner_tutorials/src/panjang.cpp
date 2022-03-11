#include "ros/ros.h"
#include "std_msgs/Int16.h"

// node_1 Panjang
// node_2 Lebar
// node_3 Tinggi
// node_4 Volume

// Timer
ros::Timer timer_1s;

class Panjang
{
    private:
        std_msgs::Int16 pan;

        // Publisher
        ros::Publisher pub_pajang;

    public:
        Panjang(ros::NodeHandle *node_h)
        {
            pub_pajang = node_h->advertise<std_msgs::Int16>("kirim_panjang", 16);
        }

        void ini_timer(const ros::TimerEvent &tim_e)
        {
            pan.data = 10;
            pub_pajang.publish(pan);
        }

        // void panggil_lebar(const std_msgs::Int16 &leb)
        // {
        //     ROS_INFO("Data dari LEBAR: [%d]", leb.data);
        // }

        // void panggil_tinggi(const std_msgs::Int16 &tin)
        // {
        //     ROS_INFO("Data dari TINGGI: [%d]", tin.data);
        // }

        // void panggil_volume(const std_msgs::Int16 &vol)
        // {
        //     ROS_INFO("Data dari VOLUME: [%d]", vol.data);
        // }
};

int main(int argc, char** argv)
{
    // inisialisasi panjang
    ros::init(argc, argv, "panjang");

    ros::NodeHandle node_h;
    ros::MultiThreadedSpinner ini_spin;

    // akses kelas
    Panjang panjang_balok = Panjang (&node_h);
    
    // timer
    timer_1s = node_h.createTimer(ros::Duration(1), &Panjang::ini_timer, &panjang_balok);

    std::cout << "DATA PANJANG DIKIRIM KE VOLUME" << std::endl;
    // Publisher
    // pub_pajang = node_h.advertise<std_msgs::Int16>("kirim_panjang", 16);

    // Subscriber
    // sub_2 = node_h.subscribe("topic_2", 16, &Panjang::panggil_lebar, &panjang_balok);
    // sub_3 = node_h.subscribe("topic_3", 16, &Panjang::panggil_tinggi, &panjang_balok);
    // sub_4 = node_h.subscribe("topic_4", 16, &Panjang::panggil_volume, &panjang_balok);

    ini_spin.spin();
}