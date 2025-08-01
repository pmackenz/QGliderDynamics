# QGliderDynamics
Visualization of Paraglider behavior in wind **for education** (not in-flight)

## Features
* Adjustable glider speed (trim - slow - accelerated)
* Adjustable glider orientation (shows info on compass orientation based on wheeled input)
* Adjustable wind speed
* Adjustable wind direction (shows info on compass orientation based on wheeled input)
* Visualized glide path for given wind and glider orientation
* Vusualizes actual glide ratio (reach) based on given wind and glider orientation

## Exercises
1. No wind: set wind speed to 0.0 and observe glider path (red) as you change the orientation of the glider.
2. Align the orientation of glider and wind. Increase the wind speed to studdy the effect of tail wind on glider speed and glide ratio.
3. Repead 2. with wind and glider in oposing directions. Observe reduction in glide ratio/reach as wind speed increases.
4. Turn wind to any direction and adjust glider orientation until the glider moves in a desired direction (red arrows).  Observe that the glider is **not** oriented in the actual flight direction if wind is present.  Further observe the change in glide ratio/reach as the wind direction changes.  The effect is stronger as wind speed increases.

All exercises allow the student to explore the needed changes to any given wind input.

## How to Compile?

1. Download QCUstomPlot from https://www.qcustomplot.com/. 
   
   * This source code has been tested with QCP version 2.1.1 and we recommend to start with that version.
   * Expand the source code and place it into a folder `QGliderDynamics/qcp`. You need to install at least the files `qcustomplot.h` and `qcustonplot.cpp`.
   
2. Open the project file in Qt Creator and use a suitable build configuration.
   * This code was tested on `Qt 6.5.3` but should compile on any `Qt 6.x.x` 
   

