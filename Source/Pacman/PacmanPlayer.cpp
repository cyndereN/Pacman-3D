// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Pacdot.h"
#include "Kismet/GameplayStatics.h"
#include "PacmanGameModeBase.h"
#include "Engine/Public/TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APacmanPlayer::APacmanPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Lifes = 3;
	InvincibleTime = 3.0f;
	NormalSpeed = 600.0f;
	Velocity = FVector(0, 0, 0);

	PacmanDisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PacmanDisplayMesh"));
	PacmanDisplayMesh->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned
void APacmanPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	GameModeRef = Cast<APacmanGameModeBase>(UGameplayStatics::GetGameMode(this));

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacmanPlayer::OnPacmanBeginOverlay);
	SetMovement(true);
}

// Called every frame
void APacmanPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APacmanPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("StartGame", IE_Pressed, this, &APacmanPlayer::StartGame);
	PlayerInputComponent->BindAction("PauseGame", IE_Pressed, this, &APacmanPlayer::PauseGame);
	PlayerInputComponent->BindAction("RestartGame", IE_Pressed, this, &APacmanPlayer::RestartGame);

	PlayerInputComponent->BindAxis("MoveX", this, &APacmanPlayer::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &APacmanPlayer::MoveY);
}

void APacmanPlayer::Injured()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Invincible"));

	Lifes--;
	if (Lifes == 0)
	{
		GameModeRef->SetCurrentState(EGameState::EGameOver);
	}
	else
	{
		SetActorLocation(StartLocation);
		GetWorldTimerManager().SetTimer(ResettingTimerHandle, this, &APacmanPlayer::Resetting, InvincibleTime, false);
	}
	
}

void APacmanPlayer::Resetting()
{
	GetWorldTimerManager().ClearTimer(ResettingTimerHandle);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
}

void APacmanPlayer::SetMovement(bool bCanMove)
{
	if (bCanMove)
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 0;
	}
}

void APacmanPlayer::StartGame()
{
	GameModeRef->StartGame();
}

void APacmanPlayer::PauseGame()
{
	GameModeRef->PauseGame();
}

void APacmanPlayer::RestartGame()
{
	GameModeRef->RestartGame();
}

void APacmanPlayer::MoveX(float Value)
{
	if (GameModeRef->GetCurrentState() == EGameState::EPlay)
	{
		Velocity.X = Value;
		Velocity.Y = 0;

		if (Value > 0)
		{
			SetActorRotation(FRotator(0, 0, 0));
		}
		else if (Value < 0)
		{
			SetActorRotation(FRotator(0, -180, 0));
		}

		AddMovementInput(Velocity);
	}
}

void APacmanPlayer::MoveY(float Value)
{
	if (GameModeRef->GetCurrentState() == EGameState::EPlay)
	{
		Velocity.X = 0;
		Velocity.Y = Value;

		if (Value > 0)
		{
			SetActorRotation(FRotator(0, 90, 0));
		}
		else if (Value < 0)
		{
			SetActorRotation(FRotator(0, -90, 0));
		}

		AddMovementInput(Velocity);
	}
}

void APacmanPlayer::OnPacmanBeginOverlay(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GameModeRef->GetCurrentState() == EGameState::EPlay)
	{
		if (OtherActor->IsA(APacdot::StaticClass()))
		{
			APacdot* CurrentPacdot = Cast<APacdot>(OtherActor);
			if (CurrentPacdot->bIsSuperPacdot)
			{
				GameModeRef->SetEnemiesVulnerable();
			}
			OtherActor->Destroy();
			GameModeRef->SetPacdotNum(GameModeRef->GetPacdotNum() - 1);
		}
	}
}

