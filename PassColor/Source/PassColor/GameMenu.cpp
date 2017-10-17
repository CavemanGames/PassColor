// Caveman Games copyright.

#include "GameMenu.h"

void UGameMenu::Load()
{
	const FName TextBlockName = FName(TEXT("TxtScore"));

	if (ScoreText == nullptr)
	{
		ScoreText = (UTextBlock*)(WidgetTree->FindWidget(TextBlockName));
	}
}

void UGameMenu::SetScore(int score)
{
	if (ScoreText != nullptr)
	{
		ScoreText->SetText(FText::FromString(FString(TEXT("Score: ")) + FString::FromInt(score)));
	}
}

void UGameMenu::OnGameOver(int score)
{
	// TODO SaveGame and Show The main Menu
	// Create a Widget To show Ads
	if (ScoreText != nullptr)
	{
		ScoreText->SetText(FText::FromString(FString(TEXT("Score: ")) + FString::FromInt(score) + TEXT("\nPress R to restart")));
	}
}
