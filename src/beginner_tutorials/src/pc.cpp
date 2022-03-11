#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "std_msgs/Int32.h"
#include "std_msgs/Int16.h"

using namespace std;
using namespace cv;

// Timer
ros::Timer timer_1s;

class cls_PC
{
    private:
        int theta, sudut, kec_x, kec_y;
        // int &theta, &sudut, &kec_x, &kec_y;
        std_msgs::Int16 hasil_theta;
        std_msgs::Int16 hasil_sudut;
        std_msgs::Int16 hasil_kec_x;
        std_msgs::Int16 hasil_kec_y;
        string y;

        // Publisher
        ros::Publisher pub_pc;

        // Subscriber
        ros::Subscriber sub_kamera; // Subscriber dari node 1

        // simpan data
        // int *v_theta, *v_sudut, *v_kec_x, *v_kec_y;


    public:
        cls_PC(ros::NodeHandle *node_h)
        {
            // publisher
            pub_pc = node_h->advertise<std_msgs::Int16>("kirim_pc", 16);

            // subscriber
            sub_kamera = node_h->subscribe("kirim_kamera", 16, &cls_PC::panggil_kamera, this);
        }

        void ini_timer(const ros::TimerEvent &tim_e)
        {
            hasil_theta.data = getTheta();
            hasil_sudut.data = getSudut();
            hasil_kec_x.data = get_kec_x();
            hasil_kec_y.data = get_kec_y();
            pub_pc.publish(hasil_theta);
            pub_pc.publish(hasil_sudut);
            pub_pc.publish(hasil_kec_x);
            pub_pc.publish(hasil_kec_y);
        }

        void panggil_kamera(const std_msgs::Int16 &x)
        {
            ROS_INFO("Data dari KAMERA: [%d]", x.data);
        }

        string yes()
        {
            cout << "Jalankan (y/n): ";
            cin >> y;
            return y;
        }

        void setTheta(int _theta)
        {
            theta = _theta;
        }

        void setSudut(int _sudut)
        {
            sudut = _sudut;
        }

        void set_kec_x(int _kec_x)
        {
            kec_x = _kec_x;
        }

        void set_kec_y(int _kec_y)
        {
            kec_y = _kec_y;
        }

        int getTheta()
        {
            return theta;
        }

        int getSudut()
        {
            return sudut;
        }

        int get_kec_x()
        {
            return kec_x;
        }

        int get_kec_y()
        {
            return kec_y;
        }

        bool clData()
        {
            int theta_set;
            int sudut_set;
            int kec_x_set;
            int kec_y_set;
            if (yes() == "n")
            {
                ros::shutdown();
            }
            else
            {                
                cout << "Masukkan theta: ";
                cin >> theta_set;
                setTheta(theta_set);

                cout << "Masukkan sudut: ";
                cin >> sudut_set;
                setTheta(sudut_set);
                if (0 <= sudut_set <= 179 || sudut_set == 180 || -179 <= sudut_set <= 0)
                {
                    setSudut(sudut_set);
                }
                else
                {
                    cout << "Sudut salah";
                }
                
                cout << "Masukkan kec x: ";
                cin >> kec_x_set;
                set_kec_x(kec_x_set);

                cout << "Masukkan kec y: ";
                cin >> kec_y_set;
                set_kec_y(kec_y_set);
            }

            // v_theta = &theta;
            // v_sudut = &sudut;
            // v_kec_x = &kec_x;
            // v_kec_y = &kec_y;
            return true;
        }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "ini_pc");

    ros::NodeHandle node_h;
    ros::MultiThreadedSpinner ini_spin;

    cls_PC ayok_pc = cls_PC (&node_h);
    
    while (ros::ok())
    {
        ayok_pc.clData();
    }

    // timer
    timer_1s = node_h.createTimer(ros::Duration(1), &cls_PC::ini_timer, &ayok_pc);

    ini_spin.spin();
}
