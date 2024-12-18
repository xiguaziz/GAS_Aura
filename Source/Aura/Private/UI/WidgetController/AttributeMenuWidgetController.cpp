// Aura学习中。


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallBacksToDependencies()
{
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS=Cast<UAuraAttributeSet>(AttributeSet);

	checkf(AttributeInfo,TEXT("请设置BP_AttributeMenuWidgetController中的AttributeInfo！"));
	FAuraAttributeInfo Info=AttributeInfo->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Strength);
	
	Info.AttributeValue=AS->GetStrength();

	AttributeInfoDelegate.Broadcast(Info);
}
