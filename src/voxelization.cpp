#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"

#include "pcl/point_cloud.h"
#include "pcl/point_types.h"
#include "pcl_conversions/pcl_conversions.h"

#include "pcl/filters/voxel_grid.h"


ros::Publisher pub;



void pointCloudCallback (const sensor_msgs::PointCloud2ConstPtr& pointCloud2) {

	pcl::PointCloud<pcl::PointXYZI>::Ptr pcl_cloud		(new pcl::PointCloud<pcl::PointXYZI>);
	pcl::PointCloud<pcl::PointXYZI>::Ptr pcl_cloud_filtered	(new pcl::PointCloud<pcl::PointXYZI>);

	// Convert ROS PointCloud2 to PCL PointCloud
	pcl::fromROSMsg (*pointCloud2, *pcl_cloud);

	// Voxelize PCL PointCloud
	pcl::VoxelGrid<pcl::PointXYZI> sor;
	sor.setInputCloud	(pcl_cloud);
	sor.setLeafSize		(0.5, 0.5, 0.5);
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

	ros::Subscriber sub = nh.subscribe<sensor_msgs::PointCloud2> ("/velodyne_points", 1000, pointCloudCallback);
	pub = nh.advertise<sensor_msgs::PointCloud2> ("/velodyne_points_voxelized", 1000);

	ros::spin ();

}
