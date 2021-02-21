
#include "PanelManager.h"
#include "RelayAlimManager.h"
#include "ButtonsManager.h"
#include <avr/sleep.h>

#define DEBUG_MODE false
#define NUM_ANIM_MODE 7
#define INIT_ANIM_MODE 0

ButtonsManager buttonsManager;
PanelManager panelManager;
RelayManager relayManager;

int mode = INIT_ANIM_MODE;

void setup(){
  if (DEBUG_MODE){
    Serial.begin(9600); // open the serial port at 9600 bps:
  }
  buttonsManager.init( NUM_ANIM_MODE, &mode );
  relayManager.init();
  panelManager.init();
  
  // Param arratInterrupt here because it cannot be define in a cpp file, like in ButtonsManager:init()
  
  // On nano every, wake from sleep after interrupt are available only on the full async pins on rising/falling 
  // the rest can only wake from sleep on low level or change, and can be used with attachIntereupt.
  // https://patriciakelly.eu/logs/docs/ktz5f.php?id=b30fe9-arduino-nano-interrupt-pins
  attachInterrupt(buttonsManager.getPinButtonNext(), ButtonNextAction, CHANGE );
  attachInterrupt(buttonsManager.getPinButtonPrevious(), ButtonPreviousAction, CHANGE );
  attachInterrupt(buttonsManager.getPinButtonPlay(), ButtonPlayAction, CHANGE );
  attachInterrupt(buttonsManager.getPinButtonNextMode(), ButtonNextModeAction, CHANGE );
  attachInterrupt(buttonsManager.getPinButtonPreviousMode(), ButtonPreviousModeAction, CHANGE );
  
}

void outSleep(){
  
}

void ButtonNextAction(){
  buttonsManager.actionButtonNext();
  sleep_disable();
}

void ButtonPreviousAction(){
  buttonsManager.actionButtonPrevious();
  sleep_disable();
}

void ButtonPlayAction(){
  buttonsManager.actionButtonPlay();
  sleep_disable();
}

void ButtonNextModeAction(){
  buttonsManager.actionButtonNextMode();
  sleep_disable();
}

void ButtonPreviousModeAction(){
  buttonsManager.actionButtonPreviousMode();
  sleep_disable();
}



void loop(){
  switch (mode) {
    case 0:
       panelManager.randomAnim();
       break;
    case 1:
       panelManager.soundAnim();
       break;
    case 2:
       panelManager.ledPerLedAnim();
       break;
    case 3:
       panelManager.rowPerRowAnim();
       break;
    case 4:
      panelManager.borderToCenterAnim();
      break;
    case 5:
      panelManager.lineAnim();
      break;
    case 6:
      panelManager.waveAnim();
      break;
  }
}
