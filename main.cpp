#include <iostream>

using namespace std;

static double timeStep = 0.01;
static double flightTime = 10;
static double airDensity = 1.29;


// mass in kg
static double rocketMass = 0.170 + 0.03;
static double engineTotalMass = 0.032;   //0.0612
static double fuelMass = 0.0124;          //0.0369
static double pcbMass = 0.050;

static double burnTime = 0.9;

static double impulseTimeOnGroundSeconds = 0.1;

static double rocketDragCoefficient = 0.75;
static double rocketFrontalArea = 0.012;
static double parachuteDragCoefficient = 1;
static double parachuteFrontalArea = 0.184;
static double parachuteDelay = 3;


static double launchHeight = 2;

//useEngine simulates a launch 
//simulates a drop from specified height if useEngine is false
static bool useEngine = false;

//useParachute simulates with the parachute or not
static bool useParachute = false;




static double totalMass = rocketMass + engineTotalMass + pcbMass + fuelMass;

double dragCoefficientCalculation(double time){
    if(useParachute && !useEngine){
        return parachuteDragCoefficient;
    }

    if(time > burnTime + parachuteDelay && useParachute){
        return parachuteDragCoefficient;
    }
    else{
        return rocketDragCoefficient;
    }
}

double frontalArea(double time){
    //if not using engine and using parachute start with it deployed
    if(useParachute && !useEngine){
        return 0.184;
    }

    if(time < burnTime + parachuteDelay || !useParachute){
        return rocketFrontalArea;
    }
    else if(time < burnTime + parachuteDelay + 2){//parachute opening over 2 seconds
       return rocketFrontalArea + parachuteFrontalArea /2 * (time- (burnTime + parachuteDelay));
    }
    else{
        return parachuteFrontalArea;
    }
}

double mass(double time){
    if(time < burnTime){  //2.7
        return totalMass - (fuelMass / burnTime) * time;
    }
    else{
        return totalMass - fuelMass;
    }
    //0.2468
}

double calculateThrustForce(double time){   
    if(!useEngine){
        return 0;
    }

    if(time < 0.275){
        return time * 80;
    }
    else if(time < 0.35){
        return 22 - (time - 0.275) * 16;
    }
    else if(time < 0.9){
        return 7.5;
    }
    else{
        return 0;
    }

    /*
    if(time < 0.25){
        return 125 * time;
    }
    else if(time < 0.5){
        return 30 - 72 * (time - 0.25);
    }
    else if(time < 2.8){
        return 10;
    }
    else{
        return 0;
    }
    */ 
}

double calculateGravityForce(double mass){
    return mass * -9.8;
}

double calculateDragForce(double frontalArea, double velocity, double time){
    if(velocity >= 0){
        return -(frontalArea * velocity * velocity * dragCoefficientCalculation(time) * airDensity) / 2;
    }
    else{
        return (frontalArea * velocity * velocity * dragCoefficientCalculation(time) * airDensity) / 2;
    }
    
}

double calculateAcceleration(double time, double mass, double frontalArea, double velocity){
    double acceleration = (calculateThrustForce(time) + calculateGravityForce(mass) + calculateDragForce(frontalArea, velocity,time)) / mass;
    if(time < 0.5 && acceleration < 0 && useEngine){
        return 0;
    }
    return acceleration;
}


double calculateVelocity(double previousVelocity, double previousAcceleration){
    return previousVelocity + previousAcceleration * timeStep;
}

double calculatePosition(double previousPosition, double previousVelocity, double previousAcceleration){
    return previousPosition + previousVelocity * timeStep + previousAcceleration * timeStep * timeStep;
}

double calculateAccelerationFromGround(double previousVelocity){
    return (0 - previousVelocity) / impulseTimeOnGroundSeconds;
}




int main(){

    cout << "time" << "," << "position" << "," << "velocity" << "," << "acceleration" << endl;

    double previousPosition = launchHeight;
    double previousVelocity = 0;
    double previousAcceleration = 0;

    double hitGroundTime = 0;
    double hitGroundAcceleration = 0;

    for(double time = 0; time < flightTime; time += timeStep){
        double newPosition = 0;
        double newVelocity = 0;
        double newAcceleration = 0;

        

        if(hitGroundTime != 0 || (previousPosition < 0 && time > 0.05)){ //hit ground
            newPosition = 0;
            newVelocity = calculateVelocity(previousVelocity, previousAcceleration);
            
            if(hitGroundTime == 0){
                hitGroundTime = time;
                newAcceleration = calculateAccelerationFromGround(newVelocity);
                hitGroundAcceleration = newAcceleration;
            }
            else{
                newAcceleration = hitGroundAcceleration;
            }
            if(time  - hitGroundTime > impulseTimeOnGroundSeconds){
                newAcceleration = -9.8;
                newVelocity = 0;
            }
            
        }
        else{
            newPosition = calculatePosition(previousPosition, previousVelocity, previousAcceleration);
            newVelocity = calculateVelocity(previousVelocity, previousAcceleration);
            newAcceleration = calculateAcceleration(time, mass(time), frontalArea(time), previousVelocity);
        }
        cout << time << "," << newPosition << "," << newVelocity << "," << newAcceleration << endl;

        previousPosition = newPosition;
        previousVelocity = newVelocity;
        previousAcceleration = newAcceleration;
        
        
    }
}