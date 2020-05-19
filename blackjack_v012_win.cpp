#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <chrono>
#include <random>
using namespace std;

/* Blackjack

This game will be a simple* game where the computer (dealer) will deal two cards to the player (user). The player will have the 
choice to hit, stand, or split (if cards are identical and != A).

*Simple in appearance, not in execution..

Array will contain 52 numbers:
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A * 4 each

numbers will be radnomly assigned to the array (shuffled) and dealt from i = 0, 1 and so on.

Impliment a method of scoring cards:

cards > 10:
J = 10,
Q = 10,
K = 10,
A = 11 || 1.

If A is dealt if player or dealer cards equal > 21, A = 1, else, A = 1.

Need to keep a running total of dealer and player cards, however, if A is drawn and > 21, it must be equal to 1.

Dealer cards must be kept from user, however, dealer's top card can be seen by player. 

Rules:
if dealer and player tie, it is a push and no one wins.
if player has score higher than dealer and is not bust, player wins.
If player and dealer both bust, the dealer wins.
if player is dealt a blackjack (10 card and ace) and the dealer does not, player wins.

Action:
Hit
Stand,
Double down,
Split,

Dealer will hit on 17 and not more.

 */

// Global constants
const int g_DECK_SIZE = 52; // Row size of array
const int g_COL = 2;        // Col size of array
const int g_CARD_INDEX = 0;
const int g_POINTS_INDEX = 1; // array[52][2] = {{g_CARD_INDEX, g_POINTS_INDEX},...};

// These are global for the runtime of the game. Running is for the entire program, and playerTurn is true when the player is player. When player is false, dealer will play.
bool running = true, reset = false, playerTurn = true, dealerTurn = false;
// Global bools to be used in the progam. Makes the functions more clear by not having to include each one into each function header
bool blackjack = false, bust = false, doubleDown = false, hit = false, stand = false, canSplit = false, handIsSplit = false;

// Function prototypes
void dealCards(int[][g_COL], int[][g_COL], int[][g_COL], int[][g_COL], int, unsigned &, unsigned &, unsigned, unsigned &, int &, int &, int &);
void shuffleDeck(int[][g_COL]);
void cardCounterShuffle(int, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &);
int cardPoints(int);
void dealOneCardPlayer(int[][g_COL], int[][g_COL], int[][g_COL], unsigned &, unsigned &, unsigned, int &, int &);
void dealOneCardDealer(int[][g_COL], int[][g_COL], unsigned &, unsigned &, int &);
void showHandPlayer(const int[][g_COL], const int[][g_COL], unsigned, unsigned);
void showHandDealer(const int[][g_COL], unsigned);
void showDeck(const int[][g_COL]);
int sumHand(const int[][g_COL], int);
void showSum(int);
void checkScore(int);
void playerSplitHand(int[][g_COL], int[][g_COL], unsigned &, unsigned &, int &);
void callBlackjack();
void callBust();
void dealerPlay(int[][g_COL], int[][g_COL], unsigned &, unsigned &, int &);
void declareWinner(int &, int &, int &);
void playAgain();

//**************************************************************************************************************************************************************************
// 3rd array created for splitHand and is functioning.
// TODO: Change A to 1 if dealt a card that busts
// TODO: Focus on getting the game to play correctly. Get the play loop running. IT'S RUNNING
// TODO: Maybe start cleaning up the UI. The system("CLS") function gets a bit messy. Otherwise, it's playable, just not pretty.

// Do this once they game is playable. Don't get too carried away.
// TODO: Split needs to actually split. The card in playerHand[1][0]/[1][1] must be transferred to split[0]0]/[0][1].
// TODO: Display the playerHand and playerSplitHand cards side-by-side and the totals below. (Hand #1   Hand #2) //close enough..
//**************************************************************************************************************************************************************************

