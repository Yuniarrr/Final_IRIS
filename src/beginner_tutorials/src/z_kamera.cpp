#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <beginner_tutorials/Num.h>

using namespace cv;
using namespace std; 

// Timer
ros::Timer timer_1s;

class Kamera
{
    private:        
        // Publisher
        ros::Publisher pub_cam;

        ros::Subscriber sub_cam;

        // gambar
        Mat image, img_resized, img_hsv, tresh;

        beginner_tutorials::Num send_cam;
        beginner_tutorials::Num ini_kamera;


        // untuk koordinat
        float x;
        float y;
 
    public:
    
        void ini_timer(const ros::TimerEvent &tim_e)
        {
            send_cam.hasil_kamera_x = get_X();
            send_cam.hasil_kamera_y = get_Y();
            pub_cam.publish(send_cam);
        }

        void clbk_kamera(Mat image)
        {
            int L_H = 25;
            int U_H = 179;
            int L_S = 81;
            int U_S = 255;
            int L_V = 29;
            int U_V = 255;
                
            while (true) {
                resize(image, img_resized, Size(1200, 800));
                cvtColor(img_resized, img_hsv, COLOR_BGR2HSV);
                
                inRange(img_hsv, Scalar(L_H, L_S, L_V), Scalar(U_H, U_S, U_V), tresh);

                vector<vector<Point>> contours;
                findContours(tresh, contours, RETR_TREE, CHAIN_APPROX_NONE);

                for (int i = 0; i < contours.size(); i++)
                {
                    vector<Point>contours_baru;
                    Point2f center;
                    float radius;
                    contours_baru = contours[i];
                    minEnclosingCircle(contours_baru, center, radius);

                    // cari koordinat x dan y
                    if (radius > 50 && radius < 200)
                    {
                        circle(img_resized, center, radius, Scalar(255, 0, 0), 3);

                        set_X(center.y);
                        set_Y(center.x);
                        // publish data x dan y
                        // send_cam.hasil_kamera_x = center.y;
                        // send_cam.hasil_kamera_y = center.x;
                        // pub_cam.publish(send_cam);
                        cout << "Nilai x: " << get_X() << endl;
                        cout << "Nilai y: " << get_Y() << endl;

                        ini_kamera.hasil_kamera_x = get_X();
                        ini_kamera.hasil_kamera_y = get_Y();
                    }
                }
            }
        }

        void set_X(int _x)
        {
            x = _x;
        }

        void set_Y(int _y)
        {
            y = _y;
        }

        float get_X()
        {
            return x;
        }

        float get_Y()
        {
            return y;
        }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "ini_kamera");
    ros::NodeHandle node_h;
    ros::MultiThreadedSpinner ini_spin;
    ros::Publisher pub_cam;

    image_transport::ImageTransport it(node_h);
    image_transport::Publisher pub = it.advertise("gambar_kamera", 100);

    Kamera ayok_kamera;

    beginner_tutorials::Num ini_kamera;
    timer_1s = node_h.createTimer(ros::Duration(1), &Kamera::ini_timer, &ayok_kamera);

    Mat image;
    image = cv::imread("/home/niar14/catkin_ws/src/beginner_tutorials/src/gambar/gam1.jpg", 1);

    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        string yes;

        cout << "Jalakan(y/n): ";
        cin >> yes;

        if (yes == "y")
        {
            ayok_kamera.clbk_kamera(image);
        }
        else
        {
            ros::shutdown();
        }

        pub_cam.publish(ini_kamera);

        loop_rate.sleep();
        ros::spinOnce();
    }

    ini_spin.spin();
}