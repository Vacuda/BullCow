// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

// struct FBullsCowsCount 
// {
// 	int32 Bulls = 0;
// 	int32 Cows = 0;
// };

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	//const
	void const GameIntro();
	void const AskRestartGame();
	void const InfoList();
	bool const bGameOverCheck();
	bool const bIsIsogram(const FString& Input);

	void InitializeNewGame();
	void GameOver();
	void CalculateBullsCows(const FString& Input);
	void ResetBullsCows();
	TArray<FString> FilterWordList(const TArray<FString>& FullWordList);

	// Your declarations go below!
	private:

	FString HiddenWord;
	int32 Cows;
    int32 Bulls;
    int32 RemainingAttempts;
	bool bGameActive;
	TArray<FString> ValidWordList;


};
