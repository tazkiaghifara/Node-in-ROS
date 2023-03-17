#include "ros/ros.h"
#include "std_msgs/Int16.h"

ros::Publisher pub_1;
ros::Publisher pub_2;
ros::Publisher pub_3;

ros::Subscriber sub_1;
ros::Subscriber sub_2;
ros::Subscriber sub_3;

ros::Timer tim_50_hz;

void cllbck_tim_50_hz(const ros::TimerEvent &event)
{
    std_msgs::Int16 msg_1;
    msg_1.data = 98;
    pub_1.publish(msg_1);

}
void cllbck_sub_2(const std_msgs::Int16 &msg_2)
{
    ROS_INFO("data kiriman node 1 : %d", msg_2.data);
}
void cllbck_sub_3(const std_msgs::Int16 &msg_3)
{
    ROS_INFO("data kiriman node 3 : %d", msg_3.data);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "node_2");

    ros::NodeHandle NH;
    ros::MultiThreadedSpinner MTS;

    tim_50_hz = NH.createTimer(ros::Duration(0.02), cllbck_tim_50_hz);
    pub_1 = NH.advertise<std_msgs::Int16>("topic_2", 16);
    sub_2 = NH.subscribe("topic_1", 16, cllbck_sub_2);
    sub_3 = NH.subscribe("topic_3", 16, cllbck_sub_3);

    MTS.spin();
}
