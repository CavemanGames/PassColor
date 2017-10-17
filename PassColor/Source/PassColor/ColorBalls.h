// Caveman Games copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColorBalls.generated.h"

UCLASS()
class PASSCOLOR_API AColorBalls : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColorBalls();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		class UShapeComponent* RootBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPaperSpriteComponent* SpriteColor;

	UPROPERTY(EditAnywhere)
		float Speed = -200.0f;

	UPROPERTY(BlueprintReadWrite)
		FString SetedSpriteName = "";
};
