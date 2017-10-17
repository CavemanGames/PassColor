// Caveman Games copyright.

#pragma once

#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PASSCOLOR_API UGameMenu : public UUserWidget
{
	GENERATED_BODY()
	
	void Load();

	void SetScore(int score);
	void OnGameOver(int score);

	UTextBlock* ScoreText;
};