int main()
{
    while (running)
    {
        // Clears screen

        const int HAND_SIZE = 10;
        int deck[g_DECK_SIZE][g_COL];
        int playerHand[HAND_SIZE][g_COL] = {0};
        int dealerHand[HAND_SIZE][g_COL] = {0};
        int splitHand[HAND_SIZE][g_COL] = {0};
        unsigned totalNumCardsDealt = 0, numPlayerCards = 0, numPlayerCardsSplit = 0, numDealerCards = 0;
        int playerSum = 0, dealerSum = 0, playerSumSplit = 0;
        int card = 0;
        unsigned choice;
        bool isValid;

        system("CLS");
        dealCards(deck, playerHand, splitHand, dealerHand, HAND_SIZE, totalNumCardsDealt, numPlayerCards,
                  numPlayerCardsSplit, numDealerCards, playerSum, playerSumSplit, dealerSum);

        while (playerTurn)
        {
            // Player should also see dealer's one card.
            // Works
            if (stand)
            {
                playerTurn = false;
                dealerTurn = true;
            }
            else if (bust)
            {
                callBust();
                playerTurn = false;
                dealerTurn = true;
            }
            else if (blackjack)
            {
                callBlackjack();
                playerTurn = false;
                dealerTurn = true;
            }
            else if (canSplit && !handIsSplit)
            {
                do
                {
                    // To be used after initial deal if split is available
                    // Function call: if (split) then this.
                    cout << "1. Hit\n"
                         << "2. Stand\n"
                         << "3. Double down\n"
                         << "4. Split\n\n"
                         << "Enter selection: " << flush;
                    cin >> choice;

                    switch (choice)
                    {
                    case 1:
                        // Clears screen
                        system("CLS");
                        showHandDealer(dealerHand, numDealerCards);
                        showSum(dealerSum);
                        dealOneCardPlayer(deck, playerHand, splitHand, totalNumCardsDealt, numPlayerCards, numPlayerCardsSplit, playerSum, playerSumSplit);
                        isValid = true;
                        break;
                    case 2:
                        stand = true;
                        isValid = true;
                        break;
                    case 3:
                        doubleDown = true;
                        isValid = true;
                        break;
                    case 4:
                        // Clears screen
                        system("CLS");
                        handIsSplit = true;
                        showHandDealer(dealerHand, numDealerCards);
                        showSum(dealerSum);
                        dealOneCardPlayer(deck, playerHand, splitHand, totalNumCardsDealt, numPlayerCards, numPlayerCardsSplit, playerSum, playerSumSplit);
                        playerSplitHand(deck, splitHand, totalNumCardsDealt, numPlayerCardsSplit, playerSumSplit);
                        isValid = true;
                        break;
                    default:
                        if (!cin)
                            cin.clear();

                        system("CLS");
                        cout << "invalid choice.\n";
                        cin.ignore(256, '\n');

                        showHandDealer(dealerHand, numDealerCards);
                        showSum(dealerSum);
                        showHandPlayer(playerHand, splitHand, numPlayerCards, numPlayerCardsSplit);
                        showSum(playerSum);
                        checkScore(playerSum);
                    }
                } while (!isValid);
            }
            else
            {
                do
                {
                    // To be used after initial deal if no split is available and subsequent deals
                    // Function call: else, then this. (Or can be if (!split))
                    cout
                        << "1. Hit\n"
                        << "2. Stand\n"
                        << "3. Double down\n\n"
                        << "Enter selection: " << flush;
                    cin >> choice;

                    switch (choice)
                    {
                    case 1:
                        // Clears screen
                        system("CLS");
                        showHandDealer(dealerHand, numDealerCards);
                        showSum(dealerSum);
                        dealOneCardPlayer(deck, playerHand, splitHand, totalNumCardsDealt, numPlayerCards, numPlayerCardsSplit, playerSum, playerSumSplit);
                        isValid = true;
                        break;
                    case 2:
                        stand = true;
                        isValid = true;
                        break;
                    case 3:
                        doubleDown = true;
                        isValid = true;
                        break;
                    default:
                        if (!cin)
                            cin.clear();

                        system("CLS");
                        cout << "invalid choice.\n";
                        cin.ignore(256, '\n');
                        isValid = false;

                        showHandDealer(dealerHand, numDealerCards);
                        showSum(dealerSum);
                        showHandPlayer(playerHand, splitHand, numPlayerCards, numPlayerCardsSplit);
                        showSum(playerSum);
                        checkScore(playerSum);
                    }
                } while (!isValid);
            }
        }

        if (bust)
        {
            // Let the player see their results before moving on
            cout << "Press enter to contiue...";
            cin.ignore(100, '\n');
            cin.get();
        }
        else if (blackjack)
        {
            // Let the player see their results before moving on
            cout << "Press enter to contiue...";
            cin.ignore(100, '\n');
            cin.get();
        }
        else
            cin.ignore(100, '\n');

        // Clear screen
        system("CLS");
        while (dealerTurn && !playerTurn)
        {
            // Dealer's turn.
            // dealOneCard, and checkScore
            // Dealer will hit <= 17.

            dealerPlay(deck, dealerHand, totalNumCardsDealt, numDealerCards, dealerSum);
            // Dealer now has 2 cards. Show the player its hand.

            // Works
            if (hit)
                continue;

            else if (stand)
                dealerTurn = false;

            else if (blackjack)
            {
                callBlackjack();
                dealerTurn = false;
            }
            else if (bust)
            {
                callBust();
                dealerTurn = false;
            }
        }

        cout << "Press enter to see the results...";
        cin.get();
        system("CLS");

        // Show player and dealer hands and scores
        showHandDealer(dealerHand, numDealerCards);
        showSum(dealerSum);
        showHandPlayer(playerHand, splitHand, numPlayerCards, numPlayerCardsSplit);
        showSum(playerSum);

        declareWinner(playerSum, playerSumSplit, dealerSum);
        playAgain();
    }
}

