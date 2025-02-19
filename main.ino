#include <WiFi.h>
#include <Espalexa.h>

// prototypes
boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);
void SecondLightChanged(uint8_t brightness);
void MotorChanged(uint8_t brightness);

// Change this!!
const char* ssid = "TANIGUCHI";
const char* password = "2046TANI1221";

boolean wifiConnected = false;

Espalexa espalexa;

// PIN Setting
const int LED_BLUE = 25;
const int LED_WHITE = 26;
const int LED_RED = 27;
const int PIN_MT_DIR = 14;
const int PIN_MT_STEP = 12;

// 
byte MOT_STEP;
byte MOT_RUN;




void setup()
{
  Serial.begin(115200);

  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, LOW);
  pinMode(LED_WHITE, OUTPUT);
  digitalWrite(LED_WHITE, LOW);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, LOW);
  pinMode( PIN_MT_DIR, OUTPUT );
  pinMode( PIN_MT_STEP, OUTPUT );
  MOT_STEP=0;
  MOT_RUN=0;
  
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    
    // Define your devices here. 
    espalexa.addDevice("LED1", firstLightChanged,0); //simplest definition, default state off
    espalexa.addDevice("LED2", SecondLightChanged); //simplest definition, default state off
    espalexa.addDevice("MT1", MotorChanged); //simplest definition, default state off

    espalexa.begin();
    
  } else
  {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}
 
void loop()
{

   espalexa.loop();
  if ( MOT_RUN ){
    if ( MOT_STEP ){
      MOT_STEP=false;
      digitalWrite( PIN_MT_STEP, HIGH );
    }else{
      MOT_STEP=true;
      digitalWrite( PIN_MT_STEP, LOW );
    }
  }
   delay(1);
}

//our callback functions
void firstLightChanged(uint8_t brightness) {
    Serial.print("Device 1 changed to ");
    
    //do what you need to do here
    showLED( brightness );

    //EXAMPLE
    if (brightness) {
      Serial.print("ON, brightness ");
      Serial.print(brightness);
    }
    else  {
      Serial.println("OFF");
    }
}

void SecondLightChanged(uint8_t brightness) {
    Serial.print("Device 2 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      digitalWrite(LED_WHITE, HIGH);
      Serial.print("ON, brightness ");
      Serial.print(brightness);
    }
    else  {
      digitalWrite(LED_WHITE, LOW);
      Serial.println("OFF");
    }
}

void MotorChanged(uint8_t brightness) {
  MOT_RUN=brightness;
}


// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state){
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}

void showLED( int value )
{
  if( value == 0 )
  {

      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_WHITE, LOW);
      digitalWrite(LED_RED, LOW);
 
      return;
  }
  
  int num = (value-3)/63;
  switch( num ){
    case 0 :
 
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_WHITE, LOW);

      break;
            
    case 1 :

      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_WHITE, LOW);

      break;
            
    case 2 :
 
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_BLUE, HIGH);
      digitalWrite(LED_WHITE, LOW);

      break;
            
    case 3 :
 
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_BLUE, HIGH);
      digitalWrite(LED_WHITE, HIGH);

      break;
            
    case 4 :

      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_BLUE, HIGH);
      digitalWrite(LED_WHITE, HIGH);
 
      break;

    default :
 
      digitalWrite(LED_BLUE, LOW);

      break;
  }
  return;
}
