// CONNECTIONS:
// DS1307 SDA --> SDA
// DS1307 SCL --> SCL
// DS1307 VCC --> 5v
// DS1307 GND --> GND

#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS1307.h>
RtcDS1307<TwoWire> Rtc(Wire);

#define countof(a) (sizeof(a) / sizeof(a[0]))

void RTC_setup(){
  //--------RTC SETUP ------------
  
  Rtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  
  if (!Rtc.IsDateTimeValid()){
    if (Rtc.LastError() == 0){
      // Common Causes:
      //    1) first time you ran and the device wasn't running yet
      //    2) the battery on the device is low or even missing
  
      // following line sets the RTC to the date & time this sketch was compiled
      // it will also reset the valid flag internally unless the Rtc device is
      // having an issue
  
      Rtc.SetDateTime(compiled);
    }
  }
  
  if (!Rtc.GetIsRunning()){
      Rtc.SetIsRunning(true);
  }
  
  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled){
      Rtc.SetDateTime(compiled);
  }
  
  // never assume the Rtc was last configured by you, so
  // just clear them to your needed state
  Rtc.SetSquareWavePin(DS1307SquareWaveOut_Low); 
}

String RTC_getHour(){
  RtcDateTime now = Rtc.GetDateTime();
  
  char datestring[3];

  snprintf_P(datestring, 
          countof(datestring),
          PSTR("%02u"),          
          now.Hour());
          
  return datestring;
}

uint8_t RTC_getHourInt(){
  RtcDateTime now = Rtc.GetDateTime();

  return now.Hour();
}

uint8_t RTC_getMin(){
  RtcDateTime now = Rtc.GetDateTime();
          
  return now.Minute();
}

String RTC_getDate(){
  RtcDateTime now = Rtc.GetDateTime();

  char datestring[16];

  snprintf_P(datestring, 
          countof(datestring),
          PSTR("%02u/%02u/%04u"),
          now.Month(),
          now.Day(),
          now.Year() );
  return(datestring);
}

String RTC_getTime(){
  RtcDateTime now = Rtc.GetDateTime();

  char datestring[20];

  snprintf_P(datestring, 
          countof(datestring),
          PSTR("%02u:%02u:%02u"),
          now.Hour(),
          now.Minute(),
          now.Second() );
  return(datestring);
}

String RTC_getDateTime(){
  RtcDateTime now = Rtc.GetDateTime();

  char datestring[20];

  snprintf_P(datestring, 
          countof(datestring),
          PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
          now.Month(),
          now.Day(),
          now.Year(),
          now.Hour(),
          now.Minute(),
          now.Second() );
  return(datestring);
}