//***************************
//  Function defintions     *
//***************************

// Working
void playAgain()
{
    char choice;
    bool isValid;

    do
    {
        cout << "Play again? (Y/N): ";
        cin >> choice;
        cin.ignore(100, '\n');
        choice = toupper(choice);

        if (choice == 'Y' || choice == 'N')
        {
            if (choice == 'Y')
            {
                running = true, reset = true, playerTurn = true, dealerTurn = false, blackjack = false, bust = false,
                doubleDown = false, hit = false, stand = false, canSplit = true, handIsSplit = false;
                isValid = true;
            }
            else
                running = false;
            isValid = true;
        }
        else
            cout << "Invalid choice.\n";
    } while (!isValid);

    return;
}

// Working
void declareWinner(int &playerSum, int &playerSumSplit, int &dealerSum)
{
    if (dealerSum <= 21 && playerSum <= 21)
    {
        if (dealerSum > playerSum)
            cout << "You lose!";

        else if (playerSum > dealerSum)
            cout << "You win!";

        else if (dealerSum == playerSum)
            cout << "Push!";
    }
    else if (dealerSum > 21 && playerSum <= 21)
        cout << "You win!";

    else if (dealerSum <= 21 && playerSum > 21)
        cout << "You lose!";

    else
        cout << "You lose!";

    cout << endl;
}

// Working
void dealerPlay(int deck[][g_COL], int hand[][g_COL], unsigned &totalNumCardsDealt, unsigned &numDealerCards, int &dealerSum)
{
    blackjack = false, bust = false, hit = false, stand = false;

    // This will play dealer. All hitting, standing and the like will be processed here and will returned to main for next loop.
    dealOneCardDealer(deck, hand, totalNumCardsDealt, numDealerCards, dealerSum);

    if (dealerSum <= 17)
        hit = true;

    else if (dealerSum > 17 && dealerSum <= 21)
        stand = true;

    else if (dealerSum > 21)
        bust = true;

    if (dealerSum == 21)
        blackjack = true;
}

// Working
void callBlackjack()
{
    // Function call: if (blackjack)
    cout << "BLACK JACK!\n"
         << flush;
}

// Working
void callBust()
{
    // Function call: if (bust)
    cout << "BUST!\n"
         << flush;
}

// Working
void checkScore(int sum)
{
    blackjack = false, bust = false, doubleDown = false, hit = false, stand = false; // Reset at beginning of function

    // assign bool (if any) and return to main().
    if (sum > 21)
    {
        bust = true;
        return;
    }
    else if (sum == 21)
    {
        blackjack = true;
        return;
    }
    else if (sum < 21)
        return;
}

