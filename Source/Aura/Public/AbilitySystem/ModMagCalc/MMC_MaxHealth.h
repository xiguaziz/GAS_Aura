// Aura学习中。

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_MaxHealth();
	
	//这个函数返回了一个应用此MMC的GE的实例，我们可以通过Spec去获取需要的内容，然后计算数值。
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
private:

	FGameplayEffectAttributeCaptureDefinition VigorDef;
	
};
