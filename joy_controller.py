#! /urs/bin/env python3

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy

class JoyStickControl(Node):
    def __init__(self):
        super().__init__("joy_controller")
        
        self.declare_parameter("Lin", 300.0)
        self.declare_parameter("Ang", 300.0)

        self.lin= self.get_parameter("Lin").value
        self.ang= self.get_parameter("Ang").value

        self.time= True

        self.pub_= self.create_publisher(Twist, "/cmd_vel", 10)

        self.sub_= self.create_subscription(Joy, '/joy', self.joy_callback, 10)

        self.timer_= self.create_timer(0.4, self.call_back)


    def call_back(self):
        self.time= True
        


    def joy_callback(self, msg: Joy):
        if(msg.axes[6]):
            self.lin-= 10.0
        elif(msg.axes[7]):
            self.ang+= 10.0
        if self.time== False:
            pass

        else:

            twist= Twist()
            
            twist.linear.x= msg.axes[1]*self.lin
            twist.angular.z= msg.axes[2]*self.ang
            
            self.pub_.publish(twist)
            self.time= False


def main(args=None):
    rclpy.init(args=args)
    node = JoyStickControl()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()


