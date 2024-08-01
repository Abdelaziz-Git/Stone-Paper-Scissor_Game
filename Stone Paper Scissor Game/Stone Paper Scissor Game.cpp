#include <iostream>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 1;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner RoundWinner;
    string RoundWinnerName;
};

struct stGameResults
{
    short GameRound = 0;
    short PlayerWonTimes = 0;
    short ComputerWonTimes = 0;
    short DrawTimes = 0;
    enWinner FinalWinner;
    string FinalWinnerName;
};

short HowManyRound()
{
    short RoundNumber = 1;
    do
    {
        cout << "How many round 1 to 10 ?\n";
        cin >> RoundNumber;
    } while (RoundNumber < 1 || RoundNumber>10);
    return RoundNumber;
}

enGameChoice ReadPlayer1Choice()
{
    short PlayerChoice = 1;
    do
    {
        cout << "\nYour choice : [1] : Stone, [2] : Paper, [3] : Scissors ?";
        cin >> PlayerChoice;
    } while (PlayerChoice < 1 || PlayerChoice>3);
    return enGameChoice(PlayerChoice);
}

int RandomNumber(int From, int To)
{
    //Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

enGameChoice GetComputerChoice()
{
    return enGameChoice(RandomNumber(1, 3));
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
            return enWinner::Computer;
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
            return enWinner::Computer;
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
            return enWinner::Computer;
        break;
    }
    return enWinner::Player1;
}

string ChoiceName(enGameChoice GameChoice)
{
    string arrChoice[3] = { "Stone","Paper","scissors" };
    return arrChoice[GameChoice - 1];
}

string WinnerName(enWinner Winner)
{
    string arrWinner[3] = { "Player1","Computer","Draw" };
    return arrWinner[Winner - 1];
}

void SeetSecrenColor(enWinner Winner)
{
    switch (Winner)
    {
    case Player1:
        system("color 2F");
        break;
    case Computer:
        cout << "\a";
        system("color 4F");
        break;
    default:
        system("color 6F");
        break;
    }
}

void PrintRound(stRoundInfo RoundInfo)
{
    cout <<
        "\n_____________[" << RoundInfo.RoundNumber << "]______________\n";
    cout <<
        "\nPlayer1 choice :" << ChoiceName(RoundInfo.Player1Choice);
    cout <<
        "\nComputer choice:" << ChoiceName(RoundInfo.ComputerChoice);
    cout <<
        "\nRound Winner   :" << RoundInfo.RoundWinnerName;
    cout <<
        "\n______________________________\n";
    SeetSecrenColor(RoundInfo.RoundWinner);
}

enWinner WhoWonTheGame(short Player1WonTimes, short ComputerWonTimes)
{
    if (Player1WonTimes > ComputerWonTimes)
        return enWinner::Player1;
    else if (Player1WonTimes < ComputerWonTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

stGameResults FillGameResults(short GameRound, short Player1WonTimes, short ComputerWonTimes, short DrawTimes)
{
    stGameResults GameResults;
    GameResults.GameRound = GameRound;
    GameResults.PlayerWonTimes = Player1WonTimes;
    GameResults.ComputerWonTimes = ComputerWonTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.FinalWinner = WhoWonTheGame(GameResults.PlayerWonTimes, GameResults.ComputerWonTimes);
    GameResults.FinalWinnerName = WinnerName(GameResults.FinalWinner);
    return GameResults;
}

stGameResults PlayGame(short HowManyRound)
{
    stRoundInfo RoundInfo;
    short PlayerWonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0, GameRounds;

    for (GameRounds = 1; GameRounds <= HowManyRound; GameRounds++)
    {
        cout << "\nRound [" << RoundInfo.RoundNumber << "] begins:\n";
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
        RoundInfo.RoundWinnerName = WinnerName(RoundInfo.RoundWinner);

        if (RoundInfo.RoundWinner == enWinner::Player1)
            PlayerWonTimes++;
        else if (RoundInfo.RoundWinner == enWinner::Computer)
            ComputerWonTimes++;
        else
        {
            DrawTimes++;
        }
        PrintRound(RoundInfo);
    }

    return FillGameResults(HowManyRound, PlayerWonTimes, ComputerWonTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 0; i < NumberOfTabs; i++)
    {
        t = t + "\t";
    }
    return t;
}

void PrintGameOver()
{
    cout << endl << Tabs(2) <<
        "___________________________________\n\n";
    cout << Tabs(2) << "      +++G a m e  O v e r+++\n";
    cout << Tabs(2) <<
        "___________________________________\n\n";
}

void PrintGameResults(stGameResults GameResults)
{
    cout << Tabs(2) <<
        "_________[Game Results]________\n";
    cout << Tabs(2) << "Game rounds:" <<
        GameResults.GameRound << endl;
    cout << Tabs(2) << "Player1 Won Times:" <<
        GameResults.PlayerWonTimes << endl;
    cout << Tabs(2) << "Computer won times:" <<
        GameResults.ComputerWonTimes << endl;
    cout << Tabs(2) << "Draw times:" <<
        GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final winner:" <<
        GameResults.FinalWinnerName << endl;
    cout << Tabs(2) <<
        "________________________________\n";

}

void ResetSecren()
{
    system("cls");
    system("color 0F");
}

void StarGame()
{
    char PlayAgain = 'y';
    do
    {
        ResetSecren();
        stGameResults GameResults = PlayGame(HowManyRound());
        PrintGameOver();
        PrintGameResults(GameResults);
        cout << Tabs(2) << "Do you want to play again? Y/n??";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main()
{
    srand((unsigned)time(NULL));
    StarGame();
    return 0;
}