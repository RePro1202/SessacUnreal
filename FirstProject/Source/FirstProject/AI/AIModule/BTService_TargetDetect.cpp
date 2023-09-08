// Fill out your copyright notice in the Description page of Project Settings.


#include "../AIPawn.h"
#include "../AIStateComponent.h"
#include "../DefaultAIController.h"
#include "BTService_TargetDetect.h"



UBTService_TargetDetect::UBTService_TargetDetect()
{
	NodeName = TEXT("TargetDetect");
	Interval = 0.5f;
	RandomDeviation = 0.1f;

}

void UBTService_TargetDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// BehaviorTreeComponent를 이용하여 AIController를 얻어올 수 있다.
	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* AIPawn = Cast<AAIPawn>(Controller->GetPawn());

	if (!IsValid(AIPawn)) return;


	FVector	AILoc = AIPawn->GetActorLocation();
	AILoc.Z -= AIPawn->GetHalfHeight();

	FHitResult result;
	FCollisionQueryParams param(NAME_None, false, AIPawn);

	bool Collision = GetWorld()->SweepSingleByChannel(
		result, 
		AILoc,
		AILoc,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel8,
		FCollisionShape::MakeSphere(AIPawn->GetAIState()->GetInteractionDistance()),
		param);

	
#if ENABLE_DRAW_DEBUG

	FColor DrawColor = Collision ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), AIPawn->GetActorLocation(), 800.f, 20, DrawColor, false, 0.35f);

#endif

	// 충돌이 되었다면 Blackboard의 Target 변수에 충돌된 물체를 지정하고
	// 충돌이 아니면 nullptr을 지정한다.

	if (Collision)
	{
		// Controller로부터 Blackboard를 얻어와서 Target을 지정한다.
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), result.GetActor());
	}
	else 
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	}
}
