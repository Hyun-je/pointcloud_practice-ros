# pointcloud_practice-ros

## How to Build
Ubuntu Native (Bionic + ROS Melodic)


#### Step 1. Install dependencies
```
sudo apt-get install ros-melodic-velodyne ros-melodic-pcl-ros ros-melodic-pcl-conversions
```
#### Step 2. Clone source code
```
git clone --recursive https://github.com/Hyun-je/pointcloud_practice-ros ~/catkin_ws/src
```
#### Step 3. Run catkin_make
```
cd ~/catkin_ws && catkin_make
```

## Screenshots
| *Voxelization* | *PassThrough* | *Clustering* |
|----|----|----|
| ![voxel](https://user-images.githubusercontent.com/7419790/120882728-9700f500-c614-11eb-8100-7149eaa7155c.png) | ![passThrough](https://user-images.githubusercontent.com/7419790/120882726-96685e80-c614-11eb-9596-d6e34f5143ce.png) | ![cluster](https://user-images.githubusercontent.com/7419790/120882724-949e9b00-c614-11eb-8001-8145c9899921.png) |

## References
- PCL Documentation  https://pcl.readthedocs.io/projects/tutorials/en/latest/



