// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "PacmanEnemy.h"
#include "NavigationSystem.h"

void AEnemyController::OnPossess(APawn* PawnToPossess)
{
	Super::OnPossess(PawnToPossess);

	ControlledEnemy = Cast<APacmanEnemy>(PawnToPossess);
}

void AEnemyController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	GoToNewDestination();
}

void AEnemyController::GoToNewDestination()
{
	UNavigationSystemV1* NavMesh = UNavigationSystemV1::GetCurrent(this);
	if (NavMesh)
	{
		const float SearchRadius = 10000.0f;
		FNavLocation RandomLocation;
		const bool bNewDestinationFound = NavMesh->GetRandomReachablePointInRadius(ControlledEnemy->GetActorLocation(), SearchRadius, RandomLocation);
		if (bNewDestinationFound)
		{
			MoveToLocation(RandomLocation.Location, 50.0f);
		}
	}
}
