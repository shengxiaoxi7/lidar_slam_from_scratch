# LiDAR SLAM From Scratch

从零开始手写一个 LiDAR SLAM 系统，基于 ROS 和 PCL 实现。

## 🎯 项目目标

通过渐进式开发，从基础到高级逐步实现一个完整的 3D LiDAR SLAM 系统，包括：
- 点云预处理
- 里程计估计
- 局部建图
- 回环检测
- 后端优化
- 全局地图构建

## 📦 当前版本: V0.1

**功能：**
- ✅ ROS 节点基础框架
- ✅ 点云数据订阅与发布
- ✅ 体素滤波降采样
- ✅ 统计滤波去除离群点
- ✅ RViz 可视化配置

## 🔧 依赖项

- ROS (Melodic/Noetic)
- PCL 1.8+
- Eigen3

```bash
sudo apt-get install ros-$ROS_DISTRO-pcl-ros ros-$ROS_DISTRO-pcl-conversions
sudo apt-get install libeigen3-dev
```

## 🚀 编译与运行

### 编译
```bash
cd ~/lidar_slam_ws
catkin_make
source devel/setup.bash
```

### 运行
```bash
# 方式1：使用 launch 文件（推荐）
roslaunch lidar_slam_from_scratch lidar_slam.launch

# 方式2：单独启动节点
rosrun lidar_slam_from_scratch lidar_slam_node
```

### 测试
使用 rosbag 播放 LiDAR 数据：
```bash
rosbag play your_lidar_data.bag
```

## 📊 话题接口

**订阅：**
- `/velodyne_points` (sensor_msgs/PointCloud2) - 原始点云数据

**发布：**
- `/filtered_cloud` (sensor_msgs/PointCloud2) - 滤波后的点云

## ⚙️ 参数配置

参数文件：`config/params.yaml`

```yaml
voxel_leaf_size: 0.5    # 体素滤波器大小 (米)
sor_meank: 50           # 统计滤波近邻点数
sor_stddev: 1.0         # 标准差倍数
```

## 📅 开发路线图

- [x] **V0.1** - 基础框架与数据可视化 (当前版本)
- [ ] **V0.2** - 里程计模块 (ICP 配准)
- [ ] **V0.3** - 局部建图
- [ ] **V0.4** - 回环检测
- [ ] **V0.5** - 后端优化
- [ ] **V0.6** - 完整系统集成
- [ ] **V1.0** - 发布版本

## 📝 版本历史

### V0.1 (2025-10-30)
- 初始版本发布
- 实现基础 ROS 节点框架
- 添加点云预处理功能
- 配置 RViz 可视化

## 🤝 贡献

欢迎提交 Issue 和 Pull Request！

## 📄 许可证

MIT License

## 👨‍💻 作者

- **syx** - [shengyx77@gmail.com](mailto:shengyx77@gmail.com)

## 📚 参考资料

- [LOAM](https://github.com/laboshinl/loam_velodyne)
- [LeGO-LOAM](https://github.com/RobustFieldAutonomyLab/LeGO-LOAM)
- [LIO-SAM](https://github.com/TixiaoShan/LIO-SAM)
- [Point Cloud Library (PCL)](https://pointclouds.org/)