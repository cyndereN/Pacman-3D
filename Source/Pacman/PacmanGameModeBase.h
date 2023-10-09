// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PacmanGameModeBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGameState : uint8
{
	EMenu,
	EPlay,
	EPause,
	EWin,
	EGameOver
};

UCLASS()
class PACMAN_API APacmanGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	APacmanGameModeBase();

protected:

	virtual void BeginPlay() override;

public:

	void StartGame();
	void PauseGame();
	void RestartGame();

	void SetEnemiesVulnerable();
	void RecordEnemiesTimer();
	void RestoreEnemiesTimer();

	int GetPacdotNum() const;
	void SetPacdotNum(int Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int PacdotNum;

	EGameState GetCurrentState() const;
	void SetCurrentState(EGameState Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EGameState CurrentState;

private:

	TArray<class APacmanEnemy*> Enemies;
	TArray<float> EnemiesTimerRemaining;

};

FORCEINLINE int APacmanGameModeBase::GetPacdotNum() const
{
	return PacdotNum;
}

FORCEINLINE EGameState APacmanGameModeBase::GetCurrentState() const
{
	return CurrentState;
}