// Working
void showSum(int sum)
{
    cout << "Total: " << sum << "\n\n"
         << flush;
}

// Working
int sumHand(const int hand[][g_COL], int numCards)
{
    int sum = 0;
    for (int i = 0; i < numCards; i++)
    {
        for (int j = 0; j < 1; j++)
            sum += hand[i][g_POINTS_INDEX];
    }
    return sum;
}

// Working
void dealOneCardPlayer(int deck[][g_COL], int playerHand[][g_COL], int splitHand[][g_COL], unsigned &totalNumCardsDealt,
                       unsigned &numPlayerCards, unsigned numPlayerCardsSplit, int &playerSum, int &playerSumSplit)
{
    static unsigned round = 1;
    int i = numPlayerCards;
    int j = totalNumCardsDealt;

    if (reset)
        round = 1;

    if (round == 1)
    {
        playerHand[0][g_CARD_INDEX] = deck[0][g_CARD_INDEX];
        playerHand[0][g_POINTS_INDEX] = deck[0][g_POINTS_INDEX];

        numPlayerCards++;
        totalNumCardsDealt++;
    }
    else if (round > 1)
    {
        playerHand[i][g_CARD_INDEX] = deck[j][g_CARD_INDEX];     // Assigns card [j,0] to [i,0]
        playerHand[i][g_POINTS_INDEX] = deck[j][g_POINTS_INDEX]; // Assigns score of [j,1] to [i, 1]

        numPlayerCards++;
        totalNumCardsDealt++;

        // Before new card is checked for ace
        playerSum = sumHand(playerHand, numPlayerCards);

        // If the card drawn is an ace and the sum is > 21, the points of the ace will be 1 instead of 11.
        if (playerHand[i][g_CARD_INDEX] == 14)
        {
            if (playerSum > 21)
            {
                playerHand[i][g_POINTS_INDEX] = 1;
                playerSum = sumHand(playerHand, numPlayerCards);
            }
        }
        if (handIsSplit)
            playerSplitHand(deck, splitHand, totalNumCardsDealt, numPlayerCardsSplit, playerSumSplit);

        showHandPlayer(playerHand, splitHand, numPlayerCards, numPlayerCardsSplit);
        showSum(playerSum);
        checkScore(playerSum);
    }

    // Check first two cards and see if they are equal. If so, player is allowed to split
    if (round == 2)
    {
        if (playerHand[0][g_CARD_INDEX] == playerHand[1][g_CARD_INDEX])
            canSplit = true;
    }
    round++;
}

// Working
void dealOneCardDealer(int deck[][g_COL], int hand[][g_COL], unsigned &totalNumCardsDealt, unsigned &numDealerCards, int &dealerSum)
{
    static unsigned round = 1;
    int i = numDealerCards;
    int j = totalNumCardsDealt;

    if (reset)
    {
        round = 1;
        reset = false;
    }

    if (round == 1)
    {
        hand[0][g_CARD_INDEX] = deck[j][g_CARD_INDEX];
        hand[0][g_POINTS_INDEX] = deck[j][g_POINTS_INDEX];
        numDealerCards++;
        totalNumCardsDealt++;
    }
    else if (round > 1)
    {
        hand[i][g_CARD_INDEX] = deck[j][g_CARD_INDEX];     // Assigns card [j,0] to [i,0]
        hand[i][g_POINTS_INDEX] = deck[j][g_POINTS_INDEX]; // Assigns score of [j,1] to [i, 1]
        numDealerCards++;
        totalNumCardsDealt++;
    }

    dealerSum = sumHand(hand, numDealerCards);

    // If the card drawn is an ace and the sum is > 21, the points of the ace will be 1 instead of 11.
    if (hand[i][g_CARD_INDEX] == 14)
    {
        if (dealerSum > 21)
        {
            hand[i][g_POINTS_INDEX] = 1;
            dealerSum = sumHand(hand, numDealerCards);
        }
    }

    if (round > 1)
        checkScore(dealerSum);

    showHandDealer(hand, numDealerCards);
    showSum(dealerSum);

    round++;
}

