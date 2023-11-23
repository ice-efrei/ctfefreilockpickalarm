#include <TM1637Display.h>

#define CLK D2 
#define DIO D3
#define BTN_RESET D1

#define DEBUG 0

const int nb_btns = 4;
const int btns[] = {D5, D6, D7, D8};

bool loop_state = false;
bool btn_states[4];
bool rst_state = false;
const long tmax = 3; 
int t0 = 0;
int tlog = 0;
int state = 0;

int sAudioPin = D4; // Speaker pin
TM1637Display display = TM1637Display(CLK, DIO);

void setup(){
  Serial.begin(115200);

  pinMode(BTN_RESET, INPUT_PULLUP);
  for(int i = 0; i < nb_btns; i++){
    pinMode(btns[i], INPUT_PULLUP);
    btn_states[i] = false;
  }
    	
    pinMode(sAudioPin, OUTPUT);
  loop_state = false;
  rst_state = false;
  t0 = -1;
  tlog = millis();

  Serial.println("program start");
}

void gamereset(){
    Serial.println("game reset");
}

void startgame(){
    Serial.println("game start");
}

void gameover(){
    Serial.println("gameover");
}

void success(){
    Serial.println("success");
    for (int x = 0; x < 500 ; x++){
        tone (11, x);
        delay(1);
    }
    noTone(sAudioPin);
}

void displaytime(){
    int minutes = (((tmax * 60 * 1000) - (millis() - t0)) / 60000) % 100;
    int seconds = (((tmax * 60 * 1000) - (millis() - t0)) % 60000) / 1000;
    int time = minutes * 100 + seconds;

    // Serial.print("time: ");
    // Serial.print(time);
    // Serial.print(" | ");
    // Serial.print(minutes);
    // Serial.print(" ");
    // Serial.println(seconds);

    // Serial.print("tmax: ");
    // Serial.print(tmax);
    // Serial.print(" | ");
    // Serial.print("t0: ");
    // Serial.print(t0);
    // Serial.print(" | ");
    // Serial.print("millis: ");
    // Serial.println(millis());
    
    display.clear();
    display.showNumberDec(time);
}

void displaystandby(){
    state = (state+1) % 12;
    uint8_t standby[12][4] = {
        {SEG_A, 0x00, 0x00, 0x00},
        {0x00, SEG_A, 0x00, 0x00},
        {0x00, 0x00, SEG_A, 0x00},
        {0x00, 0x00, 0x00, SEG_A},
        {0x00, 0x00, 0x00, SEG_B},
        {0x00, 0x00, 0x00, SEG_C},
        {0x00, 0x00, 0x00, SEG_D},
        {0x00, 0x00, SEG_D, 0x00},
        {0x00, SEG_D, 0x00, 0x00},
        {SEG_D, 0x00, 0x00, 0x00},
        {SEG_E, 0x00, 0x00, 0x00},
        {SEG_F, 0x00, 0x00, 0x00},
    };
    display.clear();
    display.setSegments(standby[state]);
}

void display_values() {
    if (!DEBUG) return;

    Serial.print("loop_state: ");
    Serial.print(loop_state);
    Serial.print(" | ");
    Serial.print("rst_state: ");
    Serial.print(rst_state);
    Serial.print(" | ");
    
    for (int i = 0; i < nb_btns; i++){
        Serial.print(btn_states[i]);
        Serial.print(" ");
    }
    Serial.println();
}

void loop(){
    display.setBrightness(5);
    bool complete = true;
    for (int i = 0; i < nb_btns; i++)
    {
        btn_states[i] = !digitalRead(btns[i]) || btn_states[i];
        if (!btn_states[i]){
            complete = false;
        }
    }
    rst_state = digitalRead(BTN_RESET);

    if (!rst_state && loop_state){
        // reset game
        loop_state = false;
        gamereset();
        delay(1000);
        return;
    }

    if (!rst_state && !loop_state){
        // start chronometer
        t0 = millis();
        loop_state = true;
        for(int i = 0; i < nb_btns; i++){
          btn_states[i] = false;
        }
        rst_state = false;
        startgame();
        delay(1000);
        return;
    }

    if (complete && loop_state){
        success();
        delay(1000);
        loop_state = false;
        return;
    }

    if (millis() - t0 > (tmax * 60 * 1000) && loop_state){
        gameover();
        delay(1000);
        loop_state = false;
    }

    if (millis() - tlog > 1000 && DEBUG){
        display_values();
        if (loop_state){
            displaytime();
        } else {
            displaystandby();
        }	
        tlog = millis();
    }
}


