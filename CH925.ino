//La papa con salsa no sabe mejor
const int coinSelector = 4;
const float signalCostFactor = 0.5; // Each signal pulse is worth 5p


//Marzo 27, 2020.


int signalValue = 0; // For storing value from analog input

int state; // Current state
int lastState = 0; // Last state

float balance = 0; // Pence
float coinValue = 0; // Curent coin value

int update = 1; // Used for sending an update

long updateDebounceTime = 0; // The last time we sent an update
long updateDebounceDelay = 250; // Update 500ms after last singal pulse

void setup() {

  pinMode(13, OUTPUT); // Status LED
  Serial.begin(9600); // Setup serial at 9600 baud
  delay(2000); // Don't start main loop until we're sure that the coin selector has started
  Serial.println("Ready..");


void loop() {

  signalValue = digitalRead(coinSelector); // Read analog value from coin selector

  if (signalValue > 0) {

    state = 1; // State is 1 as we're high

  } else {

    state = 0;
    if (update == 0) {

      if ((millis() - updateDebounceTime) > updateDebounceDelay) {

        Serial.print("Coin Value: ");
        Serial.println(coinValue); // WARNING: The coin value will be wrong if coins are inserted within the updateDebounceDelay, adjust the delay and test
        Serial.print("Balance: ");
        Serial.println(balance); // This should be the most accurate as we should get the same ammount of pulses even if multiple coins get inserted at once
        coinValue = 0;
        update = 1;
      }
    }
  }

  if (state != lastState) {
    if (state == 1) {
      balance = balance + signalCostFactor;
      coinValue = coinValue + signalCostFactor; 
      updateDebounceTime = millis();
      update = 0; 

    } 
    lastState = state; 
  }
  delay(1);
}
/*pollito lofiu*/




