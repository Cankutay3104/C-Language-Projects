

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char first_player_decision();
int score_calculator(int, int, int, int, int);
int roll_a_dice();
int play_computer(int, int);
int play_user(int, int);
void scoresheet(int, int, int);

int main(){

    int total_rounds, round_counter = 1;
    int comp_total_score = 0;
    int user_total_score = 0;

    srand(time(NULL));

    printf("Welcome to Generala game.\n");
    printf("Let's get started.\n"),
            printf("How many rounds would you like to play?: ");
    scanf("%d", &total_rounds);

    char first_player = first_player_decision();

    if(first_player == 'c') {
        comp_total_score += play_computer(round_counter, comp_total_score);
        if(comp_total_score == 50) {
            total_rounds = 0;
            printf("\nI got generala in the first roll!");
        }
        user_total_score += play_user(round_counter, user_total_score);
        if(user_total_score == 50) {
            total_rounds = 0;
            printf("\nYou got generala in the first roll!");
        }
    }
    else {
        user_total_score += play_user(round_counter, user_total_score);
        if(user_total_score == 50) {
            total_rounds = 0;
            printf("\nYou got generala in the first roll!");
        }
        comp_total_score += play_computer(round_counter, comp_total_score);
        if(comp_total_score == 50) {
            total_rounds = 0;
            printf("\nI got generala in the first roll!");
        }
    }

    scoresheet(round_counter, comp_total_score, user_total_score);

    total_rounds -= 1;
    round_counter += 1;

    /* I used pre-test loop. The difference is pre-test loop tests
       before the iteration; but, post-test loop tests the
       condition after the iteration.
    */
    while(total_rounds > 0){

        if(first_player == 'c') {
            comp_total_score += play_computer(round_counter, comp_total_score);
            user_total_score += play_user(round_counter, user_total_score);
            if(comp_total_score == 50)
                total_rounds = 0;
            if(user_total_score == 50)
                total_rounds = 0;
        }
        else {
            user_total_score += play_user(round_counter, user_total_score);
            comp_total_score += play_computer(round_counter, comp_total_score);
            if(comp_total_score == 50)
                total_rounds = 0;
            if(user_total_score == 50)
                total_rounds = 0;
        }

        scoresheet(round_counter, comp_total_score, user_total_score);

        total_rounds -= 1;
        round_counter += 1;
    }

    if(comp_total_score < user_total_score)
        printf("YOU ARE THE WINNER!");
    else if(comp_total_score > user_total_score)
        printf("I AM THE WINNER!");
    else
        printf("IT IS EVEN!");

    return 0;
}

char first_player_decision(){

    int comp_roll1, comp_roll2, comp_rolls, user_roll1, user_roll2, user_rolls;

    do {
        comp_roll1 = roll_a_dice();
        comp_roll2 = roll_a_dice();
        comp_rolls = comp_roll1 + comp_roll2;

        user_roll1 = roll_a_dice();
        user_roll2 = roll_a_dice();
        user_rolls = user_roll1 + user_roll2;

        printf("\nI have rolled the dice and got %d and %d!", comp_roll1, comp_roll2);
        printf("\nI have rolled the dice for you and got %d and %d!", user_roll1, user_roll2);

    }while(comp_rolls == user_rolls);

    if (comp_rolls < user_rolls)
        return 'u';
    else
        return 'c';
}

int score_calculator(int d1, int d2, int d3, int d4, int d5) {

    int ones = 0;
    int twos = 0;
    int threes = 0;
    int fours = 0;
    int fives = 0;
    int sixes = 0;

    if (d1 == 1) ones++;
    else if (d1 == 2) twos++;
    else if (d1 == 3) threes++;
    else if (d1 == 4) fours++;
    else if (d1 == 5) fives++;
    else if (d1 == 6) sixes++;

    if (d2 == 1) ones++;
    else if (d2 == 2) twos++;
    else if (d2 == 3) threes++;
    else if (d2 == 4) fours++;
    else if (d2 == 5) fives++;
    else if (d2 == 6) sixes++;

    if (d3 == 1) ones++;
    else if (d3 == 2) twos++;
    else if (d3 == 3) threes++;
    else if (d3 == 4) fours++;
    else if (d3 == 5) fives++;
    else if (d3 == 6) sixes++;

    if (d4 == 1) ones++;
    else if (d4 == 2) twos++;
    else if (d4 == 3) threes++;
    else if (d4 == 4) fours++;
    else if (d4 == 5) fives++;
    else if (d4 == 6) sixes++;

    if (d5 == 1) ones++;
    else if (d5 == 2) twos++;
    else if (d5 == 3) threes++;
    else if (d5 == 4) fours++;
    else if (d5 == 5) fives++;
    else if (d5 == 6) sixes++;

    if (ones == 5 || twos == 5 || threes == 5 || fours == 5 || fives == 5 || sixes == 5) {
        printf("\nGenerala!");
        return 50;
    }

    else if (ones == 4 || twos == 4 || threes == 4 || fours == 4 || fives == 4 || sixes == 4)
        return 40;

    else if ((ones == 3 || twos == 3 || threes == 3 || fours == 3 || fives == 3 || sixes == 3) &&
             (ones == 2 || twos == 2 || threes == 2 || fours == 2 || fives == 2 || sixes == 2))
        return 30;

    else if ((ones == 1 && twos == 1 && threes == 1 && fours == 1 && fives == 1) || ( twos == 1 && threes == 1 && fours == 1 && fives == 1 && sixes == 1))
        return 20;

    else {
        int result1 = ones * 1;
        int result2 = twos * 2;
        int result3 = threes * 3;
        int result4 = fours * 4;
        int result5 = fives * 5;
        int result6 = sixes * 6;

        int maximum = 0;

        if (maximum < result1)
            maximum = result1;

        if (maximum < result2)
            maximum = result2;

        if (maximum < result3)
            maximum = result3;

        if (maximum < result4)
            maximum = result4;

        if (maximum < result5)
            maximum = result5;

        if (maximum < result6)
            maximum = result6;

        return maximum;
    }
}


