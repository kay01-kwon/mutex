#include <ros_epos4_can/pub_sub.hpp>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "Pub_sub");

  PUB_SUB pub_sub_test;

  while (ros::ok())
  {
    ros::spinOnce();
  }

  cout<<"Exit"<<endl;
  return 0;
  
}