// Caveman Games copyright.

#include "ColorBalls.h"


// Sets default values
AColorBalls::AColorBalls()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AColorBalls::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AColorBalls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation.Z += Speed * DeltaTime;

	SetActorLocation(NewLocation);

	if (NewLocation.Z < -870.0f)
	{
		this->Destroy();
	}

}

