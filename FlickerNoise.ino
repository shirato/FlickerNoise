const int LED_NUM = 3;				//Number of LED
const int LED[] = {9,10,11};	//Set LED pin number
const int TIME = 100;

float curValue[LED_NUM];			//Current value for each LED (0 ~ 1.0)

void setup() {
  Serial.begin(9600);					//for debug
  for(int i = 0; i < LED_NUM; i++){
    pinMode(LED[i], OUTPUT);								//Set each LED pin as OUTPUT
    curValue[i] = random(10, 90) / 100.0;		//Set initial value (1.0 ~ 9.0)
  }
}

void loop() {
	int value;
	for (int i = 0; i < LED_NUM; i++) {
		value = chaos(i);
		analogWrite(LED[i], value);
		//Serial.print("PIN");
		//Serial.print(i);
		//Serial.print(":");
		//Serial.print(value);
		//Serial.print(",");
	}
	Serial.println(value);
	delay(TIME);
}

/*
intermittent chaos method
input:[idx] index of LED pin
output:next value
*/
int chaos(int idx){
  float x = curValue[idx];

  if(x < 0.5){
    x = x + 2 * pow(x, 2);
  } else {
    x = x - 2 * pow((1.0 - x), 2);
  }

	//reset value in case of too lower or higher value
  if(x < 0.05 || x > 0.998){
    x = random(10,90) / 100.0;
  }
  
  curValue[idx] = x;
  x = x * 255;
  return (unsigned int) x;
}

