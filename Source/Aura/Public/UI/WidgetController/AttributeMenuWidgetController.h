// Aura学习中。

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FAuraAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttibuteInfoSignature, const FAuraAttributeInfo&, Info);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:

	virtual void BindCallBacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")//设置BlueprintAssignable可以在蓝图作为委托绑定监听
	FAttibuteInfoSignature AttributeInfoDelegate;

protected:

	UPROPERTY(EditDefaultsOnly)//EditDefaultsOnly只能在UE面板编辑
	TObjectPtr<UAttributeInfo> AttributeInfo;
};
