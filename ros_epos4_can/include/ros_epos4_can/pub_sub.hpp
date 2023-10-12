#ifndef PUB_SUB_HPP
#define PUB_SUB_HPP
#include <ros/ros.h>
#include <std_msgs/Int32.h>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/chrono.hpp>

#define NUM_ID 9

using std_msgs::Int32;
using std::cout;
using std::endl;


class PUB_SUB{

  public:
  // Constructor
  PUB_SUB();

  void write();

  void read();

  void callback(const Int32::ConstPtr& target);

  // Destructor
  ~PUB_SUB();

  private:

  ros::NodeHandle nh_;
  ros::Publisher publisher_;
  ros::Subscriber subscriber_;

  boost::thread thread_write;
  boost::thread thread_read;

  boost::mutex mutex_;

  int target_;
  int id_;

  Int32 target_value;

  double time_prev;
  double time_curr;
  double dt;

};



#endif