       #include "DHT.h"
  
        #include <Servo.h>   // 서보 모터 (기본 내장) 
        #include "LedControlMS.h" //8X8 LED Martrix (외부)
        
        #include <SoftwareSerial.h>

          #include <Wire.h> //LCD wire library
          #include "LiquidCrystal_I2C.h"//LCD Library

    /*** 
     *  
     *  address 0x20, 0x27, 0x3F
     *  SDA --> A4 , SCL --->A5   
     ****/
        
    LiquidCrystal_I2C lcd(0x27,16,2);  


       #define  DIN 10
       #define  CS  11   
       #define  CLK 12
    

       /****  블루투스 RX,TX 수정  ****/
       #define TX 2
       #define RX 3
      

       

       //blueTooth 통신 init
       SoftwareSerial BTSerial(TX,RX); //Pinout RX,TX 

       // HEAT BEAT 
       #define  LOW_BEAT 0
       #define  MID_BEAT 1
       #define  HIGH_BEAT 2
       
         #define NBR_MTX 1 //number of matrices attached is one
          LedControl lc=LedControl(DIN,CLK,CS, NBR_MTX);// DIN, CLK, CS

       
     


      Servo myservo;
       
  
      /****** 입력 센서 부분 *******/
       #define LIGHT_SENSOR A0      //조도 센서 PIN 설정
       #define SOIL_HUMI A1  // 토양 수분센서 PIN 설정
       #define TEMPERTURE  7   //온도,습도 센서 PIN 설정 
  
  
       /*** 출력 부분 ********/
       #define MOTOR_PIN 9  //수중 모터 릴레이 PIN 설정
       #define LED_PIN 13  //LED 조명 릴레이 PIN 설정 
       #define PIEZO_PIN 4  //피에조 부조음

   
      
      /**** 토양 부분 ******/  
       int sensorValue = 0;  // 센서에서 받은 데이터를 저장하는 변수 
       
     
       DHT dht(TEMPERTURE, DHT11);

       
      
      
     
     

       byte all[] = {  //화면이 불이 다 커진다.
             B11111111, 
             B11111111, 
             B11111111, 
             B11111111, 
             B11111111,
             B11111111, 
             B11111111, 
             B11111111  
          };
          
         

  byte Lowbeat[12][8]={  //9컷으로 낮은 심장 박동수
             
            {B00000000,  
             B00000000,  
             B00000000,  
             B00000010,  
             B11111101,
             B00000000,  
             B00000000,  
             B00000000 },
             
            {B00000000,  
             B00000000,  
             B00000000,  
             B00000100,  
             B11111010,
             B00000001,  
             B00000000,  
             B00000000 },
             
            {B00000000,  
             B00000000,  
             B00000000,  
             B00001000,  
             B11110101,
             B00000010,  
             B00000000,  
             B00000000 },
             
            {B00000000,  
             B00000000,  
             B00000000,  
             B00010000,  
             B11101011,
             B00000100,  
             B00000000,  
             B00000000 },
             
            {B00000000,  
             B00000000,  
             B00000000,  
             B00100000,  
             B11010111,
             B00001000,  
             B00000000,  
             B00000000 },
             
            {B00000000,  
             B00000000,  
             B00000000,  
             B01000000,  
             B10101111,
             B00010000, 
             B00000000,  
             B00000000 },
             
            {B00000000,  
             B00000000,  
             B00000000,  
             B10000000,  
             B01011111,
             B00100000,  
             B00000000,  
             B00000000 },
             
            {B00000000,  
             B00000000,  
             B00000000,  
             B00000000,  
             B10111111,
             B01000000,  
             B00000000,  
             B00000000 },
             
            {B00000000,  
             B00000000,  
             B00000000,  
             B00000001, 
             B01111111,
             B10000000,  
             B00000000,  
             B00000000 },
              
            {B00000000,  
             B00000000,  
             B00000000,  
             B00000010,  
             B11111101,
             B00000000,  
             B00000000,  
             B00000000 },
             
            {B00000000,  
             B00000000,  
             B00000000,  
             B00000100,  
             B11111010,
             B00000001,  
             B00000000,  
             B00000000 
             },
             {B00000000,  
             B00000000,  
             B00000000,  
             B00000010,  
             B11111101,
             B00000000,  
             B00000000,  
             B00000000 },
          };
             
 

 byte Midbeat[11][8]={ //11컷으로 중간 심장 박동수 
            
            {B00000000,  
             B00000000,  
             B00000001,  
             B00000011,  
             B11111110,
             B00000000,  
             B00000000,  
             B00000000, },
             
            {B00000000,  
             B00000000,  
             B00000010, 
             B00000111,  
             B11111101,
             B00000001, 
             B00000000,  
             B00000000, },
             
            {B00000000,  
             B00000000,  
             B00000100,  
             B00001110,  
             B11111010,
             B00000011,  
             B00000001, 
             B00000000, },
             
            {B00000000,  
             B00000000,  
             B00001000,  
             B00011100,  
             B11110101,
             B00000111,  
             B00000010,  
             B00000000, },
             
            {B00000000,  
             B00000000, 
             B00010000, 
             B00111000,  
             B11101011,
             B00001110,  
             B00000100,  
             B00000000, },
             
            {B00000000,  
             B00000000,  
             B00100000,  
             B01110000,  
             B11010111,
             B00011100,  
             B00001000,  
             B00000000, },
           
            {B00000000,  
             B00000000,  
             B01000000, 
             B11100000,  
             B10101111,
             B00111000,  
             B00010000,  
             B00000000, },
           
            {B00000000,  
             B00000000,  
             B10000000, 
             B11000000,  
             B01011111,
             B01110000,  
             B00100000,  
             B00000000,},
           
            {B00000000,  
             B00000000,  
             B00000000,  
             B10000000, 
             B10111111,
             B11100000,  
             B01000000,  
             B00000000, },
            
            {B00000000,  
             B00000000,  
             B00000000,  
             B00000000,  
             B01111111,
             B11000000,  
             B10000000,  
             B00000000, },
            
            {B00000000,  
             B00000000,  
             B00000000,  
             B00000001, 
             B11111111,
             B10000000,  
             B00000000,  
             B00000000, },
            
            
            
            }; 


   byte Highbeat[11][8]={  //11컷으로 높은 심장 박동수 
             
             
            {B00000000,  
             B00000000,  
             B00000001,  
             B00000001,  
             B11111111,
             B10000000,  
             B10000000,  
             B00000000 },
             
            {B00000000,  
             B00000001,  
             B00000010,  
             B00000010,  
             B11111110,
             B00000000,  
             B00000000,  
             B00000000 },
             
            {B00000000,  
             B00000010,  
             B00000101, 
             B00000101,  
             B11111101,
             B00000001,  
             B00000001,  
             B00000000 },
             
            {B00000000, 
             B00000100,  
             B00001010,  
             B00001010,  
             B11111010,
             B00000010,  
             B00000010,  
             B00000001 },
             
            {B00000000,  
             B00001000,  
             B00010100,  
             B00010100,  
             B11110101,
             B00000101, 
             B00000101,  
             B00000010 },
             
            {B00000000, 
             B00010000,  
             B00101000, 
             B00101000,  
             B11101011,
             B00001010,  
             B00001010,  
             B00000100 },
             
            {B00000000,  
             B00100000,  
             B01010000,  
             B01010000,  
             B11010111,
             B00010100,  
             B00010100,  
             B00001000},
             
            {B00000000,  
             B01000000, 
             B10100000,  
             B10100000,  
             B10101111,
             B00101000,  
             B00101000}, 
             
            {B00000000,  
             B10000000,  
             B01000000,  
             B01000000,  
             B01011111,
             B01010000,  
             B01010000,  
             B00100000},
             
            {B00000000, 
             B00000000,  
             B10000000,  
             B10000000,  
             B10111111,
             B10100000,  
             B10100000,  
             B01000000},
             
            {B00000000,  
             B00000000,  
             B00000000,  
             B00000000,  
             B01111111,
             B01000000,  
             B01000000, 
             B10000000},
    };

     byte e[] =   //비행기 이모티콘 모양
    {
       B00011000,   
       B00111100,
       B01111110,
       B11011011,
       B11111111,
       B00100100,
       B01011010,
       B10100101
    };
  
      
      int count1 =0;   

      float temp = 26;        // 온도 센서 변수
      float humi = 40;        // 습도 센서 변수
             
      int light = 369;        // 조도 센서 변수
      int soil_humi = 800;     // 토양 습도 센서 변수 

      // 통신 변수 정의 
      char inBTChar; //blueTooth 글자 체크 (한 글자씩 체크)
      char inSLChar; //Serial 글자 체크 
      
      String inputBTString = "";  //On,OFF 체크... 
      String inputSLString = "";  //On,OFF 체크...

      bool light_chk, soil_chk;  //8X8 LED 상태 표시


      int delaytime = 50;
    
      
           
        void setup()
  
        {
           Serial.begin(9600);   //설정 1초당 9600byte 씨리얼 통신 속도  
           BTSerial.begin(9600); //설정 1초당 9600byte 블루투스 통신 속도  

           dht.begin();

           pinMode(LED_PIN, OUTPUT);   
           pinMode(MOTOR_PIN,OUTPUT);

       lcd.init();
       lcd.backlight();
       lcd.setCursor(0,0); 
       lcd.print("<<SMART FARM>>"); 
       lcd.setCursor(0,1);
       lcd.print("--->START"); 
           
           inputBTString = "";

           for (int i=0; i< NBR_MTX; i++) {  //LED 8*8 셋팅하는 부분
              lc.shutdown(i,false);
              lc.setIntensity(i,8);
              lc.clearDisplay(i);
              delay(100);
            }

             /* 여기서부터 수정 */ 
             digitalWrite(LED_PIN,HIGH); 
             shift_string ("I love you.",70);  
             delay(1000); 
             printByte(e); // 이모티콘
             delay(1000); 
          
          /* 피에조 부조음 및 LED 체크 */ 
          
          tone(PIEZO_PIN,300,50); 
    
  
           
           /* 심장 박동 테스트 */
           printBeat(0);
           

          
          /* 서보 모터 테스트  (180도 -> 0도 테스트)   */
          myservo.attach(MOTOR_PIN);
          myservo.write(30);
          tone(PIEZO_PIN,800,50); 
          delay(1000);
          
          myservo.write(150);
          tone(PIEZO_PIN,800,50); 
          delay(1500);
          myservo.detach();
          delay(100);


           /* 조명 테스트  */ 
           tone(PIEZO_PIN,800,50);
         

         Serial.println("\n\n====== Environment Show ======\n\n");
          digitalWrite(LED_PIN,LOW); 
         get_sensor_value();
             
        }
  

      bool water_toggle = HIGH; 
      bool light_toggle= HIGH;
         
        
      void loop() {

          Serial.println("\n\n====== Environment Show ======\n\n");
          get_sensor_value();
             
 
           delay(10);

         
           while(BTSerial.available()){
  
               inBTChar = (char)BTSerial.read();  //serial 한글마다
                
               if(inBTChar == '\n' || inBTChar == '\r' || inBTChar == '_'){               
              tone(PIEZO_PIN,500,100);    // 블루투스 값을 받았는 표시 
        


              /* 
              *   센스 값은  (온도,습도,조도,토양습도)   22,80,12,80
              */ 
              if(inputBTString.equals("SENSOR")){   
             /*  
              *  아날로그 값을 100(백분율)로 바꾸는 작업. 
              */

              Serial.println("\n\n====== Environment bluetooth show ======\n\n");
              get_sensor_value();

             
             /* 블루투스로 값 보여주기 */ 
              BTSerial.print(String((int)temp));
              delay(5);
              BTSerial.print(","+String((int)humi));
              delay(5);
              BTSerial.print(","+String((int)light));
              delay(5);
              BTSerial.print(","+String((int)soil_humi));
              delay(5);
             
             tone(PIEZO_PIN,1241,100);
             delay(20);
             
             } else if(inputBTString.equals("ON")){  //조명 켜기
                
                digitalWrite(LED_PIN,HIGH);
                printByte(all);
                delay(500);
                shift_string("LIGHT",50);

                light_toggle = LOW;
            
                delay(50);
                tone(PIEZO_PIN,300,120);     
                
                inputBTString = "";
              
             }else if (inputBTString.equals("OFF")){ //조명 끄기 

                digitalWrite(LED_PIN,LOW);
                shift_string("OFF",50);
                Serial.println("OFF");
                light_toggle = HIGH; 
                
                tone(PIEZO_PIN,745,100);
                inputBTString = "";
             }else if (inputBTString.equals("WATERON")){ // 물주기 

               Serial.println("WATERON");
              
                Serial.println("ON");

               water_toggle = LOW; 
               
               myservo.attach(MOTOR_PIN);
               myservo.write(0);  // 서보 모터 각도 
               shift_string("WATER",70);
               delay(200);
               tone(PIEZO_PIN,200,200);
               inputBTString = "";
                
               myservo.detach();
             }else if (inputBTString.equals("WATEROFF")){ //물주기 멈춤

               water_toggle = HIGH;
               
                myservo.attach(MOTOR_PIN);
                myservo.write(150);    // 서보 모터 각도 
                shift_string("OFF",50);
                delay(500);
                inputBTString = "";
                
                myservo.detach();
             }else{
                delay(50);
                Serial.println(inputBTString);
                inputBTString = "";
              }
   
            } //if
            else {
              inputBTString += inBTChar;
              tone(PIEZO_PIN,500,100);  
              Serial.print(inBTChar);
            }
 

      
       }//while  



    
         if(!BTSerial.isListening()) {water_toggle=HIGH; light_toggle=HIGH;}
          else{
            
            
           }

         if(light_toggle == HIGH){      
             light_check();
         }
         if(water_toggle == HIGH){
          humi_check();
         } 

        if(light_chk && soil_chk){

          lcd.clear(); 
          lcd.print("SMART FARM:");
          lcd.setCursor(0,1);
          lcd.print("---> nomal"); 
          
          printBeat(0); 
          
        }else if(!light_chk && soil_chk){

          lcd.clear(); 
          lcd.print("SMART FARM:");
          lcd.setCursor(0,1);
          lcd.print("-->solar is bad"); 
          
          printBeat(1); 
          
        }else if(light_chk && !soil_chk){
          lcd.clear(); 
          lcd.print("SMART FARM:");
          lcd.setCursor(0,1);
          lcd.print("-->soil is bad"); 
          
          printBeat(1); 
          
        }else{

          lcd.clear(); 
          lcd.print("SMART FARM:");
          lcd.setCursor(0,1);
          lcd.print("-->All Dangerous"); 
          
          printBeat(2); 

          
        }

         if(light_toggle==LOW && water_toggle==LOW){
          printByte(all);
         }    
     delay(20);
   }//loop

 void light_check(){
          if ( light < 40 ){                 // 조도 켜지는 기준 값              
            digitalWrite(LED_PIN,HIGH);
            light_chk = false;
          }else{
            digitalWrite(LED_PIN,LOW);
            light_chk = true;
          }  
 }


 void humi_check(){

      if(soil_humi != 0){
       if ( soil_humi < 30){
                    myservo.attach(MOTOR_PIN);
                    myservo.write(0);      
                    delay(1000);
                    myservo.detach();
                    soil_chk = false; 
         }else{
            myservo.attach(MOTOR_PIN);
            myservo.write(150);
            delay(1000);
            myservo.detach();  
            soil_chk = true; 
         }
       }
 
 }
 
  
  void get_temp_value(){

      delay(20); 
      humi = dht.readHumidity();
      temp = dht.readTemperature();
    
      Serial.print("temperature:"+String((int)temp)+"*C");
      Serial.println(",humi:"+String((int)humi)+"%");
  
  }
  
  void get_sensor_value(){

        get_temp_value();

       /* 조명 센서 */
        light= analogRead(LIGHT_SENSOR);  
        light = map(light, 0, 1023, 0, 100); 
        light= 100-light; 
       
        Serial.print("  light:");
        Serial.print(light);
        delay(5);
        
     
         /* 수분 습도 센서 */ 
        soil_humi = analogRead(SOIL_HUMI);  
        soil_humi = map(soil_humi, 0, 1023, 100, 1);       
        Serial.print("%, soil_humi:");
        Serial.print(soil_humi);
        Serial.print("%");
        delay(5);


        //temp,humi,light,soil_humi
        lcd.clear();
        lcd.print("Temp:"+String((int)temp)+"C" + ",Hum:"+ String((int)humi)+"%"); 
        lcd.setCursor(0,1);
        lcd.print("Ligh:"+String((int)light)+"%" + ",Soil:"+String((int)soil_humi)+"%");
        delay(100); 

       
      
  }

 void printBeat(int beat){

       int i;
       if(beat == 0){
            
         for(i=0; i<11; i++){
             delaytime = 20; // 초기 값  
          if(i==3 || i==6 || i==9){
              delaytime = 50;
              //tone(PIEZO_PIN,50,10);
               }
            printByte(Lowbeat[i]);
            delay(delaytime);
            }
        
       }else if(beat == 1){

       for(i=0; i<11; i++){
             delaytime = 20; 
           if(i==3 || i==6 || i==9){
                delaytime = 50;
                //tone(PIEZO_PIN,50,10);
                 }
               printByte(Midbeat[i]);
               delay(delaytime);
              }

       }else if(beat == 2){

          for(i=0; i<11; i++){
             delaytime = 20; 
            if(i==2 || i==5 || i==8){
            delaytime = 50;
            //tone(PIEZO_PIN,50,10);
           }  
          printByte(Highbeat[i]);
          delay(delaytime); 
          
          }
       }

       lc.clearAll();

     } //


     void printByte(byte character [])
      {
        int i = 0;
        for(i=0;i<8;i++)
        {
          lc.setColumn(0,7-i,character[i]);
        }
      }    

     

      void shift_string(String str,int delay_time){  //좌로 불러오기 (Sting/ 대기 시간)
      
           int count = ((str.length()-1)*6)+1; 
           int i = 0;
                            
           for(int j=count+1; j>-3;j--){  //좌우 바뀌는 것..
               for(int z=str.length()-1; z>-1;z--){
                       Serial.print(",Z:");
                       int display_char = lc.getCharArrayPosition(str[z]);
                       displayShiftChar(j-count+(z*6),display_char);                           

                               }
                  delay(delay_time);
                  lc.clearAll();
               }
        }



      void displayShiftChar(int matrix, int charIndex) { //문자 좌우로 보여주기
              int count =0; 
              for (int i=matrix; i< matrix+6;i++) {
                  lc.setRow(0,i, alphabetBitmap[charIndex][count++]);
              } 
      }
