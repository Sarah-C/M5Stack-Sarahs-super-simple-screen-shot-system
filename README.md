# M5Stack-Sarahs-super-simple-screen-shot-system

This is a very lightweight solution for making screenshots - if you're already using Serial.print, and the Arduino IDE.

Add **takeScreenshot565();** to your code where you want the screenshot producing.
Compile and run your program.

The function will output a 240 line hex block to the Serial Monitor of the Arduino IDE.

Copy **just the hex block** into the following webpage:
https://cdpn.io/SarahC/debug/oNWqKQa/bZAQWKmnQoOM

The webpage is also included in the project folder if it's down on Codepen for whatever reason.
When the picture is made, you can right click (in the Chrome browser), and "Save img as..." to download the image.

