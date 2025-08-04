#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char characters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                         'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char charactersValues[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                               1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    // for (int i = 0 ; i < strlen(characters) - 2; i++)
    // {
    //     printf("%c , %d\n", characters[i], charactersValues[i]);
    // }

    string player1Input = get_string("Player 1: ");
    string player2Input = get_string("Player 2: ");

    int player1Score = 0;
    int player2Score = 0;

    for (int i = 0; i < strlen(player1Input); i++)
    {
        player1Input[i] = toupper(player1Input[i]);
        for (int j = 0; j < strlen(characters) - 2; j++)
        {
            player1Score = (player1Input[i] == characters[j]) ? player1Score + charactersValues[j]
                                                              : player1Score;
        }
    }

    for (int i = 0; i < strlen(player2Input); i++)
    {
        player2Input[i] = toupper(player2Input[i]);
        for (int j = 0; j < strlen(characters) - 2; j++)
        {
            player2Score = (player2Input[i] == characters[j]) ? player2Score + charactersValues[j]
                                                              : player2Score;
        }
    }

    if (player1Score != player2Score)
    {
        printf("%s", player1Score > player2Score ? "Player 1 wins!\n" : "Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
