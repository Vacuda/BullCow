// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <iostream>
#include <cstdlib>
#include <map>
#include <ctime>
#include <string>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    BuildDict();

    GameIntro();
    InitializeNewGame();



}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    //reset to new game
    if(bGameActive == false)
    {
        bGameActive = true;
        PrintLine(TEXT("- New Game -"));
        InitializeNewGame();
        return;
    }

    //win
    if(Input == HiddenWord){
        PrintLine(TEXT("You Win"));
        bGameActive = false;
        AskRestartGame();
    }

    //lose
    else{
    
        RemainingAttempts--;

        if(bGameOverCheck()){
            GameOver();
            return;
        }

        PrintLine(TEXT("Drat! You Lose"));
        ListRemaining();
        PrintLine(TEXT("Enter Another Guess..."));
    }

}

void UBullCowCartridge::GameIntro()
{
    PrintLine(TEXT("Hello, and Welcome!"));
    PrintLine(TEXT("Guess the Isogram!"));
    PrintLine(TEXT("---"));
}

void UBullCowCartridge::BuildDict()
{
    Dict[0] = TEXT("watermelon");
    Dict[1] = TEXT("raspberry");
    Dict[2] = TEXT("grape");
    Dict[3] = TEXT("banana");
    Dict[4] = TEXT("pineapple");
    Dict[5] = TEXT("orange");
    Dict[6] = TEXT("cherry");
    Dict[7] = TEXT("pear");
    Dict[8] = TEXT("strawberry");
    Dict[9] = TEXT("blueberry");
}

void UBullCowCartridge::InitializeNewGame()
{
    HiddenWord = Dict[rand() % 10];
    Cows = 0;
    Bulls = 0;
    RemainingAttempts = HiddenWord.Len();
    bGameActive = true;
    // PrintLine(TEXT("The Hidden Word is %s"), *HiddenWord);
    PrintLine(TEXT("The Hidden Word is %i characters long"), HiddenWord.Len());
    ListRemaining();
    PrintLine(TEXT("Enter Your Guess..."));
}

void UBullCowCartridge::AskRestartGame()
{
    PrintLine(TEXT("---"));
    PrintLine(TEXT("Press Enter To Start Another"));
}

void UBullCowCartridge::ListRemaining()
{
    PrintLine(TEXT("Remaining Attempts: ") + FString::FromInt(RemainingAttempts));
}

bool UBullCowCartridge::bGameOverCheck()
{
    if(RemainingAttempts <= 0){
        return true;
    }
    else{
        return false;
    }
}

void UBullCowCartridge::GameOver()
{
    PrintLine(TEXT("Wrong!!!!"));
    ListRemaining();
    PrintLine(TEXT("You have lost the game."));
    bGameActive = false;
    AskRestartGame();
}






