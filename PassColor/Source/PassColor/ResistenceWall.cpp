// Caveman Games copyright.

#include "ResistenceWall.h"
#include "Components/BoxComponent.h"
#include "PassColorGameMode.h"

#define OUT

// Sets default values
AResistenceWall::AResistenceWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
}

// Called when the game starts or when spawned
void AResistenceWall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AResistenceWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation.Z = Speed * DeltaTime;

	SetActorLocation(NewLocation);

	if (NewLocation.Z < -870.0f)
	{
		this->Destroy();
		((APassColorGameMode*)GetWorld()->GetAuthGameMode())->bIsWallSpawned = false;
		((APassColorGameMode*)GetWorld()->GetAuthGameMode())->TimeResistenceWall = ((APassColorGameMode*)GetWorld()->GetAuthGameMode())->TimeToSpawnWall;
		
		//Set Dificulty Level
		((APassColorGameMode*)GetWorld()->GetAuthGameMode())->GameTimer = 0.f;

		((APassColorGameMode*)GetWorld()->GetAuthGameMode())->bSpawnColor = true;
	}
}

