// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <map>
#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void GameIntro();
	void BuildDict();
	void InitializeNewGame();
	void AskRestartGame();
	void ListRemaining();
	bool bGameOverCheck();
	void GameOver();

	// Your declarations go below!
	private:

	FString HiddenWord;
	int32 Cows;
    int32 Bulls;
    int32 RemainingAttempts;
	bool bGameActive;
	std::map<int32, FString> Dict;


};
