#include <Arduino.h>

int sensores [4] = {1,2,3,4};
int seg_init7 [7] = {5,6,7,8,9,10,11};
int seg7 [6] [7] = {
    {0,1,1,0,0,0,0}, //1
    {1,1,0,1,1,0,1}, //2
    {1,1,1,1,0,0,1}, //3
    {0,1,1,0,0,1,1}, //4
    {1,0,0,1,1,1,0}, //C
    {0,0,0,0,0,0,1}, //-
};

int boton = 10;
int t_previo3 = 0, t_delay3 = 1000;
int t_previo2 = 0, t_delay2 = 500;
int t_previo = 0, t_delay = 10000;

volatile int estado_de_produccion = 0;   // estado_de_produccion = 0 "quiere decir que la linea esta trabajando"
                                         // estado_de_produccion = 1 "quiere decir que la linea ya termino"


void IRAM_ATTR toggle (){   //QUE SUCEDE SI SE ACTIVA LA INTERRUPCION
    estado_de_produccion = 0;
} 


void setup() {

    for(int i = 0; i <= 4; i++){
        pinMode(sensores [i], INPUT);
    }

    for(int i= 0; i <= 7; i++){
        pinMode (seg_init7 [i], OUTPUT);
    }

    pinMode (boton, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt (boton), toggle, FALLING);
}

void loop(){

    int t_actual = millis();
    int t_actual2 = millis();

if(estado_de_produccion = 0){

    for(int i = 0; i < 4; i++){
        
        if(digitalRead (sensores [i])){
            for(int j = 0; j <= 7; j++){

                if(seg7 [i] [j]){                   //que sensor esta activado
                    digitalWrite (seg_init7 [j], HIGH);
                }else{
                    digitalWrite (seg_init7 [j], LOW);
                }
            }
        }
    }

                if(digitalRead (sensores [3])){       //si el sensor 4 esta encendido

                    if(t_actual - t_previo <= t_delay){    //pasan 10 segundos, luego se muestra la letra C
                        t_actual = t_previo;
                    }
                
                if(t_actual2 - t_previo2 <= t_delay2){ // encinede "C" en el 7seg cada 500ms
                    for(int i = 0; i<= 7; i++){
                        if(seg7[6] [i]){
                            digitalWrite(seg_init7 [i], HIGH);
                        }else{
                            digitalWrite(seg_init7 [i], LOW);
                        }
                        t_actual2 = t_previo2;
                    }
                }

                if(t_actual2 - t_previo3 <= t_delay3){ // apaga "C" en el 7seg cada 500ms
                    for(int i = 0; i<= 7; i++){
                        digitalWrite(seg_init7 [i], LOW);
                        t_actual2 = t_previo3;
                    }
                }
                estado_de_produccion = 1;

                while(digitalRead (sensores [0]) == 0){   //mientras no tenga nada en el primer sensor que muestre el GUION MEDIO
                    for(int k = 0; k <= 7; k ++){
                        if(seg7 [6] [k]){
                            digitalWrite(seg_init7 [k], HIGH);
                        }else{
                            digitalWrite(seg_init7 [k], LOW);
                        }
                    }
                }
            }

    }
}