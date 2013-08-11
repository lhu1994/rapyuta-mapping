/*
 * reduce_jacobian_icp.h
 *
 *  Created on: Aug 10, 2013
 *      Author: vsu
 */

#ifndef REDUCE_JACOBIAN_ICP_P2P_H_
#define REDUCE_JACOBIAN_ICP_P2P_H_

#include <keyframe.h>
#include <tbb/concurrent_vector.h>
#include <tbb/parallel_reduce.h>
#include <pcl/registration/correspondence_estimation.h>
#include <pcl/registration/correspondence_rejection_one_to_one.h>
#include <pcl/registration/correspondence_rejection_surface_normal.h>

struct reduce_jacobian_icp_p2p {

	Eigen::MatrixXf JtJ;
	Eigen::VectorXf Jte;
	int size;

	tbb::concurrent_vector<keyframe::Ptr> & frames;

	pcl::registration::CorrespondenceEstimation<pcl::PointNormal, pcl::PointNormal> ce;
	pcl::registration::CorrespondenceRejectorOneToOne croto;
	pcl::registration::CorrespondenceRejectorSurfaceNormal crsn;

	reduce_jacobian_icp_p2p(tbb::concurrent_vector<keyframe::Ptr> & frames,
			int size);

	reduce_jacobian_icp_p2p(reduce_jacobian_icp_p2p& rb, tbb::split);

	void operator()(
			const tbb::blocked_range<
					tbb::concurrent_vector<std::pair<int, int> >::iterator>& r);

	void join(reduce_jacobian_icp_p2p& rb);

};



#endif /* REDUCE_JACOBIAN_ICP_POINT_TO_PLANE_H_ */