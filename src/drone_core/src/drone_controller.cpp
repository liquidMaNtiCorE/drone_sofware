#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <chrono>

using namespace std::chrono_literals;

class DroneController : public rclcpp::Node {
public:
    DroneController() : Node("drone_controller") {
        // Létrehozunk egy publikálót (Publisher) a cmd_vel topicra
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
        
        // Időzítő, ami 50 ezredmásodpercenként (20 Hz) meghívja a timer_callback függvényt
        timer_ = this->create_wall_timer(
            50ms, std::bind(&DroneController::timer_callback, this));
            
        RCLCPP_INFO(this->get_logger(), "Autonóm vezérlés indítva (20 Hz). A drón mozgásba lendül...");
    }

private:
    void timer_callback() {
        auto msg = geometry_msgs::msg::Twist();
        
        // Egyenletes mozgás beállítása
        msg.linear.x = 1.0;   // 1.0 m/s sebességgel előre
        msg.linear.z = 11.0;   // 0.5 m/s sebességgel emelkedik
        msg.angular.z = 10.0;  // 1.0 rad/s sebességgel fordul (körpálya)

        publisher_->publish(msg);
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DroneController>());
    rclcpp::shutdown();
    return 0;
}