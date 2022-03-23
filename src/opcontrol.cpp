// Include the API
#include "pros-grafana-lib/api.h"
#include "main.h"

void opcontrol() {
	// You should put all of this code in a method you call wherever you want to track data, e.g. opcontrol()
	grafanalib::GUIManager manager;

	// The interval in milliseconds at which data should be sent (default 20ms).
	// A few disclaimers:
	// - A rate too fast will cause data to be dropped
	// - Wireless is significantly limited in its speed, requiring a refresh rate of > 100ms. 
	manager.setRefreshRate(20);

	// Standard motor declarations 
	pros::Motor leftFrontMotor(1);
	pros::Motor rightFrontMotor(2);
	pros::Motor leftBackMotor(3);
	pros::Motor rightBackMotor(4);

	// Declare the variables we'll be tracking 
	grafanalib::Variable<pros::Motor> leftFrontMotorVar("Left Front Motor", leftFrontMotor);
	// grafanalib::Variable<pros::Motor> rightFrontMotorVar("Right Front Motor", rightFrontMotor);
	// grafanalib::Variable<pros::Motor> leftBackMotorVar("Left Back Motor", leftBackMotor);
	// grafanalib::Variable<pros::Motor> rightBackMotorVar("Right Back Motor", rightBackMotor);
	
	// If you have a group of motors that you want to track together, you can make a VariableGroup:
	grafanalib::VariableGroup<pros::Motor> chassisVars({leftFrontMotorVar});

	// Getters added to a VariableGRroup will add getters to ALL of the Variables assigned to it 
	// In this example, the GUI will track the temperature, actual velocity, efficiency, 
	// and voltage for all 4 chassis motors.
	// Format: add_getter(<what the property should display as>, <a reference to the function the getter will pull from>)
	chassisVars.add_getter("Temperature", &pros::Motor::get_temperature);
	chassisVars.add_getter("Actual Velocity", &pros::Motor::get_actual_velocity);
	chassisVars.add_getter("Voltage", &pros::Motor::get_voltage);
	chassisVars.add_getter("Efficiency", &pros::Motor::get_efficiency);

	// Variable groups and variables must then be registered to the GUIManager:
	manager.registerDataHandler(&chassisVars);

	// You can start the data task at any time:
	manager.startTask();

	while(true) {
		pros::delay(20);
	}
}
