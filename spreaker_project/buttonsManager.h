//////////////////////// Buttons //////////////////////////////////
// Using glue routune for using attachInterrupt inside class


// PIN for reception button action
#define PIN_INTERRUPT_BUTTON_PREVIOUS 2     // pin D2 Arduino Nano Every
#define PIN_INTERRUPT_BUTTON_PLAY 3         // pin D3 Arduino Nano Every
#define PIN_INTERRUPT_BUTTON_NEXT 4         // pin D4 Arduino Nano Every
#define PIN_INTERRUPT_BUTTON_PREVIOUS_MODE 5    // pin D5 Arduino Nano Every
#define PIN_INTERRUPT_BUTTON_NEXT_MODE 6    // pin D6 Arduino Nano Every


// PIN for do action
#define PIN_ACTION_NEXT 7     // pin D2 Arduino Nano Every 
#define PIN_ACTION_PREVIOUS 8 // pin D3 Arduino Nano Every 
#define PIN_ACTION_PLAY 9     // pin D4 Arduino Nano Every 


class ButtonsManager{

  private:
    int *pmode = 0 ;
    int num_mode;

  public:
    void init(int num_mode , int *pmode){

      this->num_mode =num_mode;
      this->pmode = pmode;
      
      pinMode(PIN_INTERRUPT_BUTTON_NEXT, INPUT_PULLUP);
      pinMode(PIN_INTERRUPT_BUTTON_PREVIOUS, INPUT_PULLUP);
      pinMode(PIN_INTERRUPT_BUTTON_PLAY, INPUT_PULLUP);
      pinMode(PIN_INTERRUPT_BUTTON_NEXT_MODE, INPUT_PULLUP);
      pinMode(PIN_INTERRUPT_BUTTON_PREVIOUS_MODE, INPUT_PULLUP);
      pinMode(PIN_ACTION_NEXT, OUTPUT);
      pinMode(PIN_ACTION_PREVIOUS, OUTPUT);
      pinMode(PIN_ACTION_PLAY, OUTPUT);
      
      // Init state of actions pin
      digitalWrite(PIN_ACTION_NEXT, LOW); 
      digitalWrite(PIN_ACTION_PREVIOUS, LOW); 
      digitalWrite(PIN_ACTION_PLAY, LOW); 
    }
    
    void actionButtonNext(){ 
      if (digitalRead(PIN_INTERRUPT_BUTTON_NEXT) == LOW){
        digitalWrite(PIN_ACTION_NEXT, LOW);
      } else{
        digitalWrite(PIN_ACTION_NEXT, HIGH); 
      }
    }
    
    void actionButtonPrevious(){ 
      if (digitalRead(PIN_INTERRUPT_BUTTON_PREVIOUS) == LOW){
        digitalWrite(PIN_ACTION_PREVIOUS, LOW);
      } else{
        digitalWrite(PIN_ACTION_PREVIOUS, HIGH); 
      }      
    }
    
    void actionButtonPlay(){ 
      if (digitalRead(PIN_INTERRUPT_BUTTON_PLAY) == LOW){
        digitalWrite(PIN_ACTION_PLAY, LOW);
      } else{
        digitalWrite(PIN_ACTION_PLAY, HIGH); 
      } 
    }

    void actionButtonNextMode(){ 
      if (digitalRead(PIN_INTERRUPT_BUTTON_NEXT_MODE) == LOW){
        * pmode = (* pmode + 1 )%(num_mode-1);
      }
    }

    void actionButtonPreviousMode(){ 
      if (digitalRead(PIN_INTERRUPT_BUTTON_PREVIOUS_MODE) == LOW){
       * pmode = (* pmode - 1 );

       if (* pmode < 0 ){
        * pmode = num_mode -1;
       }
      }
    }

    // for get pin and use AttachInterupt in setup function

    int getPinButtonNext(){
      return PIN_INTERRUPT_BUTTON_NEXT;
    }
    
    int getPinButtonPrevious(){
      return PIN_INTERRUPT_BUTTON_PREVIOUS;
    }

    int getPinButtonPlay(){
      return PIN_INTERRUPT_BUTTON_PLAY;
    }

    int getPinButtonNextMode(){
      return PIN_INTERRUPT_BUTTON_NEXT_MODE;
    }

    int getPinButtonPreviousMode(){
      return PIN_INTERRUPT_BUTTON_PREVIOUS_MODE;
    }


};