// Working
void dealCards(int deck[][g_COL], int playerHand[][g_COL], int splitHand[][g_COL], int dealerHand[][g_COL], int handSize, unsigned &totalNumCardsDealt,
               unsigned &numPlayerCards, unsigned numPlayerCardsSplit, unsigned &numDealerCards, int &playerSum, int &playerSumSplit, int &dealerSum)
{
    int num = 0;

    shuffleDeck(deck);

    // Deals one card to player, then dealer, then player
    dealOneCardPlayer(deck, playerHand, splitHand, totalNumCardsDealt, numPlayerCards, numPlayerCardsSplit, playerSum, playerSumSplit);
    dealOneCardDealer(deck, dealerHand, totalNumCardsDealt, numDealerCards, dealerSum);
    dealOneCardPlayer(deck, playerHand, splitHand, totalNumCardsDealt, numPlayerCards, numPlayerCardsSplit, playerSum, playerSumSplit);
}

// Working
void playerSplitHand(int deck[][g_COL], int hand[][g_COL], unsigned &totalNumCardsDealt, unsigned &numPlayerCardsSplit, int &playerSumSplit)
{
    unsigned round = 1;
    int i = numPlayerCardsSplit;
    int j = totalNumCardsDealt;

    hand[i][g_CARD_INDEX] = deck[j][g_CARD_INDEX];
    hand[i][g_POINTS_INDEX] = deck[j][g_POINTS_INDEX];
    numPlayerCardsSplit++;
    totalNumCardsDealt++;

    playerSumSplit = sumHand(hand, numPlayerCardsSplit);
    showSum(playerSumSplit);
    checkScore(playerSumSplit);
}

// Working
void showHandPlayer(const int playerHand[][g_COL], const int splitHand[][g_COL], unsigned numPlayerCards, unsigned numSplitCards)
{
    unsigned numDigits = 0,
             highest = 0;
    int cardWidth;
    string cardCap, cardWall = "|";

    // Peak at cards in hand for output formatting
    // for (int i = 0; i < numCards; i++)
    // {
    //     for (int j = 0; j < 1; j++)
    //     {
    //         numDigits = hand[i][j];

    //         if (numDigits > highest)
    //             highest = numDigits;
    //     }
    // }

    // if (sizeof(highest) == 1)
    // {
    //     cardWidth = 2;
    //     cardCap = "____";
    // }
    // else
    // {
    //     cardWidth = 2;
    //     cardCap = "____";
    // }

    cout << "Player Cards:\n"
         << flush;

    if (handIsSplit)
        cout << "\nHand #1:\n"
             << flush;

    // for (int i = 0; i < numCards; i++)
    //     cout << cardCap << " ";
    // cout << endl;

    for (int i = 0; i < numPlayerCards; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            int card = playerHand[i][g_CARD_INDEX];

            if (card == 0)
                break;

            else
            {
                switch (card)
                {
                case 11:
                    cout << "J"
                         //  << " " << hand[i][g_POINTS_INDEX] << "\n"
                         << flush;
                    break;
                case 12:
                    cout << "Q"
                         //  << " " << hand[i][g_POINTS_INDEX] << "\n"
                         << flush;
                    break;
                case 13:
                    cout << "K"
                         //  << " " << hand[i][g_POINTS_INDEX] << "\n"
                         << flush;
                    break;
                case 14:
                    cout << "A"
                         //  << " " << hand[i][g_POINTS_INDEX] << "\n"
                         << flush;
                    break;
                default:
                    cout << playerHand[i][g_CARD_INDEX] /* << " " << hand[i][g_POINTS_INDEX] << "\n" */
                         << flush;
                }
            }
        }
        cout << setw(3) << flush;
    }

    if (handIsSplit)
    {
        cout << "\n\nHand #2:\n"
             << flush;

        // For split hand display
        for (int i = 0; i < numSplitCards; i++)
        {
            for (int j = 0; j < 1; j++)
            {
                int card = splitHand[i][g_CARD_INDEX];

                if (card == 0)
                    break;

                else
                {
                    switch (card)
                    {
                    case 11:
                        cout << "J"
                             //  << " " << hand[i][g_POINTS_INDEX] << "\n"
                             << flush;
                        break;
                    case 12:
                        cout << "Q"
                             //  << " " << hand[i][g_POINTS_INDEX] << "\n"
                             << flush;
                        break;
                    case 13:
                        cout << "K"
                             //  << " " << hand[i][g_POINTS_INDEX] << "\n"
                             << flush;
                        break;
                    case 14:
                        cout << "A"
                             //  << " " << hand[i][g_POINTS_INDEX] << "\n"
                             << flush;
                        break;
                    default:
                        cout << splitHand[i][g_CARD_INDEX] /* << " " << hand[i][g_POINTS_INDEX] << "\n" */
                             << flush;
                    }
                }
            }
            cout << setw(3) << flush;
        }
    }
    cout << "\n\n";
}

