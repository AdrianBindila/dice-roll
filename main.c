#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
// aici as extrage pula in pizda ma-tii
void generateSeed() {
    int pid = getpid();
    time_t sysTime = time(NULL);
    srand(pid ^ sysTime);
}

int roll() {
    return rand() % 6 + 1;
}

int getDiceRoll() {
    int die = roll();
    printf("Rolled a %d!\n", die);
    return die;
}

int getConvincingRoll(int playerRoll) {
    if (playerRoll == 6) {
        return playerRoll;
    }

    int diff = 6 - playerRoll;
    return playerRoll + rand() % diff + 1;//boost the value to something higher than the player
}

void playGame() {

    printf("Press any key to start!\n");
    getchar();
    int playerRoll = roll();
    int cpuRoll = roll();
    printf("Rolling by your hand... %d\n", playerRoll);

    //if another random number is divisible by 13... cheat
    if (rand() % 13 == 0) {
        printf("Rolling by the CPU's hands...%d\nCPU WINS!\n", getConvincingRoll(playerRoll));
        return;
    } else {
        printf("Rolling by the CPU's hand... %d\n", cpuRoll);
    }

    if (cpuRoll > playerRoll) {
        printf("CPU WINS!\n");
    } else {
        printf("PLAYER WINS!\n");
    }
}

void printStats(int player, int cpu) {
    printf("====== STATS ======\n");
    printf("Player: %3d [", player);
    for (int i = 0; i < player / 10; i++) {
        printf("=");
    }
    printf("]\n");
    printf("CPU:    %3d [", cpu);
    for (int i = 0; i < cpu / 10; i++) {
        printf("=");
    }
    printf("]\n");
}

void playBarbut() {
    printf("Bets are 10 lei each...\n");

    int playerMoney = 0;
    char moneyString[32];

    player:
    printf("Insert YOUR number of funds: ");
    scanf("%16s", moneyString);
    playerMoney = strtol(moneyString, NULL, 10);
    if (playerMoney < 10) {
        printf("Insert a number greater or equal to 10!\n");
        goto player;
    }

    int cpuMoney = 0;

    cpu:
    printf("\nInsert CPU's number of funds: ");
    scanf("%16s", moneyString);
    cpuMoney = strtol(moneyString, NULL, 10);
    if (cpuMoney < 10) {
        printf("Insert a number greater or equal to 10!\n");
        goto cpu;
    }

    printf("\n");
    printf("Press ENTER to continue...\n");
    getchar();
    getchar();
    int roundCount = 1;
    while (playerMoney > 0 && cpuMoney > 0) {
        printf("====== ROUND %d ======\n", roundCount++);
        printf("[Player] ");
        int playerRoll = getDiceRoll();
        printf("[CPU] ");
        int cpuRoll = getDiceRoll();
        if (playerRoll == cpuRoll) {
            printf("Stalemate! No money changes hands!\n");
        } else if (playerRoll > cpuRoll) {
            printf("Player wins the round!\n");
            playerMoney += 10;
            cpuMoney -= 10;
        } else {
            printf("CPU wins the round!\n");
            playerMoney -= 10;
            cpuMoney += 10;
        }
        getchar();
        printStats(playerMoney, cpuMoney);
        if (playerMoney > 0 && cpuMoney > 0) {
            printf("Keep playing?\n");
            getchar();
        }
    }
    if (playerMoney > 0) {
        printf("Player WINS the big money!");
    } else {
        printf("CPU steals player's money!");
    }
}

void rollHundred() {
    int frq[7] = {0};
    for (int i = 0; i < 100; i++) {
        frq[getDiceRoll()]++;
    }
    printf("Summary:\n");
    printf("|  1 |  2 |  3 |  4 |  5 |  6 |\n");
    for (int i = 1; i <= 6; i++) {
        printf("| %2d ", frq[i]);
    }
    printf("|\n");
}

int main(int argc, char *argv[]) {
    generateSeed();
    printf("Welcome to dice roll!\n");

    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0) {
            printf("Usage: Just run the application or use --roll, --play, --hundred, --barbut to directly select an option");
        } else if (strcmp(argv[1], "--roll") == 0) {
            getDiceRoll();
        } else if (strcmp(argv[1], "--play") == 0) {
            playGame();
        } else if (strcmp(argv[1], "--hundred") == 0) {
            rollHundred();
        } else if (strcmp(argv[1], "--barbut") == 0) {
            playBarbut();
        }
    } else {
        printf("You may choose to:\n 1) roll the dice\n 2) play against the computer\n 3) roll 100 times at once\n 4) play barbut");
        char opt = (char) getchar();
        switch (opt) {
            case '1':
                getDiceRoll();
                break;
            case '2':
                playGame();
                break;
            case '3':
                rollHundred();
                break;
            case '4':
                playBarbut();
                break;
            default:
                printf("Please choose a valid option!");
                break;
        }
    }
    return 0;
}
