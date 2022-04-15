import processing.net.*; 
import processing.serial.*;

Server s;
Client c;
String input;
int data[];
Timer timer;
Timer timerNext;

int numPorts=0;  // the number of serial ports in use
int maxPorts=24; // maximum number of serial ports
int currentPattern = 1;
int currentSpeed = 100;
int currentBright = 200;
int maxInstruction =8;
int patternLength[] = {240,240,240,240,240,240,240,240};

Serial[] ledSerial = new Serial[maxPorts];     // each port's actual Serial port

int foundSerials = 0;
int errorCount=0;

void setup() 
{
  String[] list = Serial.list();
  foundSerials = list.length;
  delay(20);
  println("Serial Ports List : ");
  println(Serial.list());
  if (errorCount > 0) exit();
  ///dev/serial1 /dev/ttyACM0 /dev/ttyAMA0
  for(String serial : Serial.list()){   
    if(serial.startsWith("COM9")){ //  if(serial.startsWith("/dev/")){
      serialConfigure(serial);
    }
  }
  //serialConfigure("/dev/ttyACM1");
   
  timer = new Timer(1);
  timerNext = new Timer(1);
  size(600, 600);
  background(204);
  stroke(0);
  frameRate(5); // Slow it down a little
  s = new Server(this, 8080); // Start a simple server on a port
}

// movieEvent runs for each new frame of movie data
void ledWriteEvent() {

  String padPattern = (String.format("%1$" + 3 + "s", currentPattern).replace(' ', '0'));
  String padBright = (String.format("%1$" + 3 + "s", currentBright).replace(' ', '0'));
  String padSpeed = (String.format("%1$" + 3 + "s", currentSpeed).replace(' ', '0'));

  String ledData = "{"+padPattern +" "+padBright+" "+padSpeed+"}";
  println(ledData);
  println(numPorts);
  for (int i=0; i < numPorts; i++) {    
    // send the raw data to the LEDs  <span class="Emoticon Emoticon1"><span>:-)</span></span>
    ledSerial[i].write(ledData); 
  }
   println("done writing");
}

// ask a Teensy board for its LED configuration, and set up the info for it.
void serialConfigure(String portName) {
 Serial newSerial = null;
 println("serialConfigure");
  try {
    newSerial = new Serial(this, portName,9600);
    //ledSerial[numPorts] = new Serial(this, portName,9600);
    //if (lnewSerial == null) throw new NullPointerException();
    newSerial.write('?');
  } catch (Throwable e) {
    println(e);
    println("Serial port " + portName + " does not exist or is non-functional");
    errorCount++;
    return;
  }
   println("delay");
  delay(500);
  println("delay over");
  String line = newSerial.readStringUntil(10);
  println("delay over");
  if (line == null) {
    newSerial.write('?');
    line = newSerial.readStringUntil(10);
    if (line == null) {
      println("Serial port " + portName + " is not responding.");
      println("Is it really a Teensy 3.2 running VideoDisplay?");
      errorCount++;
      return;
    }
  }
   println("here");
  String param[] = line.split(",");
  if (param.length != 12) {
    println("----"+line);
    println("Error: port " + portName + " did not respond to LED config query"+param.length);
    errorCount++;
    return;
  }
  ledSerial[numPorts]  = newSerial;
  println(ledSerial[numPorts]);
   println("----"+line);
  println("we got teensy on " + portName + "");
  numPorts++;
}

void draw() 
{
  background(200);
  timer.countUp();
  timerNext.countUp();
  fill(0);
  float currentTime = timer.getTime();
  float currentNextTime = timerNext.getTime();

  if(currentTime > 1){   
     println(currentTime);
   //  println(currentNextTime);
     String[] list = Serial.list();
     println("");
     print("Existing Serials:");
     print(foundSerials);
     print(" New Serials:");
     println(list.length);
     if(foundSerials < list.length){
        for (int i=0; i < numPorts; i++) {   
            ledSerial[i].clear();
            ledSerial[i].stop();
        }
        numPorts =0;
      }
      if(foundSerials != list.length){
      //  println(list);
        println("Found new device");
        foundSerials = list.length;
        for(String serial : Serial.list()){
           //if(serial.startsWith("/dev/")){ //UNDO
              serialConfigure(serial);
           // }
          }
      }
     foundSerials = list.length;
     
     for (int i=0; i < numPorts; i++) {    
       // send the raw data to the LEDs  <span class="Emoticon Emoticon1"><span>:-)</span></span>
        println("---------");
        println(ledSerial[i]); 
        println("---------");
      }
    
      ledWriteEvent();
      timer.setTime(0);
  }  
 // println(currentPattern);
  if(currentPattern > 0 && currentPattern < patternLength.length && currentNextTime > patternLength[currentPattern-1]){
     println("PATTERN CHANGED"); 
     currentPattern+=1;
     if(currentPattern > maxInstruction){
       currentPattern = 1;
       ledWriteEvent();
      }else{
       ledWriteEvent();
      }
      timerNext.setTime(0);
  }

  // Receive data from client
  c = s.available();
  if (c != null) {
    input = c.readString();
  //  println(input);
   //  println(input);
      input = input.substring(input.indexOf("{"), input.indexOf("}")+1); // Only up to the newline
    println("---------------");
   // println(input.substring(1,input.length()-1));
    data = int(split(input.substring(1,input.length()-1), ' ')); // Split values into an array
    println(input);
    currentPattern = data[0];
    currentBright = data[1];
    currentSpeed = data[2];
    timer.setTime(0);
    timerNext.setTime(0);
    ledWriteEvent();
    // Draw line using received coords
    
    s.write(input.getBytes());
   // stroke(0);
   //line(data[0], data[1], data[2], data[3]);
   s.disconnect(c);
  
  }

}
