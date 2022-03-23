<div align="center" id="top"> 
  <img src="https://user-images.githubusercontent.com/50118124/130684955-c0ffd8f8-f8b8-4173-aae3-c3896474055f.png" alt="Pros Grafana Lib" />

  &#xa0;
</div>

<h1 align="center">PROS Grafana Library</h1>

<p align="center">
  <img alt="Github top language" src="https://img.shields.io/github/languages/top/BWHS-Robotics/pros-grafana-lib?color=56BEB8">

  <!-- <img alt="Github issues" src="https://img.shields.io/github/issues/Yerti/pros-grafana-lib?color=56BEB8" /> -->

  <!-- <img alt="Github forks" src="https://img.shields.io/github/forks/Yerti/pros-grafana-lib?color=56BEB8" /> -->

  <!-- <img alt="Github stars" src="https://img.shields.io/github/stars/Yerti/pros-grafana-lib?color=56BEB8" /> -->
</p>


<h4 align="center"> 
	🚧 This library is still highly experimental  🚧
</h4> 

<hr>

<p align="center">
  <a href="#dart-about">About</a> &#xa0; | &#xa0; 
  <a href="#sparkles-features">Features</a> &#xa0; | &#xa0;
  <a href="#rocket-technologies">Technologies</a> &#xa0; | &#xa0;
  <a href="#white_check_mark-requirements">Requirements</a> &#xa0; | &#xa0;
  <a href="#checkered_flag-starting">Starting</a> &#xa0; | &#xa0;
  <a href="#memo-usage">Usage</a> &#xa0; | &#xa0;
  <a href="https://github.com/Yerti" target="_blank">Author</a>
</p>

<br>

## :dart: About ##

This project aims to improve the VEX Robotics development process by allowing statistics to easily be recorded by a V5 brain and in realtime be sent to a Grafana dashboard. The PROS Grafana Library consists of three parts:
- The [PROS C++ template](https://github.com/BWHS-Robotics/pros-grafana-lib) (this repository)
- The [PROS-Grafana CLI](https://github.com/BWHS-Robotics/pros-grafana-cli), adding a custom command for brain interaction 
- (Unfinished) The optional Grafana plugin allowing for custom visualization of data such as absolute positioning 

## :sparkles: Features ##

:heavy_check_mark: Easily track multiple objects at once\
:heavy_check_mark: Easy chart and visualization creation \
:heavy_check_mark: Wireless support

## :rocket: Technologies ##

The following tools were used in this project:

- [PROS](https://pros.cs.purdue.edu/)
- [nlohmann/json](https://github.com/nlohmann/json)

## :white_check_mark: Requirements ##

Before starting :checkered_flag:, you need to have [Git](https://git-scm.com) installed and a [PROS](https://pros.cs.purdue.edu/v5/getting-started/) project.

## :checkered_flag: Starting ##

To use the template in your PROS project, you must first download the template zip (<a href="https://github.com/BWHS-Robotics/pros-grafana-lib/raw/main/pros-grafana-lib%401.0.0.zip" target="_blank">`pros-grafana-lib@1.0.0.zip`</a>) from the repository. 

You can install it using the following commands in a terminal at the root of your project:

```bash
# Import the zip to the PROS depot 
$ pros c fetch pros-grafana-lib@1.0.0.zip

# Apply the library to your project
$ pros c apply pros-grafana-lib --force-apply

```
## :memo: Usage ##

For an example in context, please see `src/opcontrol.cpp`.

To access the template, you can import the following header: `#include "pros-grafana-lib/api.h"`

First, you need to initialize the GUIManager: 
```cpp
auto manager = std::make_shared<grafanalib::GUIManager>();

// The interval in milliseconds at which data should be sent (default 20ms).
// A few disclaimers:
// - A rate too fast will cause data to be dropped
// - Wireless is significantly limited in its speed, requiring a refresh rate of > 100ms. 
manager->setRefreshRate(20);
```

For testing, a few dummy motor objects will be created. In reality, these can be any object you want to track. 
```cpp
// Standard motor declarations 
pros::Motor leftFrontMotor(1);
pros::Motor rightFrontMotor(2);
pros::Motor leftBackMotor(3);
pros::Motor rightBackMotor(4);
```

We then have to create Variable<T> objects that are responsible for managing display names and 'getters': 
```cpp
// Declare the variables we'll be tracking 
grafanalib::Variable<pros::Motor> leftFrontMotorVar("Left Front Motor", leftFrontMotor);
grafanalib::Variable<pros::Motor> rightFrontMotorVar("Right Front Motor", rightFrontMotor);
grafanalib::Variable<pros::Motor> leftBackMotorVar("Left Back Motor", leftBackMotor);
grafanalib::Variable<pros::Motor> rightBackMotorVar("Right Back Motor", rightBackMotor);

// If you have a group of motors (e.g. chassis) that you want to track together, you can make a VariableGroup:
grafanalib::VariableGroup<pros::Motor> chassisVars({leftFrontMotorVar, rightFrontMotorVar, leftBackMotorVar, rightBackMotorVar});
```

Now that the variables are declared, we choose which methods from the objects to track and the name they'll be given in the Grafana dashboard:
```cpp
// Getters added to a VariableGRroup will add getters to ALL of the Variables assigned to it 
// In this example, the GUI will track the temperature, actual velocity, efficiency, 
// and voltage for all 4 chassis motors.
// Format: add_getter(<what the property should display as>, <a reference to the function the getter will pull from>)
chassisVars.add_getter("Temperature", &pros::Motor::get_temperature);
chassisVars.add_getter("Actual Velocity", &pros::Motor::get_actual_velocity);
chassisVars.add_getter("Voltage", &pros::Motor::get_voltage);
chassisVars.add_getter("Efficiency", &pros::Motor::get_efficiency);
```

Finally, we register the Variables or VariableGroups to the GUIManager and start the task: 

```cpp
// Variable groups and variables must then be registered to the GUIManager:
manager->registerDataHandler(&chassisVars);

// You can start the data task at any time:
manager->startTask();
```

For using this tracking in conjunction with Grafana and the CLI, please navigate to the [pros-grafana-cli](https://github.com/BWHS-Robotics/pros-grafana-cli) repository for the next steps.

<hr>

Made with :heart: by <a href="https://github.com/UZ9" target="_blank">Ryder</a>

&#xa0;

<a href="#top">Back to top</a>
