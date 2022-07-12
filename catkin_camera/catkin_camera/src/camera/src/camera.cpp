#include <ros/ros.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
using namespace std;
using namespace cv;


ros::Publisher pub1;
ros::Publisher pub2;

void imageCB(const sensor_msgs::ImageConstPtr msg){
     //获得图像话题，将图像转为opencv格式图片
     cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
     Mat dstImage = cv_ptr->image;
     //获得图像的宽度和高度
     double w = msg->width;
     double h = msg->height;
     //将图像剪裁为左右两个图像
     Rect area1(0, 0, w/2, h); 
     Rect area2(w/2, 0, w/2, h); 
     //裁减
     Mat left = dstImage(area1);  
     Mat right = dstImage(area2);
     
     //将剪裁后的图像转为ros的格式
     sensor_msgs::ImagePtr pubmsg1 = cv_bridge::CvImage(std_msgs::Header(), "bgr8", left).toImageMsg();
     sensor_msgs::ImagePtr pubmsg2 = cv_bridge::CvImage(std_msgs::Header(), "bgr8", right).toImageMsg();
     //发布图像
     pub1.publish(pubmsg1);
     pub2.publish(pubmsg2);
     imshow("left", left);
     imshow("right", right);
     waitKey(1);
}
int main(int argc, char **argv)
{
    //初始化节点
    ros::init(argc, argv, "camera");
    //创建句柄
    ros::NodeHandle n;
    //获取图像话题
    ros::Subscriber img_sub = n.subscribe("camera/rgb/image_raw",1,imageCB);
    pub1 = n.advertise<sensor_msgs::Image>("left",1000);
    pub2 = n.advertise<sensor_msgs::Image>("right",1000);
    ros::spin();
}
