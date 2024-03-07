#include <stdio.h>
#include <stdlib.h>

// prints different scoring combinations for a given NFL score n
void scoringCombinations(int n) {
    // loop in descending order to find all combinations
    // similar in concept to the coin change problem
    // use a nested loop of sums beneath the total to figure out how much of each play
    // forgoing the {} for readability
    for (int td2p = 0; td2p * 8 <= n; td2p++)
        for (int td1p = 0; td1p * 7 + td2p * 8 <= n; td1p++)
            for (int td0p = 0; td0p * 6 + td1p * 7 + td2p * 8 <= n; td0p++)
                for (int fg = 0; fg * 3 + td0p * 6 + td1p * 7 + td2p * 8 <= n; fg++)
                    for (int sf = 0; sf * 2 + fg * 3 + td0p * 6 + td1p * 7 + td2p * 8 <= n; sf++)
                        if (+ sf * 2 + fg * 3 + td0p * 6 + td1p * 7 + td2p * 8 == n)
                            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", td2p, td1p, td0p, fg, sf);
}


int main() {
    int userIn;
    
    // initial prompt
    printf("Enter 0 or 1 to STOP\n");
    printf("Enter the NFL score: ");
    scanf("%d", &userIn);

    while (userIn > 1) {
        printf("Possible combinations of scoring plays: \n");

        // print scoring combos
        scoringCombinations(userIn);
        // re-prompt user
        printf("\nEnter 0 or 1 to STOP\n");
        printf("Enter the NFL score: ");
        scanf("%d", &userIn);
    }
    return 0;
}
