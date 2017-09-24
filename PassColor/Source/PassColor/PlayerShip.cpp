// Caveman Games copyright.

#include "PlayerShip.h"
#include "Kismet/GameplayStatics.h"

#define OUT

APlayerShip::APlayerShip()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerShip::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!CurrentVelocity.IsZero())
	{
		if (!bTouch)
		{
			FVector NewLocation = GetActorLocation() + Speed * CurrentVelocity * DeltaSeconds;
			SetActorLocation(NewLocation);
		}
		else
		{
			if (CurrentVelocity.Z > -3)
			{
				CurrentVelocity.Z = -3;
			}
			if (CurrentVelocity.X < -458)
			{
				CurrentVelocity.X = -458;
			}
			else if (CurrentVelocity.X > 452)
			{
				CurrentVelocity.X = 452;
			}
			SetActorLocation(CurrentVelocity);
		}
		//UE_LOG(LogTemp, Warning, TEXT("Position X: %f Z: %f"), CurrentVelocity.X, CurrentVelocity.Z);
	}
	
}

void APlayerShip::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &APlayerShip::Move_Forward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerShip::Move_Right);
	PlayerInputComponent->BindTouch(IE_Repeat, this, &APlayerShip::TouchMoved);
	PlayerInputComponent->BindTouch(IE_Released, this, &APlayerShip::TouchEnd);
}

void APlayerShip::Move_Forward(float AxisValue)
{
	if (!bTouch)
	{
		float ClampedValue = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
		CurrentVelocity.Z = ClampedValue * 100.0f;
	}
}

void APlayerShip::Move_Right(float AxisValue)
{
	if (!bTouch)
	{
		float ClampedValue = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
		CurrentVelocity.X = ClampedValue * 100.0f;
	}
}

void APlayerShip::TouchMoved(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == 0)
	{
		bTouch = true;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectScreenPositionToWorld(Location.X, Location.Y, OUT CurrentVelocity, OUT CurrentDirection);
	}
}

void APlayerShip::TouchEnd(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == 0)
	{
		CurrentVelocity = FVector::ZeroVector;
		bTouch = false;
	}
}
