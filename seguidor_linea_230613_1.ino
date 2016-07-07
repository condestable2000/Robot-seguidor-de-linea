/*Robot seguidor de líneas con control de velocidad para
Arduino Duemilanove w/ ATmega 328 y controlador de motor
Keyes L298.

José Pablo Hernández (condestable2000 at gmail.com)
23 de junio de 2013
*/
int SensorI = 8;//Pin del sensor izquierda
int SensorC = 7;//Pin del sensor centro
int SensorD = 6;//Pin del sensor derecha
int ValI = 0;//Valor sensor izquierda
int ValC = 0;//Valor sensor centro
int ValD = 0;//Valor sensor derecha
int Val = 0;//Valor combinado de los sensores
//Motor izquierda
int EnB = 10;//PWM motor izquierda
int In4 = 5;
int In3 = 4;
//Motor derecha
int EnA = 9;//PWM motor derecha
int In2 = 3;
int In1 = 2;
//Velocidades
int VMax = 180;
int VMin = 180;
//Sentido marcha
int adelante = 1;
int atras = 0;

void setup()
{
  //Serial.begin(9600);
  //Configuramos los pines de los sensores
  pinMode(SensorI, INPUT);
  pinMode(SensorC, INPUT);
  pinMode(SensorD, INPUT);
  //Configuramos los pines de los motores
  pinMode(In4, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In1, OUTPUT);
}

void loop()
{
  //Los motores en principio adelante
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
  //Leemos los valores de cada uno de los tres sensores
  //1=blanco (no línea), 0=negro (línea)
    ValI = digitalRead(SensorI);
    ValC = digitalRead(SensorC);
    ValD = digitalRead(SensorD);
   //Combinamos los valores para que sea más fácil la comprobación
    Val = (ValI * 100) + (ValC * 10) + (ValD);
   //Actuamos en los motores según la lectura 
    switch (Val) 
    {
       case 10:
         //Estamos sobre la línea
         //Los dos motores hacia adelante
         marchaMotorD(adelante);
         marchaMotorI(adelante);
         //Los dos motores al 100%
         analogWrite(EnA, VMax);
         analogWrite(EnB, VMax);
         break;
        case 11:
         //Nos hemos deviado algo a la izquierda
         //Los dos motores hacia adelante
         marchaMotorD(adelante);
         marchaMotorI(adelante);
         //Reducimos motor derecha al 50%
         analogWrite(EnA, VMin);
         //Motor izquierda al 100%
         analogWrite(EnB, VMax);
         break;
        case 110:
         //Nos hemos desviado algo a la derecha
         //Los dos motores hacia adelante
         marchaMotorD(adelante);
         marchaMotorI(adelante);
         //Reducimos motor izquierda al 50%
         analogWrite(EnB, VMin);
         //Motor derecha al 100%
         analogWrite(EnA, VMax);
         break;
        case 100:
         //Nos hemos desviado mucho a la derecha
         //Los dos motores hacia adelante
         marchaMotorD(adelante);
         marchaMotorI(atras);
         //Reducimos motor izquierda al 50%
         analogWrite(EnB, VMin);
         //Motor derecha al 100%
         analogWrite(EnA, VMax);
         break;
        case 1:
         //Nos hemos desviado mucho a la izquierda
         //Los dos motores hacia adelante
         marchaMotorD(atras);
         marchaMotorI(adelante);
         //Reducimos motor derecha al 50%
         analogWrite(EnA, VMin);
         //Motor izquierda al 100%
         analogWrite(EnB, VMax);
         break;         
        default:
         //Hemos perdido la línea.
         //Paramos ambos motores
         analogWrite(EnA, 0);
         analogWrite(EnB, 0);
    }
}

void marchaMotorD (int sentidoMotor)
{
 if (sentidoMotor==adelante)
  { //Adelante
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
  } 
  else
  { //Atrás
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
  }
}

void marchaMotorI (int sentidoMotor)
{
 if (sentidoMotor==adelante)
  { //Adelante
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
  } 
  else
  { //Atrás
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
  }
}
