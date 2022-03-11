#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "std_msgs/Int16.h"
#include "std_msgs/Float32.h"

using namespace cv;
using namespace std;

// Timer
ros::Timer timer_1s;

class Kamera
{
    private:
        std_msgs::Float32 cam_x;
        std_msgs::Float32 cam_y;
        std_msgs::Float32 koor_x;
        
        // Publisher
        ros::Publisher pub_cam;

        // gambar
        Mat image, img_resized, img_hsv, tresh;
        
        float *tik_x;
        float *tik_y;

        float *sim_tik_x;
        float *sim_tik_y;

    public:
        Kamera(ros::NodeHandle *node_h)
        {
            pub_cam = node_h->advertise<std_msgs::Int16>("kirim_kamera", 16);
        }

        // void ini_timer(const ros::TimerEvent &tim_e)
        // {
        //     cam_x.data = tik_x;
        //     cam_y.data = tik_y;
        //     pub_cam.publish(cam_x);
        //     pub_cam.publish(cam_y);
        // }

        void clbk_kamera(Mat image)
        {

            int L_H = 0;
            int U_H = 77;
            int L_S = 73;
            int U_S = 247;
            int L_V = 83;
            int U_V = 228;
                
            while (true) {
                resize(image, img_resized, Size(800, 1200), 0.6, 0.4); // bingung size
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

                    if (radius > 15 && radius < 50)
                    {
                        circle(img_resized, center, radius, Scalar(255, 0, 0), 3);
                        tik_x = &center.y;
                        tik_y = &center.x;
                        cam_x.data = center.x;
                        cam_y.data = center.y;
                        pub_cam.publish(cam_x);
                        pub_cam.publish(cam_y);
                    }
                }
            }
        }

        // float get_x()
        // {
        //     return sim_tik_x = &tik_x;
        // }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "ini_kamera");
    ros::NodeHandle node_h;
    image_transport::ImageTransport it(node_h);

    Mat image, img_resized, img_hsv, tresh;

    image_transport::Publisher pub = it.advertise("gambar_kamera", 1);

    Kamera ayok_kamera = Kamera (&node_h);

    image = cv::imread("/home/niar14/catkin_ws/src/beginner_tutorials/src/gambar/gam1.jpg", 1);

    ayok_kamera.clbk_kamera(image);

    cv::waitKey(30);

    // sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", ayok_kamera).toImageMsg();
    // timer_1s = node_h.createTimer(ros::Duration(1), &Kamera::ini_timer, &ayok_kamera);


    // ros::Rate loop_rate(5);
    // while (node_h.ok()) {
    //     pub.publish(msg);
    //     ros::spinOnce();
    //     loop_rate.sleep();
    // }
}