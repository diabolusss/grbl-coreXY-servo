# Update Summary for v0.9j
```
Restore EEPROM feature: A new set of restore EEPROM features to help OEMs and users reset their Grbl installation to the build defaults. See Configuring Grbl Wiki for details.
More configuration options for input pins
Bug fixes including: Soft limit error handling, disable spindle when S0, g-code reporting of G38.x.
```

# Update Summary for v0.9i
```
IMPORTANT:
Homing cycle updated. Locates based on trigger point, rather than release point.
System tweaks: $14 cycle auto-start has been removed. No more QUEUE state.
New G-Codes
CoreXY Support
Safety Door Support
Full Limit and Control Pin Configurability
Additional Compile-Time Feature Options
```

# grbl-coreXY-servo

Visit My Project DIY Guide Page : http://www.arnabkumardas.com

THIS IS BASED UPON https://github.com/robottini/grbl-servo and http://github.com/grbl/grbl

grbl 0.9i with Servo motor and Core[X,Y] Configuration of Motion Control 

Use the PIN D11 to drive the servo. 
Use the commands M03 Sxxx (xxx between 0 and 255) to rotate the servo between 0-180.
The command M05 turn the servo to zero degrees.

you can change the pulse duration in the file spindle_control.c:

define RC_SERVO_SHORT     15       // Timer ticks for 0.6ms pulse duration  (9 for 0.6ms)

define RC_SERVO_LONG      32       // Timer ticks for 2.5 ms pulse duration  (39 for 2.5ms)     

define RC_SERVO_INVERT     1     // Uncomment to invert servo direction

If you want to have the servo working from 0 --> 180 degrees change RC_SERVO_SHORT and put 9, RC_SERVO_LONG and put 39
If you want invert the servo direction uncomment the line above.

I tested the code very well with Atmega328p (Arduino Uno).

-------------------------------------------------------------------

The link for GRBL vanilla is: http://github.com/grbl/grbl

Grbl is a no-compromise, high performance, low cost alternative to parallel-port-based motion control for CNC milling. It will run on a vanilla Arduino (Duemillanove/Uno) as long as it sports an Atmega 328.

The controller is written in highly optimized C utilizing every clever feature of the AVR-chips to achieve precise timing and asynchronous operation. It is able to maintain up to 30kHz of stable, jitter free control pulses.

It accepts standards-compliant g-code and has been tested with the output of several CAM tools with no problems. Arcs, circles and helical motion are fully supported, as well as, all other primary g-code commands. Macro functions, variables, and most canned cycles are not supported, but we think GUIs can do a much better job at translating them into straight g-code anyhow.

Grbl includes full acceleration management with look ahead. That means the controller will look up to 18 motions into the future and plan its velocities ahead to deliver smooth acceleration and jerk-free cornering.

Licensing: Grbl is free software, released under the GPLv3 license.

For more information and help, check out our Wiki pages! If you find that the information is out-dated, please to help us keep it updated by editing it or notifying our community! Thanks!

Lead Developer [2011 - Current]: Sungeun(Sonny) K. Jeon, Ph.D. (USA) aka @chamnit

Lead Developer [2009 - 2011]: Simen Svale Skogsrud (Norway). aka The Originator/Creator/Pioneer/Father of Grbl.

The link for GRBL vanilla is: http://github.com/grbl/grbl
