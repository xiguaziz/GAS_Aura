// Aura学习中。

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interface/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();

	//EnemyInterface
	virtual void HighlightActor() override; //高亮
	virtual void UnHighlightActor() override; //取消高亮
	//CombatInterface
	virtual int32 GetPlayerLevel() const override;
	// UPROPERTY(BlueprintReadOnly)
	// bool bHighlighted=false;
	
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Character Class Default")
	int32 Level=1;
};
