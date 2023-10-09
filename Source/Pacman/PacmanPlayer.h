// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PacmanPlayer.generated.h"

UCLASS()
class PACMAN_API APacmanPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacmanPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* PacmanDisplayMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Lifes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InvincibleTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NormalSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Injured();
	void Resetting();
	void SetMovement(bool bCanMove);

	void StartGame();
	void PauseGame();
	void RestartGame();

	void MoveX(float Value);
	void MoveY(float Value);

	UFUNCTION()
	void OnPacmanBeginOverlay(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	FVector StartLocation;
	FVector Velocity;
	class APacmanGameModeBase* GameModeRef;
	FTimerHandle ResettingTimerHandle;

};