// Working
void showHandDealer(const int hand[][g_COL], unsigned numCards)
{
    unsigned numDigits = 0,
             highest = 0;
    int cardWidth;
    string cardCap, cardWall = "|";

    // Peak at cards in hand for output formatting
    // for (int i = 0; i < numCards; i++)
    // {
    //     for (int j = 0; j < 1; j++)
    //     {
    //         numDigits = hand[i][j];

    //         if (numDigits > highest)
    //             highest = numDigits;
    //     }
    // }

    // if (sizeof(highest) == 1)
    // {
    //     cardWidth = 2;
    //     cardCap = "____";
    // }
    // else
    // {
    //     cardWidth = 2;
    //     cardCap = "____";
    // }

    cout << "Dealer cards: \n"
         << flush;

    // for (int i = 0; i < numCards; i++)
    //     cout << cardCap << " ";
    // cout << endl;

    for (int i = 0; i < numCards; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            int card = hand[i][g_CARD_INDEX];

            if (card == 0)
                return;

            else
            {
                switch (card)
                {
                case 11:
                    cout << "J"
                         //  << " " << hand[i][g_POINTS_INDEX] << "\n"
                         << flush;
                    break;
                case 12:
                    cout << "Q"
                         //  << " " << hand[i][g_POINTS_INDEX] << "\n"
                         << flush;
                    break;
                case 13:
                    cout << "K"
                         //  << " " << hand[i][g_POINTS_INDEX] << "\n"
                         << flush;
                    break;
                case 14:
                    cout << "A"
                         //  << " " << hand[i][g_POINTS_INDEX] << "\n"
                         << flush;
                    break;
                default:
                    cout << hand[i][g_CARD_INDEX] /* << " " << hand[i][g_POINTS_INDEX] << "\n" */
                         << flush;
                }
            }
        }
        cout << setw(3) << flush;
    }
    cout << "\n\n";
}

// Working
void showDeck(const int deck[][g_COL])
{
    int card;
    int counter = 0;
    for (int i = 0; i < g_DECK_SIZE; i++)
    {
        for (int j = 1; j < 2; j++)
        {
            card = deck[i][g_CARD_INDEX];

            // Cards over 10 are displayed as letters. Also displays the points of each card.
            switch (card)
            {
            case 11:
                cout << "J"
                     << " " << deck[i][g_POINTS_INDEX] << "\n"
                     << flush;
                break;
            case 12:
                cout << "Q"
                     << " " << deck[i][g_POINTS_INDEX] << "\n"
                     << flush;
                break;
            case 13:
                cout << "K"
                     << " " << deck[i][g_POINTS_INDEX] << "\n"
                     << flush;
                break;
            case 14:
                cout << "A"
                     << " " << deck[i][g_POINTS_INDEX] << "\n"
                     << flush;
                break;
            default:
                cout << deck[i][g_CARD_INDEX] << " " << deck[i][g_POINTS_INDEX] << "\n"
                     << flush;
            }
            counter++;
        }
    }
    // cout << "\n# of Cards\n";
    // cout << counter << "\n\n";
}

// Working
int cardPoints(int num)
{
    int points = 0;

    switch (num)
    {
    case 1:
        points = 1;
        break;
    case 2:
        points = 2;
        break;
    case 3:
        points = 3;
        break;
    case 4:
        points = 4;
        break;
    case 5:
        points = 5;
        break;
    case 6:
        points = 6;
        break;
    case 7:
        points = 7;
        break;
    case 8:
        points = 8;
        break;
    case 9:
        points = 9;
        break;
    case 10:
    case 11:
    case 12:
    case 13:
        points = 10;
        break;
    case 14:
        points = 11;
        break;
    }
    return points;
}

