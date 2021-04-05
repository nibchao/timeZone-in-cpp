# timeZone-in-cpp
This is my take on what I originally planned to create in Java, but in C++. In the future, I hope to convert the program to Java and figure out how to use and incorporate a GUI to replace the menu of options in the command prompt window.

This is a simple program with one main goal in mind - allowing the user to input a time in one time zone and convert said time into another time zone.

An idea I can look into adding is getting the local time of the computer and being able to use it in the various functions without having to manually store it first. 
Another idea is being able to save a "profile" that can be loaded up and contain a "main time" that can be mass converted into a preset of time zones. This "profile" idea comes from watching streamers on Twitch who upload their streaming schedules and typically mass convert their local time zone into the general time zones of their viewer base.

EDIT: After a few months of not working on this project then coming back to it, something that was very clunky and awkward was the process of testing if the time converting functions worked - an idea I thought of that could simplify this process would be adding a sort of "menu" where the user can, for example, enter '1' to select the first time saved instead of having to manually enter the hours, minutes, meridiem (if on 12-hour clock), zone abbreviation (and full zone name if the stored time zone is a duplicate time zone abbreviation case). This "menu" idea could also be re-used for when the user wants to convert a time zone to another time zone that is a duplicate time zone abbreviation case in which the menu would display the full zone name for each duplicate time zone option. While this idea would be helpful in improving the program, I am currently unsure of how to implement this in code.
