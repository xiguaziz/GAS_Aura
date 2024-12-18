// Aura学习中。

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * 曾在项目设置中修改默认的AssetManager
 * 为了初始化AuraGameplayTags::InitializeNativeGameplayTags()中的值
 */
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UAuraAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
