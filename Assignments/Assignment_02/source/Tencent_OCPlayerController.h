// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tencent_OCPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class TENCENT_OC_API ATencent_OCPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface

	// UI
public:
	/** 
	 * @brief RPC函数，显示指定UI
	 * @author Atsukko
	 */
	UFUNCTION(Client, Reliable)
	void ShowUIClient(const FString& UIName);
	/** 
	 * @brief RPC函数，隐藏指定UI
	 * @author Atsukko
	 */
	UFUNCTION(Client, Reliable)
	void HideUIClient(const FString& UIName);
	/** 
	 * @brief RPC函数，禁用玩家输入
	 * @author Atsukko
	 */
	UFUNCTION(Client, Reliable)
	void DisableInputClient();

	/** 
	 * Widget类数组
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TArray<TSubclassOf<UUserWidget>> UIClasses;

	/** 
	 * Widget对象数组
	 */
	UPROPERTY()
	TArray<UUserWidget*> UIs;

	/** 
	 * Widget名称与索引映射表
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TMap<FString, int32> UIIndexMap = {
		{TEXT("Preparation"), 0},
		{TEXT("Match"), 1},
		{TEXT("Settlement"), 2},
	};

};
