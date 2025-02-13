<h1 align="center" id="title">Grove Water Level Library</h1>

<p id="description">This tiny library is for reading the current level from the Grove Water Level Sensor. Please note that the code behind this library is from Seeed Studio - Grove Water Level Sensor. I've only put the code into a library to reduce code in my Arduino project, and now I would like to share this with you.

Note from me (the forker): I forked the original project because:

A: The example cannot be found under the Arduino IDE since there is none, except on the readme.<br>
B: I added 'readCM' because why not.<br>
C: The most important reason is that you cannot directly download the library under releases. The result is that you have to download (git clone) the project, then unzip it, go inside the folder, and zip it anew without the readme</p>

<h2>Project Screenshots:</h2>

<img src="https://i.imgur.com/tgtpJyg.jpg" alt="project-screenshot" width="400" height="600/">
<br>
<img src="https://i.imgur.com/fAqyEJw.png" alt="project-screenshot" width="800" height="600/">

  
<h2>🧐 Features</h2>

Here're some of the project's best features:

*   Getting the Data out of the Sensor without unnecessary complexity
*   Get Percentage
*   Get Centimetre

<h2>🛠️ Installation Steps:</h2>

<p>1. Go under Releases and download the waterlevelsensor.zip. Then include it in the Arduino IDE by hovering over Sketch -&gt; Include Library -&gt; Add .ZIP Library</p>

<p>2. Go under File -&gt; Examples -&gt; Grove_Water_Level_Sensor and upload the code or simply copy paste this code:</p>

```cpp
#include <waterlevelsensor.h>

WaterLevelSensor sensor = WaterLevelSensor();

void setup() {
  Serial.begin(9600);
}

void loop() {
  //lesen des Grove Wasser Level Sensors
  int waterLevel = sensor.readPercentage();
  int waterLevelinCM = sensor.readCM();

  //Ausgeben des ermittelten Wertes
  Serial.print(waterLevel);
  Serial.println("%");
  Serial.print(waterLevelinCM);
  Serial.println(" cm");
  Serial.println("--------------------------");
  
  delay(500);
}
```
