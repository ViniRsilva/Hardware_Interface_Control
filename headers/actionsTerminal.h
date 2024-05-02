/* System UNIX or WIN */ 
#ifdef __unix__         
    #define c "clear"

#elif defined(_WIN32) || defined(WIN32) 
    #define c "cls"

#endif

void printFrameLastWall(int averageOfCountCaracteres , int leghtStrToPrint, int maxLeghtStrToPrint){
    for(int i = 0; i < averageOfCountCaracteres + (maxLeghtStrToPrint - leghtStrToPrint) -1 ; i++){
        printf(" ");
    }

    printf("\x1b[31;101m"); 
    printf(" ");
    printf("\x1b[0m");
    printf("\n");
}

void countCharacterLenght(char contentTerminal[][100] ,int lenght, int *averageLenght, int *max){
    int sum = 0 ;
    *max = strlen(contentTerminal[0]);
    for(int i=0; i< lenght ; i++){
        sum += strlen(contentTerminal[i]);
        *max = strlen(contentTerminal[i]) > *max ? strlen(contentTerminal[i]) : *max;
    }   

    *averageLenght = sum / lenght;
    // int result[] = {(sum / lenght),max};
    // return result;
}

/**
 * Clear the terminal of UNIX system and win System
 */
void clearTerminal(){
    system(c);
}

/**
 * Center the text in the termial gettin the width in columns e the height in rowns of the terminal
 */
void centerAxeYTerminal(){

    clearTerminal();

    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int height = w.ws_row;

    for(int i = 0 ; i < (height * 0.2)  ; i++){
        printf("\n");
    }
}

/**
 * @param {int} lenght - lenght of the phase that will be printed in the terminal
 */
void centerAxeXTerminal(int lenght, int putFrameWall){

    // clearTerminal();
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    int width = w.ws_col;
    for(int i = 0 ; i < (width /2) - lenght; i++){
        if(i == (width /2) - 2 * lenght && putFrameWall)
          printf("\x1b[31;101m");
        
        printf(" ");

        printf("\x1b[0m");
    }
}

void printInCenter(char textToPrint[], int averageOfCountCaracteres, int maxLenghtCaracteres){
    int putFrameWall = 1;
    centerAxeXTerminal(averageOfCountCaracteres,putFrameWall);
    printf("%s",textToPrint);
    printFrameLastWall(averageOfCountCaracteres,strlen(textToPrint),maxLenghtCaracteres);
}

