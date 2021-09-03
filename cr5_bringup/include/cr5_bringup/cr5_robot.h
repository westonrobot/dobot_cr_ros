/**
 ***********************************************************************************************************************
 *
 * @author ZhangRan
 * @date   2021/08/07
 *
 * <h2><center>&copy; COPYRIGHT 2021 DOBOT CORPORATION</center></h2>
 *
 ***********************************************************************************************************************
 */

#include <string>
#include <memory>
#include <ros/ros.h>
#include <cr5_bringup/commander.h>
#include <actionlib/server/action_server.h>
#include <control_msgs/FollowJointTrajectoryAction.h>

#include <cr5_bringup/MovJ.h>
#include <cr5_bringup/MovL.h>
#include <cr5_bringup/ServoJ.h>
#include <cr5_bringup/MoveJog.h>
#include <cr5_bringup/ServoP.h>
#include <cr5_bringup/RelMovJ.h>
#include <cr5_bringup/RelMovL.h>
#include <cr5_bringup/JointMovJ.h>
#include <cr5_bringup/RobotStatus.h>

#include <cr5_bringup/ClearError.h>
#include <cr5_bringup/EnableRobot.h>
#include <cr5_bringup/DisableRobot.h>

using namespace actionlib;
using namespace control_msgs;

/**
 * CR5Robot
 */
class CR5Robot : protected ActionServer<FollowJointTrajectoryAction>
{
private:
    double goal_[6];
    uint32_t index_;
    ros::Timer timer_;
    ros::Timer movj_timer_;
    ros::NodeHandle control_nh_;
    std::shared_ptr<CR5Commander> commander_;
    std::vector<ros::Subscriber> subscriber_tbl_;
    std::vector<ros::ServiceServer> server_tbl_;

public:
    /**
     * Ctor
     * @param nh node handle
     * @param name topic
     */
    CR5Robot(ros::NodeHandle& nh, std::string name);

    /**
     * CR5Robot
     */
    ~CR5Robot() override;

    /**
     * init
     */
    void init();

    /**
     * getJointState
     * @param point
     */
    void getJointState(double* point);

    /**
     * getToolVectorActual
     * @param val value
     */
    void getToolVectorActual(double* val);

    /**
     * isEnable
     * @return ture enable, otherwise false
     */
    bool isEnable() const;

    /**
     * isConnected
     * @return ture connected, otherwise false
     */
    bool isConnected() const;

protected:
    bool movJ(cr5_bringup::MovJ::Request& request, cr5_bringup::MovJ::Response& response);
    bool movL(cr5_bringup::MovL::Request& request, cr5_bringup::MovL::Response& response);
    bool servoJ(cr5_bringup::ServoJ::Request& request, cr5_bringup::ServoJ::Response& response);
    bool servoP(cr5_bringup::ServoP::Request& request, cr5_bringup::ServoP::Response& response);
    bool relMovJ(cr5_bringup::RelMovJ::Request& request, cr5_bringup::RelMovJ::Response& response);
    bool relMovL(cr5_bringup::RelMovL::Request& request, cr5_bringup::RelMovL::Response& response);
    bool moveJog(cr5_bringup::MoveJog::Request& request, cr5_bringup::MoveJog::Response& response);
    bool jointMovJ(cr5_bringup::JointMovJ::Request& request, cr5_bringup::JointMovJ::Response& response);
    bool clearError(cr5_bringup::ClearError::Request& request, cr5_bringup::ClearError::Response& response);
    bool enableRobot(cr5_bringup::EnableRobot::Request& request, cr5_bringup::EnableRobot::Response& response);
    bool disableRobot(cr5_bringup::DisableRobot::Request& request, cr5_bringup::DisableRobot::Response& response);

private:
    void feedbackHandle(const ros::TimerEvent& tm,
                        actionlib::ActionServer<FollowJointTrajectoryAction>::GoalHandle handle);
    void moveHandle(const ros::TimerEvent& tm, actionlib::ActionServer<FollowJointTrajectoryAction>::GoalHandle handle);
    void goalHandle(actionlib::ActionServer<FollowJointTrajectoryAction>::GoalHandle handle);
    void cancelHandle(actionlib::ActionServer<FollowJointTrajectoryAction>::GoalHandle handle);
};
