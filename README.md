# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

--- 

## Objective 

To run a PID controller which would drive through the [simulator](https://github.com/udacity/self-driving-car-sim/releases) provided by [Udacity](www.udacity.com). 

## Description of Project 

We must initiate a PID controller which would respond to speed and throttle and drive the car which is safe for a human to sit in. 

## Parameters 

In this project we look at the three term controllers , Namely Proportional , Integral , Derivative. PID Controller is short for Proprotional - Intergral - Derivative Controller. Each parameter has an effect on the way car drives. 

PID controller continuously calculates an error value **e(t)** as the difference between a desired setpoint (SP) and a measured process variable (PV) and applies a correction based on proportional, integral, and derivative terms (denoted P, I, and D respectively) which give the controller its name. 

![PID Controller](https://upload.wikimedia.org/wikipedia/commons/4/43/PID_en.svg) 

Let's take a look at each parameters and it's affect on the way our car drives in simulator. 

### P - Proportional 

P - is an important parameter. It basically helps steering the car , much intuitively it uses cross track error and guides the car to the center of the road. So if your car goes on to the left side of the road somewhere close to the outer road it would help the car steer right and come back on track. P ( Proportional) helps in the movement of the car in proportion to CTE. Let's take a look at this screenshot below , 

![P set , I and D as zero](https://raw.githubusercontent.com/Shreyas3108/CarND-Term2-PID-Controller/master/Readme%20Support/p%20effect.png)

As you could see the car is off the track and is on the right hand side of the road , But it steers to the left to come back and is unable to do so because it needs the other two parameters. The car basically **overshoots** and goes out of the track ie , Moves left and right in haphazard manner. 

### D - Derivative 

D - Refers to derivative which basically helps us in predicting the future course action , much importantly it helps the car not overshoot. D helps in predicting the future state of the system based on the rate of change. It basically communicates when the error of the turn has decreased and in the long run helps the car steer through the trajectory. 

The individual effect of D is minimal and when other parameters are set to 0. The car moves in a straight line and runs out of the track as seen below. 
![P and I as zero](https://raw.githubusercontent.com/Shreyas3108/CarND-Term2-PID-Controller/master/Readme%20Support/d%20effect.png)
 
D parameter will cause the car to approach the center line smoothly without steering haphazardly. 

`d_error = cte - prev_error` 

### I - Integral 

I  refers to integral , Which basically refers to integral to face to biases faced during the execution run. I value increases over time mostly the role of I is to compensate what P couldn't do , which basically means that when the error value is small the P component has tough time detecting it. In these cases I value accumulate the error and helps the car stay on track. The accumilated error is then added up. 

The individual affect of I is that when it is initalized the car goes straight and starts going around in circle. It does look cool though but in real life it can cause some trouble. 

`i_error +=cte ` 

![I initialized with other not](https://raw.githubusercontent.com/Shreyas3108/CarND-Term2-PID-Controller/master/Readme%20Support/i%20effect.png) 

### PID as a whole 

Now , as seen above all the three seem to not work individually and for this case we combine all the three and we get a car which runs on the track and calculates the error and steers well to stay in the confinement of the road. 

![PID](https://raw.githubusercontent.com/Shreyas3108/CarND-Term2-PID-Controller/master/Readme%20Support/pid%20full.png) 

PID as a whole is `-Kp * CTE (Proportional) - Kd * d/dt(CTE) (Derivative) - Ki * sum(CTE) (Integral) ` 

## Choosing the Parameters 

I manually chose the parameters , for this i reffered to Mr.David Silver's [video](https://www.youtube.com/watch?v=YamBuzDjrs8&feature=youtu.be) and coded the initialization function into (argv[i]) (i = 1 for P , 2 for I , 3 for D value) 

I first started off with 0.5 for P , 2.0 for D and 0.01 for I which seem to run well until the first curve where it faced issues and went out. The changes continued on until i ended up 0.4 , 0.04 and 4.0. Then i used the parameters which seem to do well but had troubles in the latter part of the lap. The problem was that the car ended up steering a lot probably overshooting which led to my belief that the P and I parameters have to be changed and i did that and finally ran it on 0.25 , 0.004 and 3.0 which seem to be fine but car wasn't turning a lot and in few places it would seem as if the car had sharp curves which further led to my belief that I was fine and P had to be increased so i finally settled with 0.3 , 0.004 and 3.0 as final parameters ( I also took help from slack and other students for this ) 

I wasn't particularly sure about Speed and throttle and wanted to focus on the basic aspects hence i didn't change anything there. also , Speed thrills but kills! 


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

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

