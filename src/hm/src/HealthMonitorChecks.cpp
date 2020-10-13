#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "auv_interfaces/srv/power.hpp"

using std::placeholders::_1;

class HealthMonitorChecks : public rclcpp::Node
{
public:
  HealthMonitorChecks()
  : Node("health_monitor_checks")
  {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "battery_level", 10, std::bind(&HealthMonitorChecks::topic_callback, this, _1));
  }

private:
  void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<HealthMonitorChecks>());
  rclcpp::shutdown();
  return 0;
}