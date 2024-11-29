// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetActor.generated.h"

UCLASS()
class TENCENT_OC_API ATargetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATargetActor();

	void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:

	
public:
	/** 
	 * 消灭目标所需击中次数
	 */
	UPROPERTY(EditAnywhere, Category="Gameplay")
	int32 MaxHitCount = 2;
	
	 /** 
	 * 消灭目标可以获得的分数
	 */
	UPROPERTY(EditAnywhere, Category="Gameplay")
	int32 ScoreValue = 1;

	/** 
	 * 高价值目标分值
	 */
	UPROPERTY(EditAnywhere, Category="Gameplay")
	int32 HighScoreValue = 2;

	/** 
	 * 出现高价值目标的概率
	 */
	UPROPERTY(EditAnywhere, Category="Gameplay")
	float HighValueTargetRate = .2f;

	/** 
	 * 网格体组件
	 */
	UPROPERTY(EditAnywhere, Category="Actor")
	UStaticMeshComponent* MeshComponent;

	/** 
	 * 材质实例的父项材质
	 */
	UPROPERTY(EditAnywhere, Category="Actor")
	UMaterialInterface* ParentMaterial;

public:
	/** 
	 * @brief 将当前目标转变为高价值目标
	 * @author Atsukko
	 */
	void SetHighScoreTarget();
	/** 
	 * @brief 目标被击中后被调用
	 * @return 当此击中是否消灭该目标，如果消灭，返回true
	 * @author Atsukko
	 */
	bool Hit();
private:
	/** 
	 * 当前累计被击中的次数
	 */
	int32 CurHitCount = 0;
	/** 
	 * 该目标是否高价值目标
	 */
	UPROPERTY(Replicated)
	bool bHighValueTarget = false;

};