const int EnTxPin =  2;  // HIGH:TX y LOW:RX

void setup() 
{ 
  Serial.begin(9600);
  Serial.setTimeout(100);//establecemos un tiempo de espera de 100ms
  //inicializamos los pines
  pinMode(EnTxPin, OUTPUT);
  digitalWrite(EnTxPin, HIGH); 
} 
 
void loop() 
{ 
   
  int lectura = analogRead(0);//leemos el valor del potenciómetro (de 0 a 1023) 
  int angulo= map(lectura, 0, 1023, 0, 180);// escalamos la lectura a un valor de ángulo (entre 0 y 180) 
  //---enviamos el ángulo para mover el servo------
  Serial.print("I"); //inicio de trama
  Serial.print("S"); //S para indicarle que vamos a mover el servo
  Serial.print(angulo); //ángulo  o dato
  Serial.print("F"); //fin de trama
  //----------------------------
  delay(50); 
  //---solicitamos una lectura del sensor----------
  Serial.print("I"); //inicio de trama
  Serial.print("L"); //L para indicarle que vamos a Leer el sensor
  Serial.print("F"); //fin de trama
  Serial.flush();    //Esperamos hasta que se envíen los datos
  //----Leemos la respuesta del Esclavo-----
  digitalWrite(EnTxPin, LOW); //RS485 como receptor
  if(Serial.find("i"))//esperamos el inicio de trama
  {
      int dato=Serial.parseInt(); //recibimos valor numérico
      if(Serial.read()=='f') //Si el fin de trama es el correcto
       {
         funcion(dato);  //Realizamos la acción correspondiente          
      }
      
  }
  digitalWrite(EnTxPin, HIGH); //RS485 como Transmisor
  //----------fin de la respuesta-----------
  
} 
void funcion(int dato)
{
  if(dato>500)
  digitalWrite(ledPin, HIGH); 
  else
  digitalWrite(ledPin, LOW); 
}