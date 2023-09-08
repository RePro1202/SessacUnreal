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

	// BehaviorTreeComponent�� �̿��Ͽ� AIController�� ���� �� �ִ�.
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

	// �浹�� �Ǿ��ٸ� Blackboard�� Target ������ �浹�� ��ü�� �����ϰ�
	// �浹�� �ƴϸ� nullptr�� �����Ѵ�.

	if (Collision)
	{
		// Controller�κ��� Blackboard�� ���ͼ� Target�� �����Ѵ�.
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), result.GetActor());
	}
	else 
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	}
}
