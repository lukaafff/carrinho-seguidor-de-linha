//___________________________________________Definição Gerais dos Sensores______________________________________________
//_____________Definição Gerais dos Sensores______________
//Definição dos Sensores InfraVermelho
#define sensorDIREITO A5 //AZUL
#define sensorESQUERDO A2 //AMARELO
#define sensorCENTRAL A4 //VERMELHO

//Váriavel para armazenar dados dos Sensores
int Dados_SensorDIREITO; //AZUL
int Dados_SensorESQUERDO; //AMARELO
int Dados_SensorCENTRAL; //CENTRAL

//Definição da linha que divide preto e branco
//se maior que o linear, será preto
//se menor que o linear, será branco
#define linear 300
#define limiar2 450

//variavel de tempo 

unsigned long tempo = 16000 + 3000;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//__________________________________________Definiçoes dos MOTORES_____________________________

//Definição dos Pinos de Potencia dos Motores
#define pinPotMotorESQ  11
#define pinPotMotorDIR  10

//Definição dos Pinos de Direção de Rotação
//Motor Direito
#define MotorDireito_Frente 2
#define MotorDireito_Atras 3

//Motor Esquerdo
#define MotorEsquerdo_Frente 4
#define MotorEsquerdo_Atras 5

//Definição de Velocidades

//Diferença de 25 no valor de um motor para o outro, exemplo abaixo
//#define veloESQ1 130
//#define veloDIR1 105
#define veloESQ1 255
#define veloDIR1 240
#define veloZero 0
#define veloCurvE 150
#define veloCurvD 135

////////////////////////////////////////////////////////////////////////////////////////////////
//________________________________________Definiçoes GERAIS de Funçoes_______________________________

//__________________________________Definição das Funçoes Primarias do motor_________________________

//********************************************************
//Função que faz o carrinho ficar parado
//FUNÇÃO PARADO DESATIVADA
void PARADO(){
  digitalWrite(MotorDireito_Frente,  HIGH );
  digitalWrite(MotorDireito_Atras,    LOW );
  digitalWrite(MotorEsquerdo_Frente, HIGH );
  digitalWrite(MotorEsquerdo_Atras,   LOW );

  analogWrite(pinPotMotorESQ , veloZero);
  analogWrite(pinPotMotorDIR , veloZero);
}
//Função que faz o carrinho andar para frente
void FRENTE(){
  digitalWrite(MotorDireito_Frente,  HIGH );
  digitalWrite(MotorDireito_Atras,    LOW );
  digitalWrite(MotorEsquerdo_Frente, HIGH );
  digitalWrite(MotorEsquerdo_Atras,   LOW );

  analogWrite(pinPotMotorESQ , veloESQ1);
  analogWrite(pinPotMotorDIR , veloDIR1);
}

//Função que faz o carrinho andar para tras
void TRAS(){
  digitalWrite(MotorDireito_Frente,    LOW );
  digitalWrite(MotorDireito_Atras,    HIGH );
  digitalWrite(MotorEsquerdo_Frente,   LOW );
  digitalWrite(MotorEsquerdo_Atras,   HIGH );

  analogWrite(pinPotMotorESQ , 130);
  analogWrite(pinPotMotorDIR , 105);
}
//Função que faz o carrinho andar para a direita
//Para virar a direita o motor o direito é desativado e o da esquerdo ativado
void DIREITA(){
  digitalWrite(MotorDireito_Frente,  HIGH );
  digitalWrite(MotorDireito_Atras,    LOW );
  digitalWrite(MotorEsquerdo_Frente, HIGH );
  digitalWrite(MotorEsquerdo_Atras,   LOW );

  analogWrite(pinPotMotorESQ , veloZero);
  analogWrite(pinPotMotorDIR , veloCurvD);
}

//Função que faz o carrinho andar para a esquerda
//Para virar a esquerda o motor o esquerdo é desativado e o da direito ativado
void ESQUERDA(){
  digitalWrite(MotorDireito_Frente,  HIGH );
  digitalWrite(MotorDireito_Atras,    LOW );
  digitalWrite(MotorEsquerdo_Frente, HIGH );
  digitalWrite(MotorEsquerdo_Atras,   LOW );

  analogWrite(pinPotMotorESQ , veloCurvE);
  analogWrite(pinPotMotorDIR , veloZero);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//___________________________________Definição das Funçoes Primarias do motor________________________________

//___________________________________________________SETUP GERAL_____________________________________________

void setup() {
//Definição dos Modos de pino
//INPUT = Entrada de Dados
//OUTPUT = Saída de Dados


//Definição pinos dos motores como SAIDA
  pinMode(MotorDireito_Frente,	OUTPUT);
	pinMode(MotorDireito_Atras,	  OUTPUT);
	pinMode(MotorEsquerdo_Frente, OUTPUT);
	pinMode(MotorEsquerdo_Atras,   OUTPUT);
  
//Definição de Potencias dos motores como SAIDA
  pinMode(pinPotMotorESQ,   OUTPUT);
  pinMode(pinPotMotorDIR,   OUTPUT);

//Definição dos Sensores como ENTRAGA
  pinMode(sensorDIREITO , INPUT);
  pinMode(sensorESQUERDO , INPUT);
  pinMode(sensorCENTRAL , INPUT);

  delay(3000);
//_________________________________iNICIALIZAÇÃO DO LOG________________________________ 

  //Serial.begin(9600);
 // Serial.println("-------- iniciando LOG ---------");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//__________________________________________Código que irá se repetir dentro da função Loop_______________________________________

void loop(){
Dados_SensorCENTRAL = analogRead(sensorCENTRAL);
Dados_SensorDIREITO = analogRead(sensorDIREITO);
Dados_SensorESQUERDO = analogRead(sensorESQUERDO);
  if(Dados_SensorCENTRAL <= linear && Dados_SensorESQUERDO >= linear && Dados_SensorDIREITO >= linear )
  {
  FRENTE();
  }
  //caso o sensor vermelho esteja na linha branca, virar para a direita para o carrinho ficar reto
  if(Dados_SensorCENTRAL >= linear && Dados_SensorESQUERDO >= linear && Dados_SensorDIREITO <= linear )
  {
  DIREITA();
  }
  //caso o sensor amarelo esteja na linha branca, virar para a esquerda para o carrinho ficar reto
  if(Dados_SensorCENTRAL >= linear && Dados_SensorESQUERDO <= linear && Dados_SensorDIREITO >= linear )
  {
  ESQUERDA(); 
  }
  //cruzamento de Linhas
  if(Dados_SensorCENTRAL <= linear && Dados_SensorESQUERDO <= linear && Dados_SensorDIREITO <= linear )
  {
  FRENTE();
  }
  //Caso saia da linha
  /*if(Dados_SensorCENTRAL > limiar2 && Dados_SensorESQUERDO > limiar2 && Dados_SensorDIREITO > limiar2 )
  {
  TRAS();
  }*/
  //direita 2
  if(Dados_SensorCENTRAL <= linear && Dados_SensorESQUERDO >= linear && Dados_SensorDIREITO <= linear )
  {
  DIREITA();
  }
  //esquerda 27
  if(Dados_SensorCENTRAL <= linear && Dados_SensorESQUERDO <= linear && Dados_SensorDIREITO >= linear )
  {
  ESQUERDA(); 
  }
  if(millis()>=tempo)
  {
  PARADO();
  }


}