enum ButtonState
{
  Off,
  On,
  Repeating
};

ButtonState upButtonState = Off;
int upButtonlastStateChangeTime = 0;
const int upInputPin = 0;
const int upOutputPin = 1;

ButtonState downButtonState = Off;
int downButtonlastStateChangeTime = 0;
const int downInputPin = 2;
const int downOutputPin = 4;

void setup()
{
  pinMode(upOutputPin, OUTPUT);
  pinMode(upInputPin, INPUT_PULLUP);
  digitalWrite(upOutputPin, HIGH);
  
  pinMode(downOutputPin, OUTPUT);
  pinMode(downInputPin, INPUT_PULLUP);
  digitalWrite(downOutputPin, HIGH);

}

void processButton(int inPin, int outPin, ButtonState* state, int* lastStateChangeTime)
{
  //digitalWrite(outPin, digitalRead(inPin)); return;
  bool buttonPressed = (digitalRead(inPin) == LOW);

  if(buttonPressed)
  {
    int timeSinceStateChange = millis() - *lastStateChangeTime;
    
    switch(*state)
    {
    case Off:
      digitalWrite(outPin, LOW);
      *state = On;
      break;
  
    case On:
      if(timeSinceStateChange > 500)
      {
        *state = Repeating;
        *lastStateChangeTime = millis();
      }
      break;
  
    case Repeating:
      const int period = 50;
      int pos = timeSinceStateChange / period;
  
      if((pos % 2) == 0)
        digitalWrite(outPin, HIGH);
      else
        digitalWrite(outPin, LOW);
      break;
    }
  }
  else
  {
    digitalWrite(outPin, HIGH);
    *state = Off;
    *lastStateChangeTime = millis();
  }
}

void loop()
{
  processButton(upInputPin, upOutputPin, &upButtonState, &upButtonlastStateChangeTime);
  processButton(downInputPin, downOutputPin, &downButtonState, &downButtonlastStateChangeTime);
}
