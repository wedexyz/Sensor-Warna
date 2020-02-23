int s0=D1; //Pin S0 ke Pin D3 Arduino
int s1=D2; //Pin S1 ke Pin D3 Arduino
int s2=D2; //Pin S2 ke Pin D3 Arduino
int s3=D3; //Pin S3 ke Pin D3 Arduino
int out=D4; //Pin OUT ke Pin D3 Arduino

// LED Pin sebagai indikator Warna Object terdeteksi
const int LED=13; 

void TCS3200setup(){
pinMode(LED,OUTPUT);
pinMode(s2,OUTPUT);
pinMode(s3,OUTPUT);
pinMode(s0,OUTPUT);
pinMode(s1,OUTPUT);

return;
}

void setup(){
//Set Color Sensor
TCS3200setup();

//Setting OUT COlor LED
//RGB LED Common Cathode (Diffused RGB LED)
pinMode (9, OUTPUT);  //Red Led
pinMode (10, OUTPUT); //Green Led
pinMode (11, OUTPUT); //Blue Led

//Memulai koneksi Serial dengan Serial Monitor Arduino IDE
Serial.begin(115200);

delay(100); //delay set to loop
}

void loop(){

//Looping Color Detection
Serial.print(detectColor(out));
//Delay Color Scanner
delay(100); 
}

unsigned int detectColor(int taosOutPin){
  //Tolerance adalah nilai minimal sebuah OUT sensor yang di anggap sebagai 'WARNA TERDETEKSI'
  //Fungsinya untuk menghindari Noise hasil baca sensor dan Iddle Time Sensor (saat tidak ada object)
  //Nilai Tolerance 1-10 
double isPresentTolerance=1;
double isPresent =colorRead(taosOutPin,0,0)/colorRead(taosOutPin,0,1);

Serial.print("isPresent:");
Serial.println(isPresent,2);

Serial.print("isPresentTolerance curently set to:");
Serial.println(isPresentTolerance,2);

if(isPresent<isPresentTolerance){

Serial.println("nothing is in front of sensor");

return 0;
}

double red,blue,green;
double white = colorRead(taosOutPin,0,1);
unsigned int maxColor = white;
unsigned  int red2, blue2, green2;

//Red Color Detection mode
red = white/colorRead(taosOutPin,1,1);
red2=red*255/maxColor;

//Green Color Detection mode
green = white/colorRead(taosOutPin,3,1);
green2=green*255/maxColor;

//Blue Color Detection mode
blue = white/colorRead(taosOutPin,2,1);
blue2=blue*255/maxColor;


Serial.print("red  :");
Serial.println(red2);
//Generate RED Color to RGB LED
if(red2>20){analogWrite (9, red2);}
else {analogWrite (9, 0);}

Serial.print("green  :");
Serial.println(green2);
//Generate GREEN Color to RGB LED
if(green2>20){analogWrite (10, green2);}
else {analogWrite (10, 0);}

Serial.print("blue  :");
Serial.println(blue2);
//Generate BLUE Color to RGB LED
if(blue2>20){analogWrite (11, blue2);}
else {analogWrite (11, 0);}

}

unsigned int colorRead(unsigned int taosOutPin,unsigned int color, boolean LEDstate){
pinMode(taosOutPin, INPUT);

taosMode(1);

int sensorDelay=1;

if(color==0){
digitalWrite(s3, LOW);
digitalWrite(s2, HIGH);

}else if(color==1){
digitalWrite(s3, LOW);
digitalWrite(s2, LOW);

}else if(color==2){
digitalWrite(s3, HIGH);
digitalWrite(s2, LOW);

}if(color==3){
digitalWrite(s3, HIGH);
digitalWrite(s2, HIGH);
}

unsigned int  readPulse;
if(LEDstate==0){
digitalWrite(LED, LOW);
}

if(LEDstate==1){
digitalWrite(LED, HIGH);
}

delay(sensorDelay);
readPulse=pulseIn(taosOutPin, LOW, 25000)/2;
if( readPulse<.1){
readPulse = 25000;
}

taosMode(0);

return  readPulse;

}

void taosMode(int mode){
if(mode==0){
digitalWrite(LED,LOW);
digitalWrite(s0,LOW);
digitalWrite(s1,LOW);
} 
else if(mode==1){
digitalWrite(s0,HIGH);
digitalWrite(s1,HIGH);
} 
else if(mode==2){
digitalWrite(s0,HIGH);
digitalWrite(s1,LOW);
} 
else if(mode==3){
digitalWrite(s0,LOW);
digitalWrite(s1,HIGH);
}

return;
}
