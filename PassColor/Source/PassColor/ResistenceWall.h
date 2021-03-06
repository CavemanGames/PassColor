// Caveman Games copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResistenceWall.generated.h"

UCLASS()
class PASSCOLOR_API AResistenceWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResistenceWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		class UShapeComponent* RootBox;
	
	UPROPERTY(EditAnywhere)
		float Speed = 10.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Colors")
		float RedColor;

	UPROPERTY(BlueprintReadWrite, Category = "Colors")
		float GreenColor;

	UPROPERTY(BlueprintReadWrite, Category = "Colors")
		float BlueColor;
};
