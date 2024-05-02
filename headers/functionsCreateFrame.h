void putLineFrame(int averageOfCountCaracteres, int maxLenghtCaracteres){
    int putFrameWall = 1;
    centerAxeXTerminal(averageOfCountCaracteres,putFrameWall);
    for(int i = 0 ; i < (maxLenghtCaracteres + averageOfCountCaracteres) - 1 ; i++){
        printf(" ");
    }
    printf("\x1b[31;101m"); 
    printf(" ");
    printf("\x1b[0m");
    printf("\n");

}

void printTopFrame(int averageOfCountCaracteres, int maxLenghtCaracteres){
    int putFrameWall = 0;
    centerAxeXTerminal(averageOfCountCaracteres*2,putFrameWall);
    printf("\x1b[31;101m"); 

    for(int i = 0 ; i < (2*averageOfCountCaracteres) + maxLenghtCaracteres ; i++){
        printf(" ");
    }
    printf("\x1b[0m");
    printf("\n");

    putLineFrame(averageOfCountCaracteres,maxLenghtCaracteres);
    
}

void printBottomFrame(int averageOfCountCaracteres, int maxLenghtCaracteres){
    putLineFrame(averageOfCountCaracteres,maxLenghtCaracteres);

    int putFrameWall = 0;
    centerAxeXTerminal(averageOfCountCaracteres*2,putFrameWall);
    printf("\x1b[31;101m"); 

    for(int i = 0 ; i < (2*averageOfCountCaracteres) + maxLenghtCaracteres ; i++){
        printf(" ");
    }
    printf("\x1b[0m");
    printf("\n\n");

}



