#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"

#include "pcl/point_cloud.h"
#include "pcl/point_types.h"
#include "pcl_conversions/pcl_conversions.h"

#include <pcl/kdtree/kdtree.h>
#include <pcl/segmentation/extract_clusters.h>


int color_index = 0;
pcl::PointXYZRGB color_list[6] =
{
	{255, 0 , 0},
	{255, 255, 0},
	{0, 255, 255},
	{0, 255, 0},
	{0, 0, 255},
	{255, 0, 255}
};

ros::Publisher pub;



void pointCloudCallback (const sensor_msgs::PointCloud2ConstPtr& pointCloud2) {

	pcl::PointCloud<pcl::PointXYZI>::Ptr pcl_cloud			(new pcl::PointCloud<pcl::PointXYZI>);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcl_cloud_clustered	(new pcl::PointCloud<pcl::PointXYZRGB>);

	// Convert ROS PointCloud2 to PCL PointCloud
	pcl::fromROSMsg (*pointCloud2, *pcl_cloud);

	// Create KdTree
	pcl::search::KdTree<pcl::PointXYZI>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZI>);
 	tree->setInputCloud (pcl_cloud);

	// Clustering PCL PointCloud
	std::vector<pcl::PointIndices> cluster_indices;
 	pcl::EuclideanClusterExtraction<pcl::PointXYZI> ec;
	ec.setInputCloud	(pcl_cloud);
	ec.setClusterTolerance	(1.0);
	ec.setMinClusterSize	(10);
	ec.setMaxClusterSize	(20000);
	ec.setSearchMethod	(tree);
	ec.extract		(cluster_indices);

	for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin(); it != cluster_indices.end (); ++it) {

		for(std::vector<int>::const_iterator pit = it->indices.begin(); pit != it->indices.end(); ++pit) {

			pcl::PointXYZI	point = pcl_cloud->points[*pit];

			pcl::PointXYZRGB point_new = color_list[color_index % 6];
			point_new.x = point.x;
			point_new.y = point.y;
			point_new.z = point.z;

			pcl_cloud_clustered->points.push_back (point_new);

		}

		color_index++;
	}

	// Set Clustered PointCloud Properties
	pcl_cloud_clustered->width	= pcl_cloud_clustered->points.size();
	pcl_cloud_clustered->height	= 1;
	pcl_cloud_clustered->is_dense	= true;

	// Make Clustered PointCloud2 Message
	sensor_msgs::PointCloud2 pointCloud2_out;
	pcl::toROSMsg (*pcl_cloud_clustered, pointCloud2_out);
	pointCloud2_out.header.frame_id = "velodyne";

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
