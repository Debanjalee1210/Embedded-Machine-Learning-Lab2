# Embedded Machine Learning Lab2
 CEN 598 :Simple Sleeping Posture Detection
A simple algorithm that makes inference about sleeping postures using sensor data

Lying posture tracking provides important clinical information about a patient’s mobility,
risk of developing hospital-acquired pressure injuries, and quality of sleep. Therefore,
accurate estimation of lying postures during sleep at night plays a crucial role in
monitoring well-being of the individuals.
In this project, we used the IMU sensor unit embedded in the Arduino board to
gather sensor data that mimics various lying postures, and design and implement an
algorithm that turns the on-board LED on to indicate the specific lying posture. We
focused on three lying postures of interest including supine, prone, side (either right side or
left side). Assume that the sensor unit is attached to the chest of the user. The goal is to
design a system that will
• Turn the LED ON and OFF once if the detected posture is supine (blinking once)
• Turn the LED ON and OFF twice if the detected posture is prone (blinking twice)
• Turn the LED ON and OFF three times if the detected posture is side (blinking three
times)
• Keep the LED OFF if none of the above postures is detected
