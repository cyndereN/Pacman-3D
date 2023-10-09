// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:

	void OnPossess(class APawn* PawnToPossess) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void GoToNewDestination();

private:
	
	class APacmanEnemy* ControlledEnemy;

};
