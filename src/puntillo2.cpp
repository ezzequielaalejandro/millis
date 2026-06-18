#include <arduino.h>

int sensores [4] {1,2,3,4}; 
int seg7_init [7] {5,6,7,8,9,10,11}; //para encender los pines del 7 seg
int seg7 [5] [7] { //esquema para la secuencia del 7seg
    {0,1,1,0,0,0,0},//1 
    {1,1,0,1,1,0,1},//2
    {1,1,1,1,0,0,1},//3
    {0,0,0,0,0,0,1} //-
//   a b c d e f g
};

int visto = 13;
volatile int ambiente;  //la hago volatil xq la uso adentro de funciones
int t_previo = 0, t_delay = 1000;
int est = 0;    //uso esta variable para hacer que el guion "titile"

void IRAM_ATTR sensor1 (){ //creo todas las funciones para las interrupciones, basicamente estoy usando la variable
 ambiente = 0;              // ambiente para indicar que numero se tiene que mostrar en el 7 segmentos
}
void IRAM_ATTR sensor2 (){
ambiente = 1;
}
void IRAM_ATTR sensor3 (){
ambiente = 2;
}
void IRAM_ATTR sensor4 (){
ambiente = 3;
}
void IRAM_ATTR toggle (){   //cuando vale 4 es para que se muestre el guion
ambiente = 4;
}

void setup(){

    for (int i = 0; i <= 7; i++){
        pinMode(seg7_init[i], OUTPUT);
    }

    for (int i = 0; i <= 4; i++){
        pinMode(sensores[i], INPUT_PULLUP);
    }

    pinMode(visto, INPUT_PULLUP);

attachInterrupt (digitalPinToInterrupt (sensores [0]), sensor1, FALLING); //pongo todos las entradas q uso como interrupciones
attachInterrupt (digitalPinToInterrupt (sensores [1]), sensor2, FALLING);
attachInterrupt (digitalPinToInterrupt (sensores [2]), sensor3, FALLING);
attachInterrupt (digitalPinToInterrupt (sensores [3]), sensor4, FALLING);
attachInterrupt (digitalPinToInterrupt (visto), toggle, FALLING);
}

void loop (){

      int t_actual = millis();
if(ambiente = 4){
  if(t_actual - t_previo >= t_delay){ //el tiempo de 1 seg que se toma para que "titile" el amiguito guion
      if(est){
        for(int i = 0; i <= 7; i ++){
            if(seg7 [3] [i]) {digitalWrite (seg7_init [i], HIGH);} else{ //escribe el guion
                digitalWrite (seg7_init [i], LOW);}
        }
      }else{
        for(int i = 0; i <= 7; i ++){                   //borra el guion
                digitalWrite (seg7_init [i], LOW);}
      }
      est=!est;
    t_previo = t_actual;
  }
}

  for(int i = 0; i <= 7; i ++){
            if(seg7 [ambiente] [i]) {       //escribe el numero de ambiente segun en donde el sensor detecto movimiento
                digitalWrite (seg7_init [i], HIGH);
            } else{
                digitalWrite (seg7_init [i], LOW);}
        }
  }