/* The datatype I used in the below function is integer
   because we don't need fractions in this program.
*/
int roll_a_dice(){

    int dice_value;

    dice_value = 1 + (int)rand() % 6;

    return dice_value;
}


int play_computer(int round_counter, int comp_total_score){

    int dice1 = roll_a_dice();
    int dice2 = roll_a_dice();
    int dice3 = roll_a_dice();
    int dice4 = roll_a_dice();
    int dice5 = roll_a_dice();

    printf("\n\nRound %d -- My Turn:", round_counter);
    printf("\n---------------------------------------------------------\n");
    printf("I rolled them and I got\n");
    printf("[Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d", dice1, dice2, dice3, dice4, dice5);

    if(dice1 == dice3 && dice1 == dice4 && dice1 == dice2 && dice1 != dice5) {
        dice5 = roll_a_dice();
        printf("\nI rolled them and I got\n");
        printf("[Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d", dice1, dice2, dice3, dice4, dice5);
    }
    else if(dice1 == dice3 && dice1 == dice4 && dice1 == dice5 && dice1 != dice2){
        dice2 = roll_a_dice();
        printf("\nI rolled them and I got\n");
        printf("[Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d", dice1, dice2, dice3, dice4, dice5);
    }
    else if(dice2 == dice3 && dice2 == dice4 && dice2 == dice5 && dice2 != dice1){
        dice1 = roll_a_dice();
        printf("\nI rolled them and I got\n");
        printf("[Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d", dice1, dice2, dice3, dice4, dice5);
    }
    else if(dice1 == dice2 && dice1 == dice4 && dice1 == dice5 && dice1 != dice3){
        dice3 = roll_a_dice();
        printf("\nI rolled them and I got\n");
        printf("[Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d", dice1, dice2, dice3, dice4, dice5);
    }
    else if(dice1 == dice2 && dice1 == dice3 && dice1 == dice5 && dice1 != dice4){
        dice4 = roll_a_dice();
        printf("\nI rolled them and I got\n");
        printf("[Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d", dice1, dice2, dice3, dice4, dice5);
    }


    int this_round_score = score_calculator(dice1, dice2, dice3, dice4, dice5);
    comp_total_score += this_round_score;

    printf("\nMy Score: %d\tTotal Score: %d", this_round_score, comp_total_score);

    return this_round_score;
}


/*
    The function below returns an integer value because in my program
    I am doing addition in the main function. Therefore, I need an integer value.
*/
int play_user(int round_counter, int user_total_score){

    int dice1 = roll_a_dice();
    int dice2 = roll_a_dice();
    int dice3 = roll_a_dice();
    int dice4 = roll_a_dice();
    int dice5 = roll_a_dice();
    char decision;
    int temp = 2;

    printf("\n\nRound %d -- Your Turn:", round_counter);
    printf("\n---------------------------------------------------------\n");
    printf("You got [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d ", dice1, dice2, dice3, dice4, dice5);

    while(temp != 0){
        printf("\nShall I roll for you (Y/N)? ");
        scanf(" %c", &decision);

        if(decision == 'N'){
            temp = 0;
        }
        else if(decision == 'Y'){

            int kept1, kept2;

            do{

                printf("\nWhich ones do you want to keep? ");
                scanf("%d %d", &kept1, &kept2);

                if(kept1 < 1 || kept1 > 5 || kept2 < 1 || kept2 > 5)
                    printf("\nInvalid numbers! Please choose again!");
            }while(kept1 < 1 || kept1 > 5 || kept2 < 1 || kept2 > 5);

            for (int i = 1; i <= 5; i++) {
                if (i != kept1 && i != kept2) {
                    if (i == 1) dice1 = roll_a_dice();
                    else if (i == 2) dice2 = roll_a_dice();
                    else if (i == 3) dice3 = roll_a_dice();
                    else if (i == 4) dice4 = roll_a_dice();
                    else dice5 = roll_a_dice();
                }
            }
            printf("You got [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d ", dice1, dice2, dice3, dice4, dice5);

            temp -= 1;
        }
        else {
            printf("\nInvalid input! Please enter either Y or N!");
        }
    }

    int this_round_score = score_calculator(dice1, dice2, dice3, dice4, dice5);
    user_total_score += this_round_score;

    printf("\nYour Score: %d\tTotal Score: %d", this_round_score, user_total_score);

    return this_round_score;
}


void scoresheet(int round_counter, int comp_total_score, int user_total_score){

    printf("\n\nOur scoresheet after round %d:\n=============================\n", round_counter);
    printf("My Score\tYour Score\n%d\t \t%d\n", comp_total_score, user_total_score);
}