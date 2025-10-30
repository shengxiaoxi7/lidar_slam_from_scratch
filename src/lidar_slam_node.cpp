#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/statistical_outlier_removal.h>

class LidarSlamNode {
private:
    ros::NodeHandle nh_;
    ros::Subscriber cloud_sub_;
    ros::Publisher cloud_filtered_pub_;

    double voxel_leaf_size_;
    int sor_meank_;
    double sor_stddev_;
    
public:
    LidarSlamNode() : nh_("~") {
        
        nh_.param<double>("voxel_leaf_size", voxel_leaf_size_, 0.2);
        nh_.param<int>("sor_meank", sor_meank_, 50);
        nh_.param<double>("sor_stddev", sor_stddev_, 1.0);
        
        cloud_sub_ = nh_.subscribe("/velodyne_points", 10, &LidarSlamNode::cloudCallback, this);
        cloud_filtered_pub_ = nh_.advertise<sensor_msgs::PointCloud2>("/filtered_cloud", 10);
        
        ROS_INFO("LiDAR SLAM Node V0.1 Initialized!");
        ROS_INFO("  - Voxel leaf size: %.2f", voxel_leaf_size_);
        ROS_INFO("  - SOR mean K: %d", sor_meank_);
        ROS_INFO("  - SOR stddev: %.2f", sor_stddev_);
    }
    
    void cloudCallback(const sensor_msgs::PointCloud2::ConstPtr& cloud_msg) {
        
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::fromROSMsg(*cloud_msg, *cloud);
        
        // ROS_INFO_THROTTLE(1.0, "Received cloud with %lu points", cloud->size());
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered = preprocessCloud(cloud);

        sensor_msgs::PointCloud2 output;
        pcl::toROSMsg(*cloud_filtered, output);
        output.header = cloud_msg->header;
        cloud_filtered_pub_.publish(output);
        
        // ROS_INFO_THROTTLE(1.0, "Published filtered cloud with %lu points", cloud_filtered->size());
    }
    
    pcl::PointCloud<pcl::PointXYZ>::Ptr preprocessCloud(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud) {

        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_voxel(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::VoxelGrid<pcl::PointXYZ> voxel_filter;
        voxel_filter.setInputCloud(cloud);
        voxel_filter.setLeafSize(voxel_leaf_size_, voxel_leaf_size_, voxel_leaf_size_);
        voxel_filter.filter(*cloud_voxel);

        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
        sor.setInputCloud(cloud_voxel);
        sor.setMeanK(sor_meank_);
        sor.setStddevMulThresh(sor_stddev_);
        sor.filter(*cloud_filtered);
        
        return cloud_filtered;
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "lidar_slam_node");
    
    LidarSlamNode node;
    
    ros::spin();
    
    return 0;
}
