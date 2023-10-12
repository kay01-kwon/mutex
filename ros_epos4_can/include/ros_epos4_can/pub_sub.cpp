#include "pub_sub.hpp"

PUB_SUB::PUB_SUB()
{
  // Data Initialization
  target_ = 0;
  time_curr = time_prev;
  dt = 0;


  // Publisher and subscriber setup
  publisher_ = nh_.advertise<Int32>("/actual_value",1);
  subscriber_ = nh_.subscribe("/target_value",1,&PUB_SUB::callback,this);

}

void PUB_SUB::write()
{
  boost::mutex::scoped_lock lock(mutex_);
  for(int id = 0; id < NUM_ID; id++){
    cout<<"*** Write function ***"<<endl;
    cout<<"Target Id - "<<id<<" : "<<endl;
  }
  

}

void PUB_SUB::read()
{
  boost::mutex::scoped_lock lock(mutex_);

  for(int id = 0; id < NUM_ID; id++)
  {
    cout<<"*** Read function ***"<<endl;
    cout<<"Target Id - "<<id<<" : ";
    cout<<target_<<" Loop time: "<<dt<<endl;
    target_value.data = target_;
  }
}

void PUB_SUB::callback(const Int32::ConstPtr& msg)
{

  
  target_ = msg->data;
  
  cout<<target_<<endl;

  time_curr = ros::Time::now().toSec();
  dt = time_curr - time_prev;

  thread_write = boost::thread(boost::bind(&PUB_SUB::write, this));

  thread_read = boost::thread(boost::bind(&PUB_SUB::read, this));


  time_prev = time_curr;

  publisher_.publish(target_value);

}

PUB_SUB::~PUB_SUB()
{

  for(int id_ = 0; id_ < NUM_ID; id_++)
  {
    thread_write.join();
  }

  for(int id_ = 0; id_ < NUM_ID; id_++)
  {
    thread_read.join();
  }

}