// Working
void shuffleDeck(int deck[][g_COL])
{
    // This function will generate the deck making sure there are 4 of each card in deck

    // Create the seed for the random number generator. mt19937 is more random than srand
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed);
    // Counters
    int card1 = 0, card2 = 0, card3 = 0, card4 = 0, card5 = 0, card6 = 0, card7 = 0,
        card8 = 0, card9 = 0, card10 = 0, cardJ = 0, cardQ = 0, cardK = 0, cardA = 0;
    // Stores the number and score of cards
    int num1 = 0, points = 0;

    // Start assigning cards to deck in random order from 1 to 14
    for (int i = 0; i < g_DECK_SIZE; i++)
    {
        deck[i][g_CARD_INDEX] = (generator() % 14 + 1);

        num1 = deck[i][g_CARD_INDEX];

        // Check the card assigned and count the number of that card already in the deck. If there are already 4 of that card,
        // the iter will be decremented and the card replaced with a new card.
        cardCounterShuffle(num1, card1, card2, card3, card4, card5, card6,
                           card7, card8, card9, card10, cardJ, cardQ, cardK, cardA);

        if (card1 > 4 || card2 > 4 || card3 > 4 || card4 > 4 || card5 > 4 || card6 > 4 || card7 > 4 ||
            card8 > 4 || card9 > 4 || card10 > 4 || cardJ > 4 || cardQ > 4 || cardK > 4 || cardA > 4)
        {
            if (card1 > 4)
            {
                if (num1 == 1)
                    i--;
            }
            else if (card2 > 4)
            {
                if (num1 == 2)
                    i--;
            }
            else if (card3 > 4)
            {
                if (num1 == 3)
                    i--;
            }
            else if (card4 > 4)
            {
                if (num1 == 4)
                    i--;
            }
            else if (card5 > 4)
            {
                if (num1 == 5)
                    i--;
            }
            else if (card6 > 4)
            {
                if (num1 == 6)
                    i--;
            }
            else if (card7 > 4)
            {
                if (num1 == 7)
                    i--;
            }
            else if (card8 > 4)
            {
                if (num1 == 8)
                    i--;
            }
            else if (card9 > 4)
            {
                if (num1 == 9)
                    i--;
            }
            else if (card10 > 4)
            {
                if (num1 == 10)
                    i--;
            }
            else if (cardJ > 4)
            {
                if (num1 == 11)
                    i--;
            }
            else if (cardQ > 4)
            {
                if (num1 == 12)
                    i--;
            }
            else if (cardK > 4)
            {
                if (num1 == 13)
                    i--;
            }
            else if (cardA > 4)
            {
                if (num1 == 14)
                    i--;
            }
        }
    }

    // Assign the points for each card in the deck
    for (int i = 0; i < g_DECK_SIZE; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            num1 = deck[i][g_CARD_INDEX];

            points = cardPoints(num1);
            deck[i][g_POINTS_INDEX] = points;
        }
    }
}

// Working
void cardCounterShuffle(int num1, int &card1, int &card2, int &card3, int &card4,
                        int &card5, int &card6, int &card7, int &card8, int &card9,
                        int &card10, int &cardJ, int &cardQ, int &cardK, int &cardA)
{
    // Counters for cards in deck and returns to shuffleDeck().
    switch (num1)
    {
    case 1:
        card1++;
        break;
    case 2:
        card2++;
        break;
    case 3:
        card3++;
        break;
    case 4:
        card4++;
        break;
    case 5:
        card5++;
        break;
    case 6:
        card6++;
        break;
    case 7:
        card7++;
        break;
    case 8:
        card8++;
        break;
    case 9:
        card9++;
        break;
    case 10:
        card10++;
        break;
    case 11:
        cardJ++;
        break;
    case 12:
        cardQ++;
        break;
    case 13:
        cardK++;
        break;
    case 14:
        cardA++;
        break;
    }
}