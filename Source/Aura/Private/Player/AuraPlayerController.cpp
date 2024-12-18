// Aura学习中。


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interface/EnemyInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates=true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();

	
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit); //获取可视的鼠标命中结果
	if(!CursorHit.bBlockingHit) return; //如果未命中直接返回

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/**
	 * 射线拾取后，会出现的几种情况
	 * 1. LastActor is null   ThisActor is null 不需要任何操作
	 * 2. LastActor is null   ThisActor is valid 高亮ThisActor
	 * 3. LastActor is valid   ThisActor is null 取消高亮LastActor
	 * 4. LastActor is valid   ThisActor is valid LastActor ！= ThisActor 取消高亮LastActor 高亮ThisActor
	 * 5. LastActor is valid   ThisActor is valid LastActor == ThisActor 不需要任何操作
	 */

	if(LastActor == nullptr)
	{
		if(ThisActor != nullptr)
		{
			//case 2
			ThisActor->HighlightActor();
		} // else case 1
	}
	else
	{
		if(ThisActor == nullptr)
		{
			//case 3
			LastActor->UnHighlightActor();
		}
		else
		{
			if(LastActor != ThisActor)
			{
				//case 4
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			} //else case 5
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	//check(Subsystem);
	if(Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext,0);
	}


	bShowMouseCursor=true;
	DefaultMouseCursor=EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);

	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector=InputActionValue.Get<FVector2d>();
	const FRotator Rotation=GetControlRotation();
	const FRotator YawRotation(0.0f,Rotation.Yaw,0.0f);
	
	const FVector ForwardDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn=GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
} 

