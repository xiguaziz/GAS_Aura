// Aura学习中。


#include "Character/AuraCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; //设置为true，角色将朝移动的方向旋转
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f); //旋转速率
	GetCharacterMovement()->bConstrainToPlane = true; //约束到平面
	GetCharacterMovement()->bSnapToPlaneAtStart = true; //设置了上面一项为true，且此项设置为true，则在开始时与地面对其

	//设置使用控制器选择Pitch，Yaw，Roll的值。
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

}

int32 AAuraCharacter::GetPlayerLevel() const
{
	AAuraPlayerState* AuraPlayerState=GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState)
	return AuraPlayerState->GetPlayerLevel();
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//Init Ability Actor Info for Server
	InitAbilityActorInfo();
	SetOwner(NewController);
	
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//Init Ability Actor Info for Client
	InitAbilityActorInfo();
	
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState=GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);
	//回调UAuraAbilitySystemComponent中的AbilityActorInfoSet函数。
	CastChecked<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();

	AbilitySystemComponent=AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet=AuraPlayerState->GetAttributeSet();

	if(AAuraPlayerController* AuraPlayerController=Cast<AAuraPlayerController>(GetController()))
	{
		if(AAuraHUD* AuraHUD=Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}