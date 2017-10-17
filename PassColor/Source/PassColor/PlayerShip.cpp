// Caveman Games copyright.

#include "PlayerShip.h"
#include "Kismet/GameplayStatics.h"
#include "ColorBalls.h"
#include "PassColorGameMode.h"
#include "PaperSpriteComponent.h"
#include "Engine.h"

#define OUT

APlayerShip::APlayerShip()
{
	PrimaryActorTick.bCanEverTick = true;
	//RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
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

void APlayerShip::OnRestart()
{
	/*if (Died)
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}//*/
}

void APlayerShip::ReceiveActorBeginOverlap(AActor * OtherActor)
{
	//Super::ReceiveActorBeginOverlap(OtherActor);
	if (OtherActor->IsA(AColorBalls::StaticClass()))
	{
		AColorBalls* Ball = (AColorBalls*)OtherActor;
		
		GetColorOfBall(Ball->SetedSpriteName);

		RedColor = FMath::Clamp<float>(RedColor, 0.0f, 1.0f);

		GreenColor = FMath::Clamp<float>(GreenColor, 0.0f, 1.0f);

		BlueColor = FMath::Clamp<float>(BlueColor, 0.0f, 1.0f);
		
		OtherActor->Destroy();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("RedColor:%f - GreenColor:%f - BlueColor:%f"), RedColor, GreenColor, BlueColor));
		}
		//UE_LOG(LogTemp, Warning, TEXT("Colided to: %s!!!!!!!"), *ColorName);
	}
}

void APlayerShip::GetColorOfBall(FString ColorName)
{
	FString Color = ColorName;

	if (Color == ("B_color_Sprite"))
	{
		BlueColor += 0.1f;
	}
	else if (Color == ("G_color_Sprite"))
	{
		GreenColor += 0.1f;
	}
	else if (Color == ("R_color_Sprite"))
	{
		RedColor += 0.1f;
	}
	else if (Color == ("GB_color_Sprite"))
	{
		GreenColor += 0.1f;
		BlueColor += 0.1f;
	}
	else if (Color == ("RB_color_Sprite"))
	{
		RedColor += 0.1f;
		BlueColor += 0.1f;
	}
	else if (Color == ("RG_color_Sprite"))
	{
		RedColor += 0.1f;
		GreenColor += 0.1f;
	}
	else if (Color == ("RGB_colors_Sprite"))
	{
		RedColor += 0.1f;
		GreenColor += 0.1f;
		BlueColor += 0.1f;
	}
	else if (Color == ("RGB_discolors_Sprite"))
	{
		RedColor -= 0.1f;
		GreenColor -= 0.1f;
		BlueColor -= 0.1f;
	}
}
