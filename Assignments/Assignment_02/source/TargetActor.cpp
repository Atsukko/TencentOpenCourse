// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetActor.h"

#include "Kismet/KismetMathLibrary.h"
#include "Misc/MapErrors.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ATargetActor::ATargetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
}

void ATargetActor::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATargetActor, bHighValueTarget);
}

// Called when the game starts or when spawned
void ATargetActor::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		if(UKismetMathLibrary::InRange_FloatFloat(UKismetMathLibrary::RandomFloat(), 0, HighValueTargetRate))
		{
			bHighValueTarget = true;
		}
	}
	if(bHighValueTarget)
	{
		SetHighScoreTarget();
	}
}

// Called every frame
void ATargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATargetActor::Hit()
{
	CurHitCount++;
	if(CurHitCount >= MaxHitCount)
	{
		Destroy();
		return true;
	}
	SetActorScale3D(FVector::One() * (1 - static_cast<float>(CurHitCount) / MaxHitCount));
	return false;
}

void ATargetActor::SetHighScoreTarget()
{
	ScoreValue = HighScoreValue;
	UMaterialInstanceDynamic* MI = UMaterialInstanceDynamic::Create(ParentMaterial, this);
	MI->SetScalarParameterValue("bUseHighValueColor(0:1)", 1);
	MeshComponent->SetMaterial(0, MI);
}

