#include "mapRegisters.h"

unsigned int setBit(unsigned int registrador , int bit){
  return registrador | (0x1 << bit);
}

unsigned int clearBit(unsigned int registrador , int bit){
  return registrador & ~(0x1 << bit);
}

void setDisplaySpeed(unsigned int speed){
  unsigned int mascara = (0x77 << 3) ;
  *hardware.registradores[0] &= ~mascara;
  *hardware.registradores[0] |= (speed << 3);
}

void onOffDisplay(unsigned int mode){
  *hardware.registradores[0] = mode ? setBit(*hardware.registradores[0],0) : clearBit(*hardware.registradores[0],0);
}

void setOperationLed(unsigned int mode){
  *hardware.registradores[0] =mode ? setBit(*hardware.registradores[0],9) : clearBit(*hardware.registradores[0],9);
}

void reset(unsigned int mode){
 *hardware.registradores[0] = mode ? setBit(*hardware.registradores[0],13) : clearBit(*hardware.registradores[0],13);
}

void setDisplayMode(unsigned int mode){
  unsigned int mascara = (0x3 << 1) ;

  *hardware.registradores[0] &= ~mascara;
  *hardware.registradores[0] |= (mode << 1);
}

void setLedStatus(unsigned int color){
  unsigned mascara = (0x7 << 10);
  *hardware.registradores[0] &= ~mascara;
  *hardware.registradores[0] |= (0x1 << 9 + color);
}

void setRedDisplay(unsigned int redColorIntesive){
  unsigned int mascara = (0xFF);
  *hardware.registradores[1] &= ~mascara;
  *hardware.registradores[1] |= redColorIntesive;
}

void setGreenDisplay(unsigned int greencolorIntesive){
  unsigned int mascara = (0xFF << 8);
  *hardware.registradores[1] &= ~mascara;
  *hardware.registradores[1] |= (greencolorIntesive << 8);
}

void setBlueDisplay(unsigned int blueColorIntesive){
  unsigned int mascara = (0xFF);
  *hardware.registradores[2] &= ~mascara;
  *hardware.registradores[2] |= (blueColorIntesive);
}

void setBateryLevel(unsigned int level){
  unsigned int mask = (0x3);
  *hardware.registradores[3] &= ~mask;
  *hardware.registradores[3] |= level;
}

void countSlidingDisplayMessages(unsigned int count){
  unsigned int mask = (0xF << 2);
  *hardware.registradores[3] &= ~mask;
  *hardware.registradores[3] |= (count << 2);
}

void setTemperature(unsigned int temperature){
  // temperature /= 10;
  unsigned int mask = (0x3FF << 6);
  *hardware.registradores[3] &= ~mask;

  if(temperature < 0)
    temperature = ~temperature + 1;

  *hardware.registradores[3] |= (temperature << 6);
  printf("register 4  0x%02x\n", *hardware.registradores[4]);
  printf("register 5  0x%02x\n", *hardware.registradores[5]);
  printf("register 6  0x%02x\n", *hardware.registradores[6]);
  printf("register 7  0x%02x\n", *hardware.registradores[7]);
  printf("register 8  0x%02x\n", *hardware.registradores[8]);
  printf("register 9  0x%02x\n", *hardware.registradores[9]);
  printf("register 10  0x%02x\n", *hardware.registradores[10]);
  printf("register 11  0x%02x\n", *hardware.registradores[11]);
  printf("register 12  0x%02x\n", *hardware.registradores[12]);
  printf("register 13  0x%02x\n", *hardware.registradores[13]);
  printf("register 14  0x%02x\n", *hardware.registradores[14]);
  printf("register 15  0x%02x\n", *hardware.registradores[15]);


}

void setLetter(unsigned int letter, unsigned short *registrador, int bitShift){
  unsigned int mask = (0xFF << bitShift);
  *registrador &= ~mask;
  *registrador |= (letter << bitShift);
}

void setDisplayWord(char word[100]){
  char letter = ' ';
  int indexRegister = 0 , i = 0;
  int bitShift = 0;
  for(i = 0 ; i < strlen(word) ; i++){

    letter = word[i];
    bitShift = i % 2 == 0 ? 0 : 8;
    indexRegister = i % 2 == 0 && i != 0 ? indexRegister++ : indexRegister;

    // printf("letter %c\n", letter);
    setLetter(letter, hardware.registradores[4 + indexRegister],bitShift);
    // *hardware.registradores[4 + indexRegister] = letter;
  }

  bitShift = 0;
  for(int j = i ; j < 16 ; j++){
    bitShift = i % 2 == 0 ? 0 : 8;
    indexRegister = j % 2 == 0 ? indexRegister++ : indexRegister;

    setLetter(0x00,hardware.registradores[4 + indexRegister],bitShift);
  }

}