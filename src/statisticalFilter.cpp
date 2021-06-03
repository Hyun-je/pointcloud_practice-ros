#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"

#include "pcl/point_cloud.h"
#include "pcl/point_types.h"
#include "pcl_conversions/pcl_conversions.h"

#include "pcl/filters/statistical_outlier_removal.h"


ros::Publisher pub;



void pointCloudCallback (const sensor_msgs::PointCloud2ConstPtr& pointCloud2) {

	pcl::PointCloud<pcl::PointXYZI>::Ptr pcl_cloud		(new pcl::PointCloud<pcl::PointXYZI>);
	pcl::PointCloud<pcl::PointXYZI>::Ptr pcl_cloud_filtered	(new pcl::PointCloud<pcl::PointXYZI>);

	// Convert ROS PointCloud2 to PCL PointCloud
	pcl::fromROSMsg (*pointCloud2, *pcl_cloud);

	// Filter PCL PointCloud
  	pcl::StatisticalOutlierRemoval<pcl::PointXYZI> sor;
  	sor.setInputCloud	(pcl_cloud);
  	sor.setMeanK		(50);
  	sor.setStddevMulThresh	(1.0);
  	sor.filter		(*pcl_cloud_filtered);

	// Make Filtered PointCloud2 Message
	sensor_msgs::PointCloud2 pointCloud2_out;
	pcl::toROSMsg (*pcl_cloud_filtered, pointCloud2_out);

	// Publish Message
	pub.publish (pointCloud2_out);

}


int main (int argc, char** argv) {

	ros::init (argc, argv, "voxelization");
	ros::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe<sensor_msgs::PointCloud2> ("/cloud_input", 1000, pointCloudCallback);
	pub = nh.advertise<sensor_msgs::PointCloud2> ("/cloud_output", 1000);

	ros::spin ();

}
