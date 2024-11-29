// Fill out your copyright notice in the Description page of Project Settings.


#include "Tencent_OCGameState.h"

#include "Tencent_OCPlayerController.h"
#include "Tencent_OCPlayerState.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"


void ATencent_OCGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATencent_OCGameState, MatchTimerInteger);
	DOREPLIFETIME(ATencent_OCGameState, bMatchStarted);
	DOREPLIFETIME(ATencent_OCGameState, CurState);
}

ATencent_OCGameState::ATencent_OCGameState()
{
	// 启用Tick
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	
}

void ATencent_OCGameState::OnTerminatedTarget(const int32 PlayerID, int32 ScoreToIncrease)
{
	for (TObjectPtr<APlayerState> PlayerState : PlayerArray)
	{
		if(PlayerState->GetPlayerId() == PlayerID)
		{
			Cast<ATencent_OCPlayerState>(PlayerState)->IncreaseScore(ScoreToIncrease);
		}
	}
}

void ATencent_OCGameState::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATencent_OCGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(HasAuthority())
	{
		if(bMatchStarted)
		{
			if(MatchTimer < 0 && MatchTimer + DeltaSeconds >= 0)
			{
				OnEnterPrepareState();
			}
			if(MatchTimer < PrepareTimeMax && MatchTimer + DeltaSeconds >= PrepareTimeMax)
			{
				OnEnterMatchState();
			}
			if(MatchTimer < PrepareTimeMax + MatchTimeMax && MatchTimer + DeltaSeconds >= PrepareTimeMax + MatchTimeMax)
			{
				OnEnterSettlementState();
			}
			MatchTimer += DeltaSeconds;
			if(FMath::FloorToInt32(MatchTimer) != MatchTimerInteger)
			{
				MatchTimerInteger = MatchTimer;
			}
		}
	}
}

void ATencent_OCGameState::StartTheMatch()
{
	bMatchStarted = true;
}

int32 ATencent_OCGameState::GetPrepareCountdown()
{
	if(!bMatchStarted) return PrepareTimeMax;

	if(MatchTimerInteger < PrepareTimeMax)
	{
		return PrepareTimeMax - MatchTimerInteger;
	}
	return -1;
}

int32 ATencent_OCGameState::GetMatchCountdown()
{
	if(!bMatchStarted) return MatchTimeMax;

	if(MatchTimerInteger < PrepareTimeMax + MatchTimeMax)
	{
		return PrepareTimeMax + MatchTimeMax - MatchTimerInteger;
	}
	return -1;
}

TArray<FSettlementListViewRowInfo> ATencent_OCGameState::GetSortedRwInfoArray()
{
	TArray<FSettlementListViewRowInfo> ListViewArray;
	for (TObjectPtr<APlayerState> PlayerState : PlayerArray)
	{
		ListViewArray.Add(FSettlementListViewRowInfo(0, PlayerState->GetPlayerId(), Cast<ATencent_OCPlayerState>(PlayerState)->GetCurrentScore()));
	}
	ListViewArray.StableSort([](FSettlementListViewRowInfo A, FSettlementListViewRowInfo B){return A.Score > B.Score;});
	int32 Rank = 1;
	int32 Num = ListViewArray.Num();
	for(int i = 0; i < Num; i++)
	{
		if(i > 0)
		{
			if(ListViewArray[i].Score != ListViewArray[i-1].Score)
			{
				Rank = i + 1;
			}
		}
		ListViewArray[i].Rank = Rank;
	}

	return ListViewArray;
}

void ATencent_OCGameState::OnEnterPrepareState()
{
	CurState = EState::Preparation;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Enter Prepare State");
	ShowUIForAllPlayer(TEXT("Preparation"));
}

void ATencent_OCGameState::OnEnterMatchState()
{
	CurState = EState::Match;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Enter Match State");
	HideUIForAllPlayer(TEXT("Preparation"));
	ShowUIForAllPlayer(TEXT("Match"));

	RandomlyGenerateTarget();
}

void ATencent_OCGameState::OnEnterSettlementState()
{
	CurState = EState::Settlement;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Enter Settlement State");
	HideUIForAllPlayer(TEXT("Match"));
	ShowUIForAllPlayer(TEXT("Settlement"));

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), .1f);
	DisableAllPlayerInputClient();
}

void ATencent_OCGameState::ShowUIForAllPlayer(const FString& UIName) const
{
	int32 PCNum = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	for(int32 PCIndex = 0; PCIndex < PCNum; ++PCIndex)
	{
		if(APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), PCIndex))
		{
			Cast<ATencent_OCPlayerController>(PlayerController)->ShowUIClient(UIName);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Null Player Controller");
		}
	}
}

void ATencent_OCGameState::HideUIForAllPlayer(const FString& UIName) const
{
	int32 PCNum = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	for(int32 PCIndex = 0; PCIndex < PCNum; ++PCIndex)
	{
		if(APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), PCIndex))
		{
			Cast<ATencent_OCPlayerController>(PlayerController)->HideUIClient(UIName);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Null Player Controller");
		}
	}
}

void ATencent_OCGameState::DisableAllPlayerInputClient() const
{
	int32 PCNum = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	for(int32 PCIndex = 0; PCIndex < PCNum; ++PCIndex)
	{
		if(APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), PCIndex))
		{
			Cast<ATencent_OCPlayerController>(PlayerController)->DisableInputClient();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Null Player Controller");
		}
	}
}

void ATencent_OCGameState::RandomlyGenerateTarget() const
{
	if(!HasAuthority()) return;
	AActor* RandomAreaActor = UGameplayStatics::GetActorOfClass(GetWorld(), RandomAreaActorClass);
	if(RandomAreaActor)
	{
		UActorComponent* BoxComponent = RandomAreaActor->GetComponentByClass(UBoxComponent::StaticClass());
		if(BoxComponent)
		{
			for (int32 i = 0; i < TargetNum; i++)
			{
				FVector BoxExtent = Cast<UBoxComponent>(BoxComponent)->GetScaledBoxExtent();
				FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(
					RandomAreaActor->GetActorLocation(), BoxExtent);
				AActor* Target = GetWorld()->SpawnActor(TargetActorClass, &RandomLocation);
			}
		}
	}
}




