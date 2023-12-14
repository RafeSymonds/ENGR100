# Rocket Simulation

Rocket simulation that tracks the position, velocity, and acceleration of a model rocket. Designed for ENGR100 (980) Rocket Science.

## Simulation design has 3 major components 
We wanted our simulation to be able to accurately predict the position, velocity, and acceleration of a model rocket throughout the entire flight while allowing a high degree of customization to the user. To accomplish this we wrote our program in C++ to allow us to easily calculate the 3 variables at every moment of the flight. Our final simulation package performs 3 major functions: impact assessment module, terminal velocity monitoring, and rocket launch prediction.

### Impact Assessment Module 
Our simulation can predict the position, velocity, and acceleration of a falling rocket. By using adjustable variables—such as mass, drag coefficient, frontal area, and ground impulse time—our product can analyze what happens to the rocket during landing. We calculate the acceleration of the rocket throughout descent by calculating the force of gravity and the force of air resistance acting on the rocket. Once the rocket hits the ground, we calculate the rocket’s acceleration by using impulse with the user-specified time to calculate the reaction force from the ground. This part of the simulation is a valuable tool for rocket design because the forces the rocket has to withstand during landing can easily be identified before starting the building process.

### Terminal Velocity Monitoring 
The rocket’s terminal velocity can easily be measured with our simulation. Our high level of customization allows users to have a personalized simulation that can accurately track their custom rocket. Our package allows users to specify the rocket mass, the parachute size, the parachute deployment delay, the parachute drag coefficient, and the starting altitude. The parachute opening delay can also be accounted for. These variables allow very precise terminal velocity calculations to be done in real-time. Potential designs can easily be tested on our program, allowing companies to save money by building fewer versions of similar rockets. The terminal velocity monitor is also seamlessly integrated with the impact assessment module, so users will also be able to know the forces that will act on their rocket after reaching terminal velocity.

### Rocket Launch Tracking 
The primary part of our simulation is the prediction of the position, velocity, and acceleration of a model rocket throughout the entire flight. Our simulation allows customization of the engine thrust profile, fuel exhaust rate, and the rocket’s mass to have an accurate representation of the accent phase of the rocket. The Rocket Launch Tracker is coupled with the terminal velocity monitor and impact assessment module to allow every phase of the flight to be modeled.
