<!-- Operating the test-bed -->
## Operating the test-bed

Instruction to operate the test-bed from the Iridia computer Socrates. 
The Arduino code should already be uploaded on the device. 

On the computer, open 5 terminal. 

### To set up every terminal 

  ```sh
  source /opt/ros/noetic/setup.bash
  ```
  
  ```sh
  source ~/catkin_ws/devel/setup.bash
  ```

### In each terminal

1. Launch ROS core
   
   ```sh
   roscore
   ```
   
3. Launch camera 

   ```sh
   roslaunch tycho_launchers phormica_camera.launch
   ```
   
3. Launch visualization

   ```sh
   rosrun rviz rviz -d /home/students/catkin_ws/src/demiurge-tycho/tycho_launchers/launch/rviz_phormica.rviz
   ```
   
4. Launch serial connection with the Arduino

   ```sh
   rosrun rosserial_arduino serial_node.py /dev/ttyACM0
   ```
   
6. Moving the LEDs.
   
   For setting everything to zero, that is, to stop everything
   ```sh
   rostopic pub /arduino_control std_msgs/Bool "data: false" -1
   ```
   
   For moving the LEDs (it automaticall takes into account the current position)
   ```sh
   rostopic pub /arduino_control std_msgs/Bool "data: true" -1 
   ```

<p align="right">(<a href="#top">back to top</a>)</p>






