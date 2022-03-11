#include "ros/ros.h"
#include "std_msgs/Int16.h"

// Timer
ros::Timer timer_1s;

class Volume
{
    private:
        std_msgs::Int16 vol;

        // Publisher
        ros::Publisher pub_volume;

        // Subscriber
        ros::Subscriber sub_panjang; // Subscriber dari node 1
        ros::Subscriber sub_lebar; // Subscriber dari node 2
        ros::Subscriber sub_tinggi; // Subscriber dari node 3
        ros::Subscriber sub_volume; // Subscriber dari node 4

        // simpan data
        const std_msgs::Int16 *panjang;
        const std_msgs::Int16 *lebar;
        const std_msgs::Int16 *tinggi;

    public:
        Volume(ros::NodeHandle *node_h)
        {
            // publisher
            pub_volume = node_h->advertise<std_msgs::Int16>("hasil_volume", 16);

            // subscriber
            sub_panjang = node_h->subscribe("kirim_panjang", 16, &Volume::panggil_panjang, this);
            sub_lebar = node_h->subscribe("kirim_lebar", 16, &Volume::panggil_lebar, this);
            sub_tinggi = node_h->subscribe("kirim_tinggi", 16, &Volume::panggil_tinggi, this);
            sub_volume = node_h->subscribe("hasil_volume", 16, &Volume::panggil_volume, this);
        }

        void ini_timer(const ros::TimerEvent &tim_e)
        {
            vol.data = 0;
            pub_volume.publish(vol);
        }

        void panggil_panjang(const std_msgs::Int16 &pan)
        {
            panjang = &pan;
            ROS_INFO("Data dari PANJANG: [%d]", pan.data);
        }

        void panggil_lebar(const std_msgs::Int16 &leb)
        {
            lebar = &leb;
            ROS_INFO("Data dari LEBAR: [%d]", leb.data);
        }

        void panggil_tinggi(const std_msgs::Int16 &tin)
        {
            tinggi = &tin;
            ROS_INFO("Data dari TINGGI: [%d]", tin.data);
        }

        void panggil_volume(const std_msgs::Int16 &vol)
        {
            ROS_INFO("Data dari VOLUME: [%d]", (panjang->data)*(lebar->data)*(tinggi->data));
        }
};


int main(int argc, char** argv)
{
    // inisialisasi volume
    ros::init(argc, argv, "volume");

    ros::NodeHandle node_h;
    ros::MultiThreadedSpinner ini_spin;

    Volume volume_balok = Volume (&node_h);
    
    // timer
    timer_1s = node_h.createTimer(ros::Duration(1), &Volume::ini_timer, &volume_balok);

    // Publisher
    // pub_volume = node_h.advertise<std_msgs::Int16>("hasil_volume", 16);

    // Subscriber
    // sub_panjang = node_h.subscribe("kirim_panjang", 16, &Volume::panggil_panjang, &volume_balok);
    // sub_lebar = node_h.subscribe("kirim_lebar", 16, &Volume::panggil_lebar, &volume_balok);
    // sub_tinggi = node_h.subscribe("kirim_tinggi", 16, &Volume::panggil_tinggi, &volume_balok);
    // sub_volume = node_h.subscribe("hasil_volume", 16, &Volume::panggil_volume, &volume_balok);

    ini_spin.spin();
}
