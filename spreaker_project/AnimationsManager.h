//////////////////////////// Animations ////////////////////////////////

#include "ln74hc595_controller.h"
#include "SoundSensorManager.h"
#include <stdlib.h> // For rand() and malloc()
#include <math.h>

#define showAnimationConsole false


class AnimationsManager{

  private:
    //How many shift register
    int numOfLed;
    int numOfRows;
    int maxNumOfLedPerRow;
    int* tabNumLedPerRow = (int*) malloc(255 * sizeof(int));
    SoundSensor soundSensor;

  public:
    AnimationsManager(){}

    void init( int numOfLed, int numOfRows, int* tabNumLedPerRow){
  
      this->numOfLed = numOfLed;
      this->numOfRows = numOfRows;
      this->tabNumLedPerRow = tabNumLedPerRow;
       
      for (int i = 0; i < numOfRows; i++) {
        this->tabNumLedPerRow[i] = tabNumLedPerRow[i];
      }

      //if (tabNumLedPerRow == -1){exit;}
  
      //free(tabNumLedPerRow);
       
      initPin74hc595();
  
      //reset all register pins
      clearRegisters(this->numOfLed);
      
      maxNumOfLedPerRow=0;
      // find the max number of led in array tabNumLedPerRow
      for (int index =0; index<numOfRows; index++){
        if (maxNumOfLedPerRow < tabNumLedPerRow[index] ){
          maxNumOfLedPerRow = tabNumLedPerRow[index];
        }
      }

      soundSensor.init();
   }

  void allLedAnim( bool ledState, int timeToWait){
    // Create an array with boolean, size of pin of 74hc595
    bool registers[numOfLed] = { ledState };
  
    // for each led
    for (int led = 0; led <= numOfLed; led++)
    {
        registers[led] = !ledState;
    }
    // display led panel 
    writeRegisters(numOfLed, registers, timeToWait);
  }
  
  
  
  void ledPerLedAnim( bool ledState, int timeToWait){
    // Create an array with boolean, size of pin of 74hc595
    bool registers[numOfLed];
    // Initializing register array
    for (int i = 0; i < numOfLed; ++i){
        registers[i] = ledState;
    }

    // for each led
    for (int led = 0; led <= numOfLed; led++)
    {
        registers[led] = !registers[led];
      
        // display led panel 
        writeRegisters(numOfLed, registers, timeToWait/(numOfLed*20));
    }
  }
  
  
  void rowPerRowAnim(bool ledState, int timeToWait){
    // Create an array with boolean, size of pin of 74hc595
    bool registers[numOfLed];
    // Initializing register array
    for (int i = 0; i < numOfLed; ++i){
        registers[i] = ledState;
    }
      
    // counter to memorize number of LED updated 
    int ledCount = 0 ;
    
    // For each row
    for (int row = 0; row < numOfRows; row++){
    
      ledCount += tabNumLedPerRow[row];
    
      // Update all LED
      for (int led = 0; led <= numOfLed; led++){
        if ( led < ledCount){
          registers[led] = !ledState; 
        }
      }
    
      // display led panel 
      writeRegisters(numOfLed, registers, timeToWait/numOfRows);  
    }
  }
  
  
  
  
  void waveAnim(bool ledState, int timeToWait){
    // Create an array with boolean, size of pin of 74hc595
    bool registers[numOfLed];
    // Initializing register array
    for (int i = 0; i < numOfLed; ++i){
        registers[i] = ledState;
    }
    
    // counter to memorize number of LED updated 
    int waveHeight = 4;
    
    
    for (int waveRowPosition = 0 ; waveRowPosition <= numOfRows + 2* waveHeight ; waveRowPosition++){
    
      int topWave = 0;
      int bottomWave = 0;
      
      for (int row = 0 ;  row <= numOfRows + 2* waveHeight ; row++ ){
          if (row < waveRowPosition && row < numOfRows){
            topWave += tabNumLedPerRow[row];
          } 
          if (row <= waveRowPosition - waveHeight  && row - waveHeight >= 0 ) {
            bottomWave += tabNumLedPerRow[row - waveHeight];
          }
      }
      
      for (int led = 0 ; led < numOfLed ; led++){
    
        if (led < topWave){
          registers[led] = !ledState; 
        }
        if (led < bottomWave){
          registers[led] = ledState; 
        }
      }
          
      // display led panel 
      writeRegisters(numOfLed, registers, timeToWait/numOfRows);
    
    }
  }
  
