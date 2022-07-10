# TLE data based satellite tracker for Arduino Nano mit MS Code PlattformIO

Basierend auf:
* PLAN-13 Library von DL9SEC (based on G3RUH) https://github.com/dl9sec/AioP13
* Anwendungsbeispiel von 
https://create.arduino.cc/projecthub/tnowroz/3d-printed-real-time-satellite-orbit-follower-tracker-w-5ef735


"Time" and "Servo" libs können über den PlattformIO Library Manager installiert werden.<br>
Suchbegriff "Michael Margolis".
<br>

Demonstriert die Berechnung von 
* Azimut und Elevation 
* der ISS 
* auf der Basis von TLE Daten 
* und dem Beobachterstandort 
* zu einer bestimmten Zeit.
<br>
<br>

Die TLE Daten für die ISS (CATNR=25544) können geladen werden mit:<br>
https://celestrak.org/NORAD/elements/gp.php?CATNR=25544
<br>
Der Arduino Nano hat keine Echtzeituhr!
<br><br>
Eine andere Methode zur Berechung der Satelliten ist<br>
https://github.com/sparkfun/SparkFun_SGP4_Arduino_Library<br>
Die lib ist aber für den Arduino Nano zu groß!<br>


Interessante Links:
* https://www.amsat.org/amsat/articles/g3ruh/111.html
* http://celestrak.org/NORAD/documentation/spacetrk.pdf

<br>
TODO:<br>
Die Servoansteuerung wurde noch nicht getestet.
<br>
LIZENZ: Es gelten die Lizenen der verwendeten Projekte