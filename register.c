#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#include "headers/teste.h"
#include "headers/actionsTerminal.h"
#include "headers/functionsCreateFrame.h"
#include "headers/menus.h"

int actionsR0(int action) {
  unsigned int actionValue;

  printf("Digite sua opcao : ");
  scanf("%d", & actionValue);

  switch (action) {
  case 1:
    onOffDisplay(actionValue);
    break;
  case 2:
    setDisplayMode(actionValue);
  case 3:
    setDisplaySpeed(actionValue);
    break;
  case 4:
    setOperationLed(actionValue);
    break;
  case 5:
    setLedStatus(actionValue);
    break;
  case 6:
    reset(actionValue);
    break;
  }

}

void actionsR1(int action) {
  unsigned int colorValue;

  char colors[][9] = { {"Vermelho"},{"Verde"}, {"Azul"} };

  printf("Digite um valor para a %s do display : ", colors[action - 1]);
  scanf("%d", & colorValue);

  switch (action) {
  case 1:
    setRedDisplay(colorValue);
    break;
  case 2:
    setGreenDisplay(colorValue);
    break;
  }
}

void actionsR2(int action) {
  unsigned int colorValue;

  char colors[][9] = { {"Vermelho"},{"Verde"}, {"Azul"} };

  printf("Digite um valor para a %s do display : ", colors[action - 1]);
  scanf("%d", & colorValue);

  switch (action) {
  case 3:
    setBlueDisplay(colorValue);
    break;
  }
}

void actionsR3(int action){
    unsigned int actionValue;

    printf("Digite sua opcao : ");
    scanf("%x", &actionValue);

    switch(action){
      case 1:
        setBateryLevel(actionValue);
        break;
      case 2: 
        countSlidingDisplayMessages(actionValue);
        break;
      case 3:
        setTemperature(actionValue);
        break;
    }

}

void setWordInDisplay(){
  char word[100];
  printf("Digite uma palavra : ");
  scanf("%s", word);
  setDisplayWord(word);
}

void clearBuffer() {
  char ch;
  do {
    ch = fgetc(stdin);
  } while (ch != '\n' && ch != EOF);
}

int main() {

  initializeRegisters();
  int fd;
  char * map = registers_map(FILE_PATH, FILE_SIZE, & fd);

  if (map == NULL) {
    return EXIT_FAILURE;
  }

  int action = 0, actionValue = 0, numMenu = 0;
  menu();
  printf("Digite sua opcao : ");
  scanf("%d", & numMenu);

  clearBuffer();
  clearTerminal();

  switch (numMenu) {
  case 1:
    menuLigDeslDisplay();
    action = 1;
    actionsR0(action);
    break;
  case 2:
    menuModoExibicao();
    action = 2;
    actionsR0(action);
    break;
  case 3:
    menuDisplaySpeed();
    action = 3;
    actionsR0(action);
    break;
  case 4:
    menuLigDeslLedOperacao();
    action = 4;
    actionsR0(action);
    break;
  case 5:
    menuLedStatus();
    action = 5;
    actionsR0(action);
    break;
  case 6:
    menuReset();
    action = 6;
    actionsR0(action);
    break;
  case 7:
    menuRgbDisplay( & action);
    printf("%d\n", action);
    action == 3 ? actionsR2(action) : actionsR1(action);
    break;
  case 8:
    menuBateryLevel();
    action = 1;
    actionsR3(action);
    break;
  case 9:
    menuCountDisplayMessages();
    action = 2;
    actionsR3(action);
    break;
  case 10:
    menuSetTemperature();
    action = 3;
    actionsR3(action);

  case 11:
    menuSetWordInDisplay();
    setWordInDisplay();
  default:

    break;
  }

  // Release resources
  if (registers_release(map, FILE_SIZE, fd) == -1) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}