  void borderToCenterAnim(bool ledState, int timeToWait){
    // Create an array with boolean, size of pin of 74hc595
    bool registers[numOfLed];
    // Initializing register array
    for (int i = 0; i < numOfLed; ++i){
        registers[i] = ledState;
    }
    
    // numLedPerEdge is a border compose of led updated
    for (int numLedPerEdge = 0 ; numLedPerEdge < 3 ; numLedPerEdge++){
    
      int row = 0;
    
      // counter to memorize number of LED updated 
      int ledcount = 0 ;
    
      
      // Update all LED
      for (int row = 0; row < numOfRows; row++){
        if(row< numOfRows-1){
        
          for (int led = 0 ; led < tabNumLedPerRow[row] ; led++){
    
            if ((led <= numLedPerEdge || led >= tabNumLedPerRow[row] - numLedPerEdge -1 ) && tabNumLedPerRow[row] >= tabNumLedPerRow[row+1]  ){
              registers[ledcount] = !ledState; 
            } 
            
            ledcount++;
          }
        }
      }
      writeRegisters(numOfLed, registers, timeToWait / 3);
      
      row = 0;
      ledcount = 0 ;
      
      // Update all LED
      for (int row = 0; row < numOfRows; row++){
    
        for (int led = 0 ; led < tabNumLedPerRow[row] ; led++){
    
          if (led <= numLedPerEdge || led >= tabNumLedPerRow[row] - numLedPerEdge -1){
            registers[ledcount] = !ledState; 
          }
          ledcount++;
        }
      }
      writeRegisters(numOfLed, registers, timeToWait /3);
    }
  }
  
  
  
  void lineAnim(bool ledState, int timeToWait){
    // Create an array with boolean, size of pin of 74hc595
    bool registers[numOfLed];
    // Initializing register array
    for (int i = 0; i < numOfLed; ++i){
        registers[i] = ledState;
    }
    
    // numLedPerEdge is a border compose of led updated
    for (int numLedPerEdge = 0 ; numLedPerEdge < 3 ; numLedPerEdge++){
    
      int row = 0;
    
      // counter to memorize number of LED updated 
      int ledcount = 0 ;
    
      
      // Update all LED
      for (int row = 0; row < numOfRows; row++){
        if(row< numOfRows-1){
        
          for (int led = 0 ; led < tabNumLedPerRow[row] ; led++){
    
            if (led <= numLedPerEdge){
              registers[ledcount] = !ledState; 
            } 
            ledcount++;
          }
          // display led panel 
          writeRegisters(numOfLed, registers, timeToWait/(numOfLed*20));
    
        }
      }
      
      row = 0;
      ledcount = 0 ;
      
      // Update all LED
      for (int row = 0; row < numOfRows; row++){
    
        for (int led = 0 ; led < tabNumLedPerRow[row] ; led++){
    
          if (led <= numLedPerEdge || led >= tabNumLedPerRow[row] - numLedPerEdge -1){
            registers[ledcount] = !ledState; 
          } 
          ledcount++;
        }
        // display led panel 
        writeRegisters(numOfLed, registers, timeToWait/(numOfLed*10));
      
      }
    }
  }
  
  void levelAnim(){

    // Create an array with boolean, size of pin of 74hc595
    bool registers[numOfLed];
    
    // Initializing register array
    for (int i = 0; i < numOfLed; ++i){
        registers[i] = false;
    }

    int meanValueSensor = soundSensor.getValue();
    int minValueSensor = soundSensor.getMinValue();
    int maxValueSensor = soundSensor.getMaxValue();

    int ccScale = meanValueSensor - minValueSensor;
    int maxCcScale = maxValueSensor - minValueSensor;

    // prevent errors
    if (maxCcScale == 0){
      maxCcScale = 1024;
    }
    
    // counter to memorize number of LED updated 
    int topWave =  1 + ceil( (numOfRows -1) * ccScale / maxCcScale ); 

    if (showAnimationConsole){
      Serial.println("");
      Serial.print("meanValueSensor : ");
      Serial.println(meanValueSensor);
      Serial.print("minValueSensor : ");
      Serial.println(minValueSensor);
      Serial.print("maxValueSensor : ");
      Serial.println(maxValueSensor);
      Serial.print("ccScale : ");
      Serial.println(ccScale);
      Serial.print("maxCcScale : ");
      Serial.println(maxCcScale);
      Serial.print("100 * ccScale / maxCcScale : ");
      Serial.println(ceil( 100 * ccScale / maxCcScale));
      Serial.print("ceil( (numOfRows -1) * ccScale / maxCcScale) : ");
      Serial.println(ceil( (numOfRows -1) * ccScale / maxCcScale ));
      Serial.print("topWave : ");
      Serial.println(topWave);
    }

    for (int RowPosition = 0 ; RowPosition <= numOfRows ; RowPosition++){

      int onLedWave =0;
      
      for (int row = 0 ;  row < numOfRows; row++ ){
          if (row < topWave){
            onLedWave += tabNumLedPerRow[row];
          }
      }
      
      for (int led = 0 ; led < numOfLed ; led++){
        
        if (led < onLedWave){
          registers[led] = true; 
        }
      }
          
      // display led panel 
      writeRegisters(numOfLed, registers, 0);
    
    }
  }
};
