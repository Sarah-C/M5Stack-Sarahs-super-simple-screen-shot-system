# M5Stack-Sarahs-super-simple-screen-shot-system

This is a very lightweight solution for making screenshots - if you're already using Serial.print, and the Arduino IDE.

Copy the **void takeScreenshot565(void){}** function into your code.

Then add **takeScreenshot565();** to your code where you want the screenshot producing.
Compile and run your program.

The function will output a 240 line hex block to the Serial Monitor of the Arduino IDE, for each of the **takeScreenshot565();** calls.

Copy **just the hex block** into the following webpage:
https://cdpn.io/SarahC/debug/oNWqKQa/bZAQWKmnQoOM

The webpage is also included in the project folder if it's down on Codepen for whatever reason.
When the picture is made, you can right click (in the Chrome browser), and "Save img as..." to download the image.


**takeScreenshot888();** produces the SAME results as the 565 bit version, but may be useful if you want to paste the 888 RGB to some other program.

