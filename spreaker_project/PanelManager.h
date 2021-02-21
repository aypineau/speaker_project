//////////////////////////////// Led panel //////////////////////////////////

#include "AnimationsManager.h"

#define NUM_OF_74HC959 10
#define NUM_REGISTER_PINS NUM_OF_74HC959 * 8
#define NUM_LED NUM_REGISTER_PINS - 1
#define NUM_ROWS 25
#define TAB_NUM_LED_PER_ROW {2, 4, 4, 6, 5, 4, 5, 4, 5, 4, 3, 4, 3, 4, 3, 2, 3, 2, 3, 2, 1, 2, 1, 2, 1}

class PanelManager{

  private:
  
    // Define state of all panel for adapt animation
    int tabNumLedPerRow[NUM_ROWS] = TAB_NUM_LED_PER_ROW;
    
    bool ledState = false;
    
    AnimationsManager anim;
  
  public:
    void init(){
      
      anim.init(NUM_LED, NUM_ROWS, this->tabNumLedPerRow);
    }

    void randomAnim(){
      // define a random value for animation time variation
      int timeToWait = 1000 + rand() % 800;

      // define a random number for select animation randomly
      int nAnimationSelected = rand() % 5;
      
      switch (nAnimationSelected) {
        case 0:
           anim.ledPerLedAnim(this->ledState, timeToWait);
           break;
        case 1:
           anim.rowPerRowAnim(this->ledState, timeToWait);
           break;
        case 2:
          anim.borderToCenterAnim(this->ledState, timeToWait);
          break;
        case 3:
          anim.lineAnim(this->ledState, timeToWait);
          break;
        case 4:
          anim.waveAnim(this->ledState, timeToWait);
          this->ledState = !this->ledState;
          break;
      }

      this->ledState = !this->ledState;
    }

    void ledPerLedAnim(){
      // define a random value for animation time variation
      int timeToWait = 1000 + rand() % 800;
      
      anim.ledPerLedAnim(this->ledState, timeToWait);
      
      this->ledState = !this->ledState;
    }

    void rowPerRowAnim(){
      // define a random value for animation time variation
      int timeToWait = 1000 + rand() % 800;
      
      anim.rowPerRowAnim(this->ledState, timeToWait);

      this->ledState = !this->ledState;
    }

    void borderToCenterAnim(){
      // define a random value for animation time variation
      int timeToWait = 1000 + rand() % 800;
      
      anim.borderToCenterAnim(this->ledState, timeToWait);
    
      this->ledState = !this->ledState;
    }

    void lineAnim(){
      // define a random value for animation time variation
      int timeToWait = 1000 + rand() % 800;
  
      anim.lineAnim(this->ledState, timeToWait);
      
      this->ledState = !this->ledState;
    }

    void waveAnim(){
      // define a random value for animation time variation
      int timeToWait = 1000 + rand() % 800;

      anim.waveAnim(this->ledState, timeToWait);
      
    }
    
    void soundAnim(){    
       anim.levelAnim();
    }
};
