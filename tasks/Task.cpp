/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"
#include <base/commands/Joints.hpp>

using namespace motoman_mh12_streamer;
using namespace motoman_mh12;

Task::Task(std::string const& name)
    : TaskBase(name)
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine)
{
}

Task::~Task()
{
}

/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

bool Task::configureHook()
{
    if (! TaskBase::configureHook())
        return false;

    return true;
}
bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;

    driver.openTCP("192.168.10.77",50241);
    return true;
}
void Task::updateHook()
{
    TaskBase::updateHook();
    msgs::MotomanMsgType msg_type =  driver.read(); 
    if(msg_type == msgs::MOTOMAN_JOINT_FEEDBACK)
    {
        msgs::MotomanJointFeedback joint_feedback = driver.getJointFeedback();
        base::commands::Joints joints;
        joints.elements = joint_feedback.joint_states;
        joints.time = joint_feedback.time;
    }
    else
    {
        msgs::MotomanStatus status = driver.getRobotStatus();
        _error_code.write(status.error_code);
    }
    
}
void Task::errorHook()
{
    TaskBase::errorHook();
}
void Task::stopHook()
{
    TaskBase::stopHook();
}
void Task::cleanupHook()
{
    TaskBase::cleanupHook();
}
