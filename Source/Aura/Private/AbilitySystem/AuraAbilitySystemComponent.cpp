// Aura学习中。


#include "AbilitySystem/AuraAbilitySystemComponent.h"

//在角色类的void InitAbilityActorInfo()进行绑定;
void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	/** Called on server whenever a GE is applied to self. This includes instant and duration based GEs. */
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//GEngine->AddOnScreenDebugMessage(1,5.f,FColor::Blue,FString("Effect Applied!"));
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	// for(const FGameplayTag& Tag : TagContainer)
	// {
	// 	//TODO: 将tag广播给Widget Controller
	// 	const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString()); //获取Asset Tag
	// 	GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Cyan, Msg); //打印到屏幕上 -1 不会被覆盖
	// }

	EffectAssetTags.Broadcast(TagContainer);
}
