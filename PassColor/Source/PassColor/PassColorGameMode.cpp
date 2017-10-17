// Caveman Games copyright.

#include "PassColorGameMode.h"
#include "EngineUtils.h"
#include "ColorBalls.h"
#include "MainMenu.h"
#include "GameMenu.h"
#include "ResistenceWall.h"

void APassColorGameMode::BeginPlay()
{
	Super::BeginPlay();

	TimeResistenceWall = TimeToSpawnWall;

	AddMenuHUD();
}

void APassColorGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bIsMenuOpen)
	{
		GameTimer += DeltaSeconds;
		ColorTimer -= DeltaSeconds;

		//UE_LOG(LogTemp, Warning, TEXT("ColorTimer: %f"), ColorTimer);


		if (!bIsWallSpawned)
		{
			UWorld* World = GetWorld();

			if (World)
			{
				FVector Location = FVector(0.0f, 0.0f, 1000.0f);

				World->SpawnActor<AResistenceWall>(ResistenceWallBlueprint, Location, FRotator::ZeroRotator);
				bIsWallSpawned = true;
			}
		}
		if (TimeResistenceWall <= 0.f)
		{
			for (TActorIterator<AResistenceWall> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
				AResistenceWall *Wall = *ActorItr;
				if (Wall->Speed == 0.f)
				{
					Wall->Speed = -400.0f;
					bSpawnColor = false;
				}
			}
		}

		if (bSpawnColor)
		{
			if (ColorTimer <= 0.0f)
			{
				float difficultyPercentage = FMath::Min(GameTimer / TIME_TO_MINIMUM_INTERVAL, 1.0f);

				ColorTimer = MAXIMUM_INTERVAL - (MAXIMUM_INTERVAL - MINIMUM_INTERVAL) * difficultyPercentage;

				UWorld* World = GetWorld();

				if (World)
				{
					FVector Location = FVector(FMath::RandRange(-470.f, 470.0f), 10.0f, 1000.0f);

					World->SpawnActor<AColorBalls>(ColorBallsBlueprint, Location, FRotator::ZeroRotator);
				}
			}
			TimeResistenceWall -= DeltaSeconds;
		}
		//UE_LOG(LogTemp, Warning, TEXT("%f"), TimeResistenceWall);
		//IncrementScore();
	}
}

void APassColorGameMode::IncrementScore(int Value)
{
	Score = Value;
}

void APassColorGameMode::AddGameHUD()
{
	ChangeMenuWidget(GameWidgetClass);
	bIsMenuOpen = false;
}

void APassColorGameMode::AddMenuHUD()
{
	ChangeMenuWidget(MainMenuWidgetClass);
	bIsMenuOpen = true;
}

void APassColorGameMode::OnGameOver()
{
}

void APassColorGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
