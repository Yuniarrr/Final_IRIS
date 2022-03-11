#include "ros/ros.h"            //ROS
#include <stdio.h>
#include <iostream>
#include <sensor_msgs/Image.h> 
#include <sensor_msgs/image_encodings.h>    //Converting ROS to OpenCV images
#include <cv_bridge/cv_bridge.h>            //Converting ROS to OpenCV images
#include <image_transport/image_transport.h>//Publishing and subscribing to images in ROS
#include <opencv2/imgproc/imgproc.hpp>      //Converting ROS to OpenCV images
#include "opencv2/core/core.hpp"            //OpenCV Stitching
#include "opencv2/features2d/features2d.hpp"//OpenCV Stitching
#include "opencv2/highgui/highgui.hpp"      //OpenCV Stitching 
// #include "opencv2/nonfree/nonfree.hpp"      //OpenCV Stitching
#include "opencv2/calib3d/calib3d.hpp"      //OpenCV Stitching
#include "opencv2/imgproc/imgproc.hpp"      //OpenCV Stitching

using namespace cv;

// Create a container for the data.
sensor_msgs::Image cam1;
sensor_msgs::Image cam2;
sensor_msgs::Image output;
cv_bridge::CvImagePtr cv_ptr1;          //ROS and OpenCV suitable image for cam1
cv_bridge::CvImagePtr cv_ptr2;          //ROS and OpenCV suitable image for cam1
cv_bridge::CvImagePtr stitching_output; //ROS and OpenCV suitable output
Mat image1;
Mat image2; 

//Callback Funktionen
//If an image is published load it into the global variable
void cam1_cb (const sensor_msgs::ImageConstPtr& input)
{
  cam1=*input;
  ROS_INFO("Input from cam1");

  //Convert ROS image message to CvImage suitable for OpenCV
  try
  {
        cv_ptr1 = cv_bridge::toCvCopy(input, sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& e)
  {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
  }
}

void cam2_cb (const sensor_msgs::ImageConstPtr& input)
{
  cam2=*input;
  ROS_INFO("Input from cam2");
  //Convert ROS image message to CvImage suitable for OpenCV
  try
  {
        cv_ptr2 = cv_bridge::toCvCopy(input, sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& e)
  {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
  }
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "img_stitch");

  ros::NodeHandle n;

  //Create a publisher for the stitched images
  ros::Publisher image_pub = n.advertise<sensor_msgs::Image>("stitched", 1);

  //Publish-rate [Hz]
  ros::Rate loop_rate(1);

  //Create ROS subscribers for the input images
  ros::Subscriber sub1 = n.subscribe ("topicname", 1, cam1_cb);
  ros::Subscriber sub2 = n.subscribe ("topicname", 1, cam2_cb);

    int count = 0;
    while (ros::ok())
    {
        if ( cv_ptr1 && cv_ptr2 )
        {
            //Here is usually your stitching-routine. 
        // Error won't occur here:
        image1 = cv_ptr1->image;     //Load the cv_bridge image into an OpenCV Matrix

        //Convert cv::Mat stitched to ROS image


        image_pub.publish(stitching_output);

        // after you have processed the image your might want to release them
        // so your node does not process the same images multiple times
        // reset the ptrs and wait for the callbacks to fill them again
        cv_ptr1.reset();
        cv_ptr2.reset();
        }
        else
        {
        // nothing can be done here; we have to spin and wait for images to arrive
        }


        ros::spinOnce();

        loop_rate.sleep();
        ++count;
    }
}