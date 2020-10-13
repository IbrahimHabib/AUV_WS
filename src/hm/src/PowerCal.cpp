#include "rclcpp/rclcpp.hpp"
#include "auv_interfaces/srv/power.hpp"

#include <memory>

void power(const std::shared_ptr<auv_interfaces::srv::Power::Request> request,
          std::shared_ptr<auv_interfaces::srv::Power::Response>      response)
{
  response->power = request->ampere * request->volt;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\nampere: %f" " volt: %f",
                request->ampere, request->volt);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%f]", (float)response->power);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("power_calculation");

  rclcpp::Service<auv_interfaces::srv::Power>::SharedPtr service =
node->create_service<auv_interfaces::srv::Power>("power_calculation", &power);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to provide power val;ue in W.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}