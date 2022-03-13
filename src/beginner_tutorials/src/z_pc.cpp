#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>
#include "std_msgs/Int16.h"
#include <beginner_tutorials/Num.h>

using namespace std;
using namespace cv;
 
// Timer
ros::Timer timer_1s;

class cls_PC
{
    private:
        // untuk contructor
        int sudut, kec_x, kec_y;

        // Subscriber
        ros::Subscriber sub_kamera;
        
        beginner_tutorials::Num ini_pc;

        float gerak_x;
        float gerak_y;

    public:
        cls_PC(ros::NodeHandle *node_h, int _sudut, int _kec_x, int _kec_y)
        {
            // subscriber
            sub_kamera = node_h->subscribe("kirim_kamera", 16, &cls_PC::panggil_kamera, this);

            sudut = _sudut;
            kec_x = _kec_x;
            kec_y = _kec_y;
        }

        void panggil_kamera(const beginner_tutorials::Num::ConstPtr& cam)
        {
            cout << "Posisi x: " << cam->hasil_kamera_x << endl;
            cout << "Posisi y: " << cam->hasil_kamera_y << endl;

            // mengambil posisi x, y yang dihasilkan kamera
            set_X_NOW(cam->hasil_kamera_x);
            set_Y_NOW(cam->hasil_kamera_y);
        }

        void setSudut(int _sudut)
        {
            sudut = sudut + _sudut;
        }

        void set_kec_x(int _kec_x)
        {
            kec_x = kec_x + _kec_x;
        }

        void set_kec_y(int _kec_y)
        {
            kec_y = kec_y + _kec_y;
        }

        void set_X_NOW(int _gerak_x)
        {
            gerak_x = _gerak_x;
        }

        void set_Y_NOW(int _gerak_y)
        {
            gerak_y = _gerak_y;
        }

        int getSudut()
        {
            if (sudut >= 0 && sudut < 180)
            {
                sudut = sudut;
            }
            else if (sudut < 0 && sudut > -180)
            {
                sudut = -sudut;
            }
            else if (sudut >= 180)
            {
                while (sudut >= 180)
                {
                    sudut = 180 - sudut;
                }
            }            
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

        float get_X_NOW()
        {
            return gerak_x;
        }

        float get_Y_NOW()
        {
            return gerak_y;
        }
};

void panggil_kamera(const beginner_tutorials::Num::ConstPtr& cam)
        {
            ROS_INFO("Posisi x: [%f]", cam->hasil_kamera_x);
            ROS_INFO("Posisi y: [%f]", cam->hasil_kamera_y);
        }

int main(int argc, char** argv)
{
    ros::init(argc, argv, "ini_pc");

    ros::NodeHandle node_h;
    ros::MultiThreadedSpinner ini_spin;

    ros::Publisher pub_pc;
    pub_pc = node_h.advertise<beginner_tutorials::Num>("kirim_pc", 16);

    ros::Rate loop_rate(1);
    
    // nilai awal
    cls_PC ayok_pc = cls_PC (&node_h, 0, 0, 0);
    
    while (ros::ok())
    {
        beginner_tutorials::Num ini_pc;

        string yes;
        int ini_sudut;

        cout << "Jalan(y/n): ";
        cin >> yes;

        if (yes == "y")
        {
            ayok_pc.setSudut(20);
            ayok_pc.set_kec_x(10);
            ayok_pc.set_kec_y(10);

            // jika x lebih besar drpd y (digambar)
            if (ayok_pc.get_X_NOW() <= ayok_pc.get_Y_NOW())
            {
                while (ayok_pc.get_kec_y() <= ayok_pc.get_Y_NOW())
                {
                    ayok_pc.getSudut();
                    ayok_pc.get_Y_NOW();
                }
                while (ayok_pc.get_kec_x() <= ayok_pc.get_X_NOW())
                {
                    ayok_pc.get_kec_x();
                }
            }

            // jika y lebih besar dr x (di gambar)
            else if (ayok_pc.get_X_NOW() >= ayok_pc.get_Y_NOW())
            {
                while (ayok_pc.get_kec_y() <= ayok_pc.get_Y_NOW())
                {
                    ayok_pc.get_Y_NOW();
                }
                while (ayok_pc.get_kec_x() <= ayok_pc.get_X_NOW())
                {
                    ayok_pc.get_kec_x();
                    ayok_pc.getSudut();
                }
            }

            // jika x = y
            else
            {
                while (ayok_pc.get_kec_y() <= ayok_pc.get_Y_NOW())
                {
                    ayok_pc.get_Y_NOW();
                    ayok_pc.get_kec_x();
                    ayok_pc.getSudut();
                }
            }
            
            cout << "Nilai sudut: " << ayok_pc.getSudut() << endl;
            cout << "Nilai x: " << ayok_pc.get_kec_x() << endl;
            cout << "Nilai y: " << ayok_pc.get_kec_y() << endl;
            cout << "di titik x: " << ayok_pc.get_X_NOW() << endl;
            cout << "di titik y: " << ayok_pc.get_Y_NOW() << endl;   
        } 
        else
        {
            ros::shutdown();
        }

        loop_rate.sleep();
        ros::spinOnce();

        ini_pc.hasil_pc_sudut = ayok_pc.getSudut();
        ini_pc.hasil_pc_kec_x = ayok_pc.get_kec_x();
        ini_pc.hasil_pc_kec_y = ayok_pc.get_kec_y();
        pub_pc.publish(ini_pc);
    }

    ros::Subscriber sub_kamera = node_h.subscribe("kirim_kamera", 16, panggil_kamera);
    
    ini_spin.spin();
}