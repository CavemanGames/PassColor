// Caveman Games copyright.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PlayerShip.generated.h"

/**
 * 
 */
UCLASS()
class PASSCOLOR_API APlayerShip : public APaperCharacter
{
	GENERATED_BODY()

	APlayerShip();

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Move_Forward(float AxisValue);
	void Move_Right(float AxisValue);
	void TouchMoved(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchEnd(ETouchIndex::Type FingerIndex, FVector Location);
	void OnRestart();

	FVector CurrentVelocity;
	FVector CurrentDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float Speed = 10.0f;

	bool bTouch = false;

	bool Died = true;

	UPROPERTY(EditAnywhere)
		class UShapeComponent* RootBox;
	
	UFUNCTION()
		void ReceiveActorBeginOverlap(AActor* OtherActor);

	UPROPERTY(BlueprintReadWrite, Category = "PlayerColor")
		float RedColor = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = "PlayerColor")
		float BlueColor = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = "PlayerColor")
		float GreenColor = 0.0f;

	void GetColorOfBall(FString ColorName);
};
