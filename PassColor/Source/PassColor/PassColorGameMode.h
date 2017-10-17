// Caveman Games copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PassColorGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PASSCOLOR_API APassColorGameMode : public AGameMode
{
	GENERATED_BODY()


	float MINIMUM_INTERVAL = 0.5f;
	float MAXIMUM_INTERVAL = 2.0f;
	float TIME_TO_MINIMUM_INTERVAL = 30.0f;

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AColorBalls> ColorBallsBlueprint;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AEnemy> EnemyBlueprint;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AResistenceWall> ResistenceWallBlueprint;
	
	float ColorTimer;
	float GameTimer;

	UFUNCTION(BlueprintCallable, Category = "GamePoints")
		void IncrementScore(int Value);

	UFUNCTION(BlueprintCallable, Category = "UMGGame")
		void AddGameHUD();

	UFUNCTION(BlueprintCallable, Category = "UMGGame")
		void AddMenuHUD();

	void OnGameOver();

	UFUNCTION(BlueprintCallable, Category = "UMGGame")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UPROPERTY(EditAnywhere, Category = "WallSpawn")
		bool bIsWallSpawned = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WallSpawn")
		float TimeToSpawnWall = 60;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WallSpawn")
		float TimeResistenceWall;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GamePoints")
		int Score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSetup")
		bool bIsMenuOpen = true;

	bool bSpawnColor = true;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMGGame")
		TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMGGame")
		TSubclassOf<UUserWidget> GameWidgetClass;

	UPROPERTY()
		UUserWidget* CurrentWidget;
	
};
