/*
 * visualization.h
 *
 *  Created on: Dec 6, 2015
 *      Author: marius
 */

#ifndef _VISUALIZATION_H_
#define _VISUALIZATION_H_

#include <parameter/visualization_bag.h>
#include <visualization_msgs/MarkerArray.h>
#include <geometry_msgs/PoseArray.h>
#include <localization_processor.h>

// Forward declaration
struct pose;

class visualization
{
public:
	visualization (visualization_bag visual_param);
	void visualize_particle (std::vector<geometry_msgs::Pose> the_particles,
							 visualization_msgs::MarkerArray::Ptr a_marker_array, int a_marker_id,
							 float a_color_r, float a_color_g, float a_color_b);
	void visualize_particle_pose (geometry_msgs::PoseArray::Ptr a_poseArray, std::vector<pose> the_particles);

private:
	visualization_bag visual_param;
};


#endif /* _VISUALIZATION_H_ */