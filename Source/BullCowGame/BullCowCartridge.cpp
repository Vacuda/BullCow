// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
// #include <iostream>
// #include <cstdlib>
// #include <ctime>
// #include <string>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // build WordList
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);

    GameIntro();
    InitializeNewGame();



}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    // UE_LOG(MyGame, Log, TEXT("Is Isogram: %s"), bIsIsogram? "true" : "false" );

    //reset to new game
    if(bGameActive == false)
    {
        bGameActive = true;
        PrintLine(TEXT("- New Game -"));
        InitializeNewGame();
        return;
    }

    //is Isogram?
    if(!bIsIsogram(Input)){
        PrintLine(TEXT("- NOT AN ISOGRAM -"));
        PrintLine(TEXT("- Try again -"));
        InfoList();
        return;
    }

    //right length?
    if(Input.Len() != HiddenWord.Len()){
        PrintLine(TEXT("- Wrong Length -"));
        PrintLine(TEXT("- Try again -"));
        InfoList();
        return;
    }

    CalculateBullsCows(Input);

    //win
    if(Input == HiddenWord){
        PrintLine(TEXT("You Win"));
        InfoList();
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

        PrintLine(TEXT("Drat! Wrong Guess."));
        InfoList();
        ResetBullsCows();
        PrintLine(TEXT("Enter Another Guess..."));
    }

}

void const UBullCowCartridge::GameIntro()
{
    PrintLine(TEXT("Hello, and Welcome!"));
    PrintLine(TEXT("Guess the Isogram!"));
    PrintLine(TEXT("---"));
}

void UBullCowCartridge::InitializeNewGame()
{
    HiddenWord = Words[rand() % Words.Num()];
    Cows = 0;
    Bulls = 0;
    RemainingAttempts = HiddenWord.Len();
    bGameActive = true;
    PrintLine(TEXT("The Hidden Word is %s"), *HiddenWord);
    InfoList();
    PrintLine(TEXT("Enter Your Guess..."));
}

void const UBullCowCartridge::AskRestartGame()
{
    PrintLine(TEXT("---"));
    PrintLine(TEXT("Press Enter To Start Another"));
}

void const UBullCowCartridge::InfoList()
{
    PrintLine(TEXT("Remaining Attempts: ") + FString::FromInt(RemainingAttempts));
    PrintLine(TEXT("Hidden Word length: %i"), HiddenWord.Len());
    PrintLine(TEXT("Bulls: ") + FString::FromInt(Bulls));
    PrintLine(TEXT("Cows: ") + FString::FromInt(Cows));

}

bool const UBullCowCartridge::bGameOverCheck()
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
    InfoList();
    PrintLine(TEXT("You have lost the game."));
    bGameActive = false;
    AskRestartGame();
}

void UBullCowCartridge::CalculateBullsCows(const FString& Input)
{
    //SAFETY - null input
    if(Input.Len()==0){
        return;
    }

    //SAFETY - unequal lengths
    if(Input.Len()!=HiddenWord.Len()){
        return;
    }

    for(int32 i=0; i<Input.Len(); i++){

        //Bulls == right letter, RIGHT spot
        if(Input[i]==HiddenWord[i]){
            Bulls++;
            continue;
        }

        //Cows == right letter, WRONG spot
        for(int32 j=0; j<HiddenWord.Len(); j++){
            if(Input[i]==HiddenWord[j]){
                Cows++;
                break;
            }
        }

        
    }

}

bool const UBullCowCartridge::bIsIsogram(const FString& Input)
{

    for(int32 i=0; i<Input.Len(); i++){
        for(int32 j=i+1; j<Input.Len(); j++){
            if(Input[i]==Input[j]){
                return false;
            }
        }
    }

    return true;
}

void UBullCowCartridge::ResetBullsCows()
{
    Bulls = 0;
    Cows = 0;
}




