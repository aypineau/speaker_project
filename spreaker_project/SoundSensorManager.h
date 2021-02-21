/////////////////////////// Sound sensor manager //////////////////////////////////
#include <math.h>

#define PIN_SENSOR_OUT A7 // pin A7 Arduino Nano Every

#define MEAN_VALUES_RANGE 10
#define MIN_MAX_VALUES_RANGE 500

#define showSoundSensorConsole false
#define showSoundSensorConsoleDetail false

class SoundSensor{

  private:
    // Define two counter for homogeneous scale transition
    int maxValue[2] = {0,0};
    int minValue[2] = {1024,1024};
    int getCount[2] = {0, MIN_MAX_VALUES_RANGE/2};
  
  public:
    void init(){
    
      pinMode(PIN_SENSOR_OUT, INPUT);
    
    }
    
    int getValue(){
    
      if (getCount[0] >= MIN_MAX_VALUES_RANGE){
        // Reset values
        getCount[0] = 0;
        maxValue[0] = 0;
        minValue[0] = 0;
      }

      if (getCount[1] >= MIN_MAX_VALUES_RANGE){
        // Reset values
        getCount[1] = 0;
        maxValue[1] = 0;
        minValue[1] = 0;
      }
    
      int sumValues =0 ;
      for (int values = 0 ; values <= MEAN_VALUES_RANGE ; values++){
        
        if (showSoundSensorConsoleDetail) {
          Serial.print("Sound sensor value unit : ");
          Serial.println(analogRead(PIN_SENSOR_OUT));
        }
        
        sumValues += analogRead(PIN_SENSOR_OUT);
      }

      // clac mean for values getted
      int meanValue = ceil(sumValues / MEAN_VALUES_RANGE);

      // Refresh min and max
      if (meanValue > maxValue[0] ){
        maxValue[0] = meanValue;
      }
      if (meanValue > maxValue[1] ){
        maxValue[1] = meanValue;
      }
      if (meanValue < minValue[0]){
        minValue[0] = meanValue;
      }
      if (meanValue < minValue[1]){
        minValue[1] = meanValue;
      }

      // for debug
      if (showSoundSensorConsole) {
        Serial.print("Sound sensor meanValue : ");
        Serial.println(meanValue);
        Serial.print("Sound sensor maxValue : ");
        Serial.println(ceil((maxValue[0]+maxValue[1])/2));
        Serial.print("Sound sensor minValue : ");
        Serial.println(ceil((minValue[0]+minValue[1])/2));
      }
      
      return meanValue;
    }

    int getMaxValue(){
      return ceil((maxValue[0]+maxValue[1])/2);
    }

    int getMinValue(){
      return ceil((minValue[0]+minValue[1])/2);
    }

};
