#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// using namespace cv;
namespace enc = sensor_msgs::image_encodings;

void imageCb(const sensor_msgs::ImageConstPtr &msg)
{
  cv::Mat img;
  cv_bridge::CvImagePtr cv_ptr;
  try
  {
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
  }
  catch(cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }

  if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
  {
    circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255, 0, 0));
  }

  cv::imshow("Image Window", img);
  cv::waitKey(3);
}

// void show_image(const sensor_msgs::ImageConstPtr &msg)
// {
//   cv::Mat img;
//   cv::imshow("Image Window", img);  
//   cv::waitKey(3);
// }

// void imageCb(const sensor_msgs::ImageConstPtr &msg)
// {
//   ros::Publisher img_pub;
//   cv_bridge::CvImagePtr cv_ptr;
//   try
//   {
//     cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
//   }
//   catch(cv_bridge::Exception& e)
//   {
//     ROS_ERROR("cv_bridge exception: %s", e.what());
//     return;
//   }

//   // Draw an example circle on the video stream
//   if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
//   {
//     circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255, 0, 0));
//   }
            
//   // Update GUI window
//   imshow(OPEN_WINDOW, cv_ptr->image);
//   cv::waitKey(3);

//   // output modified video stream
//   img_pub.publish(cv_ptr->toImageMsg());
// }

int main(int argc, char** argv)
{
  ros::init(argc, argv, "cam_angel");
  cv::Mat img;
  cv::imshow("Image Window", img);
  cv::waitKey(3);

  ros::Subscriber sub_kamera;
  // ros::Publisher pub_kamera;

  ros::MultiThreadedSpinner putar;
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);

  image_transport::Publisher pub_kamera = it.advertise("node_1", 1, imageCb);

  cv::namedWindow("image window", 1);

  while (true)
  {
    putar.spin();
  }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// using namespace cv;

// int main(int argc, char** argv)
// {
//     ros::init(argc, argv, "gam_sulit");
//     ros::NodeHandle nh;
//     image_transport::ImageTransport it(nh);
//     image_transport::Publisher pub_1 = it.advertise("gambar/gam1", 1);

//     Mat image = imread(argv[1], COLOR_BGR2HSV);
//     waitKey(30);

//     sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();

//     ros::Rate loop_rate(5);
//     while (nh.ok())
//     {
//         pub_1.publish(msg);
//         ros::spinOnce();
//         loop_rate.sleep();
//     }
    
// }
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// static const std::string OPEN_WINDOW = "Image window";
// using namespace cv;

// class ImageConverter
// {
//     ros::NodeHandle nh_;
//     image_transport::ImageTransport it_;
//     image_transport::Subscriber img_sub_;
//     image_transport::Publisher img_pub_;
//     Mat img, img_resized, img_hsv;

//     public:
//         ImageConverter()
//             :it_(nh_)
//         {
//             // Subscrive to input video feed and publish output video feed
//             img_sub_ = it_.subscribe("gambar/gam1", 1, &ImageConverter::imageCb, this);

//             // img_pub_ = it_.advertise("gambar/gam1", 1);
//             img = imread("gambar/gam1.jpg");
//             img_pub_ = img.advertise("pub_gambar", 16);
        
//             namedWindow(OPEN_WINDOW);
//         }

//         ~ImageConverter()
//         {
//             destroyWindow(OPEN_WINDOW);
//         }

//         void imageCb(const sensor_msgs::ImageConstPtr &msg)
//         {
//             cv_bridge::CvImagePtr cv_ptr;
//             try
//             {
//                 cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
//             }
//             catch(cv_bridge::Exception& e)
//             {
//                 ROS_ERROR("cv_bridge exception: %s", e.what());
//                 return;
//             }

//             // Draw an example circle on the video stream
//             if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
//             {
//                 circle(cv_ptr->image, Point(50, 50), 10, CV_RGB(255, 0, 0));
//             }
            
//             // Update GUI window
//             imshow(OPEN_WINDOW, cv_ptr->image);
//             waitKey(3);

//             // output modified video stream
//             img_pub_.publish(cv_ptr->toImageMsg());
//         }
// };

// // int main(int argc, char** argv)
// // {
// //     ros::init(argc, argv, "kamera");
// //     ImageConverter ic;
// //     ROS_INFO("kamera");
// //     ros::spin();
// //     return 0;
// // }
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// #include <ros/ros.h>
// #include <image_transport/image_transport.h>
// #include <opencv2/highgui/highgui.hpp>
// #include <cv_bridge/cv_bridge.h>
// #include <sensor_msgs/image_encodings.h>
// #include <iostream>

// using namespace cv;

// int main(int argc, char** argv)
// {
//   ros::init(argc, argv, "image_publisher");
//   ros::NodeHandle nh;

//     image_transport::ImageTransport it(nh);
//     image_transport::Publisher pub = it.advertise("node_1", 1);
//     Mat image;
//     Mat img_resized, img_hsv;

//     // string encoding(image, size(), 2, 2);
//     image = imread("gambar/gam1.jpg");
//     // cv::resize(image, img_resized, Size(), 2, 2);
//     // cv::cvtColor(img_resized, img_hsv, COLOR_BGR2HSV);
//     // image_color(COLOR_BGR2HSV);

//         int L_H = 0;
//         int U_H = 77;
//         int L_S = 73;
//         int U_S = 247;
//         int L_V = 83;
//         int U_V = 228;
        
//     // inRange(image, Scalar(L_H, L_S, L_V), Scalar(U_H, U_S, U_V), img_hsv);
//     // // waitKey(30);
//     sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
  
//     ros::Rate loop_rate(5);
//     while (nh.ok()) {
//       pub.publish(msg);
//       ros::spinOnce();
//       loop_rate.sleep();
//     }
  
//   imshow("WINDOW", image);
//   ROS_INFO("test gambar");
//   namedWindow("WINDOW", 1);
//   waitKey(0);
//   return 0;
// }

