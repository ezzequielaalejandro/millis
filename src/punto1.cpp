#include <Arduino.h>

int sensores [4] = {1,2,3,4};
int seg_init7 [7];
int seg7 [6] [7] = {
    {0,1,1,0,0,0,0}, //1
    {1,1,0,1,1,0,1}, //2
    {1,1,1,1,0,0,1}, //3
    {0,1,1,0,0,1,1}, //4
    {1,0,0,1,1,1,0}, //C
    {0,0,0,0,0,0,1}, //-
};

int boton = 10;
int t_previo2 = 0, t_delay2 = 500;
int t_previo = 0, t_delay = 10000;


void setup() {

    for(int i = 0; i <= 4; i++){
        pinMode(sensores [i], INPUT);
    }

    for(int i= 0; i <= 7; i++){
        pinMode (seg_init7 [i], OUTPUT);
    }

    pinMode (boton, INPUT);
}

void loop(){

    
    for(int i = 0; i < 4; i++){
        
        if(digitalRead (sensores [i])){
            for(int j = 0; j < 7; j++){

                if(seg7 [i] [j]){                   //que sensor esta activado
                    digitalWrite (seg7 [i] [j], HIGH);
                }else{
                    digitalWrite (seg7 [i] [j], LOW);
                }

                if(sensores [3]){       //si el sensor 4 esta encendido

                
                    int t_actual = millis ();   //pasan 10 segundos
                    t_delay=t_actual+10000;
                    t_previo=t_actual;
                    while(t_actual - t_previo <= t_delay){
                  
                  }

                  while (digitalRead (boton) == 0){

                      for(int j = 0; j < 7; j++){  //muestra la C
                   if(seg7 [4] [j]){
                       digitalWrite (seg7 [4] [j], HIGH);
                   }else{
                       digitalWrite (seg7 [4] [j], LOW);
                   }
                   }

                   int t_actual2 = millis();
                   if(t_actual2 - t_previo2 <= t_delay2){

                   }

                  }


            }
        }
        }
    }
}