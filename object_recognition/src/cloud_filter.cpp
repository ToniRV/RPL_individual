/*
 * cloud_filter.cpp
 *
 *  Created on: Nov 24, 2015
 *      Author: marius
 */

#include <cloud_filter.h>

cloud_filter::cloud_filter(filter_bag fil_bag)
{
	filter_param = fil_bag;
}

void cloud_filter::resolution_filter (pcl::PointCloud<pcl::PointXYZ>::Ptr a_cloud,
									  pcl::PointCloud<pcl::PointXYZ>::Ptr a_cloud_filtered)
{
  std::cerr << "\nPointCloud before res_filtering: " << a_cloud->width * a_cloud->height
       << " data points (" << pcl::getFieldsList (*a_cloud) << ").\n";

  // Create the filtering object
  pcl::VoxelGrid<pcl::PointXYZ> sor;
  sor.setInputCloud (a_cloud);
  sor.setLeafSize (filter_param.resolution.leafsize_x,
		  	  	   filter_param.resolution.leafsize_y,
				   filter_param.resolution.leafsize_z);
  sor.filter (*a_cloud_filtered);

  std::cerr << "PointCloud after res_filtering: " << a_cloud_filtered->width * a_cloud_filtered->height
       << " data points (" << pcl::getFieldsList (*a_cloud_filtered) << ").\n";
}

void cloud_filter::passthrough_filter (pcl::PointCloud<pcl::PointXYZ>::Ptr a_cloud,
									   pcl::PointCloud<pcl::PointXYZ>::Ptr a_cloud_filtered)
{
 // Create the filtering object
 pcl::PassThrough<pcl::PointXYZ> pass;
 pass.setInputCloud (a_cloud);
 pass.setFilterFieldName ("z");
 pass.setFilterLimits (filter_param.passthrough.min_filterlimit_z,
		 	 	 	   filter_param.passthrough.max_filterlimit_z);
 pass.filter (*a_cloud_filtered);

 std::cerr << "PointCloud after passthrough_filtering: " << a_cloud_filtered->width * a_cloud_filtered->height
       << " data points (" << pcl::getFieldsList (*a_cloud_filtered) << ").\n";
}

void cloud_filter::statistical_outlier_removal_filter (pcl::PointCloud<pcl::PointXYZ>::Ptr a_cloud,
		 	 	 	 	 	 	 	 	 	 	 	   pcl::PointCloud<pcl::PointXYZ>::Ptr a_cloud_filtered)
{
 // Create the filtering object
 pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
 sor.setInputCloud (a_cloud);
 // Number of neighbors to analyze for each point is set to meank
 sor.setMeanK (filter_param.outlier.meank);
 // All points who have a distance larger than stddev_mul_thresh *standard deviation of the mean distance
 // to the query point will be marked as outliers and removed
 sor.setStddevMulThresh (filter_param.outlier.stddev_mul_thresh);
 sor.filter (*a_cloud_filtered);

 std::cerr << "PointCloud after outlier_filtering: " << a_cloud_filtered->width * a_cloud_filtered->height
       << " data points (" << pcl::getFieldsList (*a_cloud_filtered) << ").\n";
}
