//Coded this with help from Lesson here: https://www.youtube.com/watch?v=OsMoowoB2Rg&t=1008s
//Make sure that Adafruit GPS library is installed for this to work

#include <Adafruit_GPS.h> 
#include <SoftwareSerial.h> 
SoftwareSerial mySerial(3, 2); //GPS in pins 2 and 3
Adafruit_GPS GPS(&mySerial); //Create GPS object

String NMEA1;  //variable for first NMEA sentence
String NMEA2;  //variable for second NMEA sentence
char c;       //read the characters spewing from the GPS module

void setup()  
{
  Serial.begin(115200);  //Turn on the Serial Monitor
  GPS.begin(9600);       //Turn GPS on at baud rate of 9600
  GPS.sendCommand("$PGCMD,33,0*6D"); // Turn Off GPS Antenna Update
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); //Tell GPS we want only $GPRMC and $GPGGA NMEA sentences
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  delay(1000);  //Pause
}


void loop()                     // run over and over again
{
readGPS();  //This is a function we define below which reads two NMEA sentences from GPS
delay(12);  //Just keeps everything in line.
}

void readGPS(){  
  //This function will read and remember two NMEA sentences from GPS
  clearGPS(); //Serial port probably has old or corrupt data, so begin by clearing it all out
  
  while(!GPS.newNMEAreceived()) { 
    //Keep reading characters in this loop until a good NMEA sentence is received
  c=GPS.read(); //read a character from the GPS
  }
GPS.parse(GPS.lastNMEA()); //Once you get a good NMEA, parse it
NMEA1=GPS.lastNMEA();      //Once parsed, save NMEA sentence into NMEA1

  while(!GPS.newNMEAreceived()) {  
  //Go out and get the second NMEA sentence, should be different type than the first one read above.
  c=GPS.read();
  }
GPS.parse(GPS.lastNMEA());
NMEA2=GPS.lastNMEA();
  //dont do anything before this, because otherwise you'll get inaccurate data points, since data is always flowing.
  //Now we can start reading and doing other stuff:
  Serial.println(NMEA1);
  Serial.println(NMEA2);
  Serial.println("");
}


void clearGPS() {  
  //Clear old and corrupt data from serial port
  //Since between GPS reads, we still have data streaming in, we need to clear the old data by reading a few sentences, and discarding these
while(!GPS.newNMEAreceived()) {
  c=GPS.read();
  }
GPS.parse(GPS.lastNMEA());
while(!GPS.newNMEAreceived()) {
  c=GPS.read();
  }
GPS.parse(GPS.lastNMEA());

}
