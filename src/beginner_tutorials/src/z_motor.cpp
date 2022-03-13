#include <ros/ros.h>
#include <beginner_tutorials/Num.h>

using namespace std;  
// using namespace cv;

// Timer
ros::Timer timer_1s;

class cls_motor
{
    private:
        // std_msgs::Int16 vol;

        // Publisher
        ros::Publisher pub_motor;

        // Subscriber
        ros::Subscriber sub_pc;
        
        beginner_tutorials::Num vol;

    public:
        cls_motor(ros::NodeHandle *node_h)
        {
            // publisher
            pub_motor = node_h->advertise<beginner_tutorials::Num>("pergerakan", 16);
        }

        void ini_timer(const ros::TimerEvent &tim_e)
        {
            vol.hasil_motor = 0;
            pub_motor.publish(vol);
        }
};

void panggil_pc(const beginner_tutorials::Num::ConstPtr& pc)
        // void panggil_pc(const beginner_tutorials::Num& pc)
        {
            cout << "Nilai sudut: " << pc->hasil_pc_sudut << endl;
            cout << "Nilai x: " << pc->hasil_pc_kec_x << endl;
            cout << "Nilai y: " << pc->hasil_pc_kec_y << endl;
            ROS_INFO("Data sudut dari PC: [%d]", pc->hasil_pc_sudut);
            ROS_INFO("Data x dari PC: [%d]", pc->hasil_pc_kec_x);
            ROS_INFO("Data y dari PC: [%d]", pc->hasil_pc_kec_y);
        }
 
int main(int argc, char** argv)
{
    // inisialisasi cls_motor
    ros::init(argc, argv, "terima_data");

    ros::NodeHandle node_h;
    ros::MultiThreadedSpinner ini_spin;

    ros::Subscriber sub_pc;
    sub_pc = node_h.subscribe("kirim_pc", 16, panggil_pc);

    // ros::spin();
    ini_spin.spin();
}

