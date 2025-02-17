// Copyright Epic Games, Inc. All Rights Reserved.


#include "Tencent_OCPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "SettlementListViewWidget.h"
#include "Tencent_OCGameState.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ATencent_OCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}

	// 初始化UI
	if(!HasAuthority())
	{
		for (auto UIClass : UIClasses)
		{
			UUserWidget* UI = CreateWidget(GetWorld(), UIClass);
			UIs.Add(UI);
		}
	}
}



void ATencent_OCPlayerController::ShowUIClient_Implementation(const FString& UIName)
{
	UUserWidget* UIToShow = UIs[UIIndexMap[UIName]];
	UIToShow->AddToViewport();
}

void ATencent_OCPlayerController::HideUIClient_Implementation(const FString& UIName)
{
	UIs[UIIndexMap[UIName]]->RemoveFromViewport();
}

void ATencent_OCPlayerController::DisableInputClient_Implementation()
{
	GetPawn()->DisableInput(this);
}

