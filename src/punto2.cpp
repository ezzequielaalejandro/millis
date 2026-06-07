#include <Arduino.h>

int sensores [4] = {1,2,3,4};
int seg_init7 [7] = {5,6,7,8,9,10,11};
int seg7 [5] [7] = {
    {0,1,1,0,0,0,0}, //1
    {1,1,0,1,1,0,1}, //2
    {1,1,1,1,0,0,1}, //3
    {0,1,1,0,0,1,1}, //4
    {0,0,0,0,0,0,1}, //-
};

int boton = 13;

volatile int movimiento = 0; //movimiento = 0 NO se detecto movimiento
                            //movimiento = 1 SI se detecto movimiento
int t_previo3 = 0, t_delay3 = 1000;
int t_previo2 = 0, t_delay2 = 500;

void IRAM_ATTR toggle(){
    movimiento = 0; //"VISTO"
}

void setup (){

        for(int i = 0; i <= 4; i++){
        pinMode(sensores [i], INPUT);
    }

    for(int i= 0; i <= 7; i++){
        pinMode (seg_init7 [i], OUTPUT);
    }
    pinMode (boton, INPUT_PULLUP);
    attachInterrupt (digitalPinToInterrupt (boton), toggle, FALLING);
}

void loop(){

    int t_actual2 = millis();
    while(movimiento = 0){

        if(t_actual2 - t_previo2 <= t_delay2){ // encinede "-" en el 7seg cada 500ms
                        for(int i = 0; i<= 7; i++){
                            if(seg7[5] [i]){
                                digitalWrite(seg_init7 [i], HIGH);
                            }else{
                                digitalWrite(seg_init7 [i], LOW);
                            }
                            t_actual2 = t_previo2;
                        }
                    }
    
                    if(t_actual2 - t_previo3 <= t_delay3){ // apaga "-" en el 7seg cada 500ms
                        for(int i = 0; i<= 7; i++){
                            digitalWrite(seg_init7 [i], LOW);
                            t_actual2 = t_previo3;
                        }
                    }

                    for(int i = 0; i < 4; i++){     //Registro si hay algun sensor encendido
                        
                        if(digitalRead (sensores [i])){
                
                            for(int j = 0; j <= 7; j++){
                                
                                if(seg7 [i] [j]){                   //que sensor esta activado
                                    digitalWrite (seg_init7 [j], HIGH);
                                }else{
                                    digitalWrite (seg_init7 [j], LOW);
                                }
                            }
                            movimiento = 1;
                        }
                    }
                }
            if(digitalRead(sensores [1]) && digitalRead(sensores [2]) && digitalRead(sensores [3]) && digitalRead(sensores [4]) == 0){
                movimiento = 0;
                /*En caso que no haya ningun sensor encendido se vuelve a sensar*/
            }

}