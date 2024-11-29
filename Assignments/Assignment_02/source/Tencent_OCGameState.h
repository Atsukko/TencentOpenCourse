// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetActor.h"
#include "GameFramework/GameState.h"
#include "Tencent_OCGameState.generated.h"


USTRUCT(BlueprintType)
struct FSettlementListViewRowInfo
{
	GENERATED_BODY()
	
	FSettlementListViewRowInfo() = default;
	FSettlementListViewRowInfo(const int32 R, const int32 N, const int32 S) : Rank(R), ID(N), Score(S) {}

	UPROPERTY(BlueprintReadWrite)
	int32 Rank;
	UPROPERTY(BlueprintReadWrite)
	int32 ID;
	UPROPERTY(BlueprintReadWrite)
	int32 Score;
};

UENUM(BlueprintType)
enum class EState : uint8
{
	Preparation,
	Match,
	Settlement
};

/**
 * 
 */
UCLASS()
class TENCENT_OC_API ATencent_OCGameState : public AGameState
{
	GENERATED_BODY()

	
public:
	ATencent_OCGameState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


public:
	/** 
	 * @brief 调用以开始对局
	 * @author Atsukko
	 */
	UFUNCTION(BlueprintCallable)
	void StartTheMatch();

	/** 
	 * @brief 获取准备阶段的倒计时
	 * @author Atsukko
	 */
	UFUNCTION(BlueprintCallable)
	int32 GetPrepareCountdown();

	/** 
	 * @brief 获取对局阶段的倒计时
	 * @return 向下取整的倒计时秒数
	 * @author Atsukko
	 */
	UFUNCTION(BlueprintCallable)
	int32 GetMatchCountdown();

	/** 
	 * @brief 获取所有玩家比赛信息的数组
	 * @return 结构体数组，每个元素的结构体代表一个玩家的数据
	 * @author Atsukko
	 */
	UFUNCTION(BlueprintCallable)
	TArray<FSettlementListViewRowInfo> GetSortedRwInfoArray();
public:
	void OnTerminatedTarget(const int32 PlayerID, int32 ScoreToIncrease);

	/** 
	 * 目标Actor类
	 */
	UPROPERTY(EditAnywhere, Category="Gameplay")
	TSubclassOf<ATargetActor> TargetActorClass;
	/** 
	 * 目标生成区域类
	 */
	UPROPERTY(EditAnywhere, Category="Gameplay")
	TSubclassOf<AActor> RandomAreaActorClass;
	/** 
	 * 生成目标数
	 */
	UPROPERTY(EditAnywhere, Category="Gameplay")
	int32 TargetNum = 10;
	/** 
	 * 准备阶段时间
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Match State")
	float PrepareTimeMax = 5.f;
	/** 
	 * 对局阶段时间
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Match State")
	float MatchTimeMax = 10.f;


	/** 
	 * 游戏总计时器
	 */
	float MatchTimer = -0.01f;
	/** 
	 * 计时器向下取整
	 */
	UPROPERTY(Replicated)
	int32 MatchTimerInteger = 0;
	/** 
	 * 对局是否开始
	 */
	UPROPERTY(Replicated)
	bool bMatchStarted = false;
	/** 
	 * 当前阶段
	 */
	UPROPERTY(Replicated)
	EState CurState;



private:
	/** 
	 * @brief 进入准备阶段
	 * @author Atsukko
	 */
	void OnEnterPrepareState();
	/** 
	 * @brief 进入对局阶段
	 * @author Atsukko
	 */
	void OnEnterMatchState();
	/** 
	 * @brief 进入结算阶段
	 * @author Atsukko
	 */
	void OnEnterSettlementState();

	/** 
	 * @brief 使用RPC让所有玩家显示某个UI
	 * @author Atsukko
	 */
	void ShowUIForAllPlayer(const FString& UIName) const;
	/** 
	 * @brief 使用RPC让所有玩家隐藏某个UI
	 * @author Atsukko
	 */
	void HideUIForAllPlayer(const FString& UIName) const;
	/** 
	 * @brief 使用RPC禁用所有玩家输入
	 * @author Atsukko
	 */
	void DisableAllPlayerInputClient() const;
	/** 
	 * @brief 在指定区域随机生成指定数量目标
	 * @author Atsukko
	 */
	void RandomlyGenerateTarget() const;
};
