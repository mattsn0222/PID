# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

Fellow students have put together a guide to Windows set-up for the project [here](https://s3-us-west-1.amazonaws.com/udacity-selfdrivingcar/files/Kidnapped_Vehicle_Windows_Setup.pdf) if the environment you have set up for the Sensor Fusion projects does not work for this project. There's also an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3).

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Rubric points

### Compilation

#### Your code should compile. Code must compile without errors with cmake and make.

There is no errors during compilation without any modification on the provided setup.

### Implementation

#### The PID procedure follows what was taught in the lessons.

The PID implementation is done on the "./SRC/PID.cpp". Necessary coefficients to achieve PID calculation are defined in PID class.
PID::UpdateError method calculates proportional, differencial, and integral erros, and PID::TotalError calculates total error with the coefficients.

## Reflection

### Describe the effect each of the P, I, D components had in your implementation.

* The propotional components: This portion tries to steer the car towards the center line proportional to the cross-track error. This considers only how much the car is apart from the reference line, so it will let the car overshoot at first. Then it tries to set steer the car towards reference line, and overshoot again. So it's never stable on the reference line, and oscillates around the reference line.

* The integral components: This portion takes the sum of the past errors into account to define the next steering angle. It will remove a possible bias on the control system such as mechanical steering angle bias.

* The differential components: This portion utilizes the difference of the current and the previous errors into the next steering angle. This helps to smooth the change of the steering angle to avoid overshoot and oscillation around reference line.

### Visual aids are encouraged, i.e. record of a small video of the car in the simulator and describe what each component is set to.

I implemented two PIDs. One for steering angle, and the other one is for throttle to adjust speed.
First, I tried to optimize the PID parameters for steering and fixed throttle = 0.3 which can drive around 35 mph at maximum.

#### PID parameters for steering
I assumed that there is no bias in the simulation, so the integral component Ki is set as zero. Started from proportional components and differential compoonents (Kp and Kd) as 1.0.
As you can see below video, the vehicle is oscillating a lot especially in the curve.
<img src="./file/1stAttempt.mov.gif" width="480" alt="1st Attempt Video" />

 I repeated twiddle optimization several times, and came to the parameter as below.
 * P: Kp = 0.14
 * I: Ki = 0.0
 * D: Kd = 1.1
 
 #### PID parameters for throttle
 Then, I tried to fix PID parameter for throttle. I set the target speed as 35 mph, and fixed with the below parameters.
 * P: Kp = 0.2
 * I: Ki = 0.0
 * D: Kd = 1.0

The above PID parameters show very stable speed.

Here is the video of the car in the simulator with the above PID parameters and target speed as 35MPH

<img src="./file/final.mov.gif" width="480" alt="Final Video" />

## Simulation
### The vehicle must successfully drive a lap around the track.
No tire left the drivable portion of the track surface. The car did not pop up onto ledges or roll over any surfaces.

## Room for improvement.
When I changed target speed, the vehicle behavior is very different, especially in faster speed.
It's very difficult to find the optimum PID parameters for 60MPH constant speed (7th attempt in the code).
As usual drive, I think it's better to control throttle according to the road condition. If in the curve, the target speed should be decreased so that need to control throttle according to steering angle or CTE value.
