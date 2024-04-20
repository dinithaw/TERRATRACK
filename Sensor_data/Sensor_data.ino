/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
//-----------------------------------------------------------------------
/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPL6G0MZDy9T"
#define BLYNK_TEMPLATE_NAME "arduno gsm"
#define BLYNK_AUTH_TOKEN "QClGORaxjEV6RvLnIcy-EGJ3UpwpV1ME"
//-----------------------------------------------------------------------
// Select your modem:
#define TINY_GSM_MODEM_SIM800
//-----------------------------------------------------------------------
// Default heartbeat interval for GSM is 60
// If you want override this value, uncomment and set this option:
//#define BLYNK_HEARTBEAT 30
//-----------------------------------------------------------------------
#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>
//-----------------------------------------------------------------------
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;
//-----------------------------------------------------------------------
// Your GPRS credentials
// Leave empty, if missing user or pass
char apn[]  = "dialogbb";
char user[] = "";
char passw[] = "";
//-----------------------------------------------------------------------
// Hardware Serial on Mega, Leonardo, Micro
//#define SerialAT Serial3
//-----------------------------------------------------------------------
// or Software Serial on Uno, Nano
#include <SoftwareSerial.h>
SoftwareSerial SerialAT(12, 11); // RX, TX
TinyGsm modem(SerialAT);
//-----------------------------------------------------------------------
#include <DHT.h>
#define DHT11_PIN A3
#define DHTTYPE DHT11
DHT dht(DHT11_PIN, DHTTYPE);
//-----------------------------------------------------------------------
BlynkTimer timer;
#define INTERVAL 500L
//-----------------------------------------------------------------------



/************************************************************************************
 *  This function sends Arduino's up time every second to Virtual Pin.
 *  In the app, Widget's reading frequency should be set to PUSH. This means
 *  that you define how often to send data to Blynk App.
 **********************************************************************************/
void SendData()
{
  //-----------------------------------------------------------------------
  float a = analogRead(A0);
  a = map(a, 0, 1023, 0, 100);
  //-----------------------------------------------------------------------
  float s = analogRead(A1);
  s = map(s, 0, 1023, 0, 100);
  //-----------------------------------------------------------------------
  float l = analogRead(A2); //read ldr data
  l = map(l, 0, 1023, 0, 100);
  //-----------------------------------------------------------------------
  //Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  //-----------------------------------------------------------------------
  //Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  //-----------------------------------------------------------------------
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  //-----------------------------------------------------------------------
  //Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  //-----------------------------------------------------------------------
  Serial.print("Temperature: ");
  Serial.println(t);
  Serial.print("Humidity: ");
  Serial.println(h);
  Serial.print("Light: ");
  Serial.println(l);
  Serial.print("Air Quality: ");
  Serial.println(a);
  Serial.print("Soil Moisture: ");
  Serial.println(s);
  Serial.println("------------------------------------------");
  //-----------------------------------------------------------------------
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, a);
  Blynk.virtualWrite(V3, l);
  Blynk.virtualWrite(V4, s);
  //-----------------------------------------------------------------------
}


/************************************************************************************
 *  setup() function
 **********************************************************************************/
void setup()
{
  //-----------------------------------------------------------
  // Debug console
  Serial.begin(115200);
  delay(10);
  //-----------------------------------------------------------
  // Set GSM module baud rate
  SerialAT.begin(9600);
  //SerialAT.begin(9600,SWSERIAL_8N1,D3,D4);
  delay(3000);
  //-----------------------------------------------------------
  dht.begin();
  //-----------------------------------------------------------
  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  Serial.println("Initializing modem...");
  modem.restart();
  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");
  //-----------------------------------------------------------
  //Blynk.begin(auth, modem, apn, user, pass);
  Blynk.begin(auth, modem, apn, user, passw);
  //-----------------------------------------------------------
  // Setup a function to be called every second
  timer.setInterval(INTERVAL, SendData);
  //-----------------------------------------------------------  
}


/************************************************************************************
 *  loop() function
 **********************************************************************************/
void loop()
{
  Blynk.run();
  timer.run();
}
