// Fill out your copyright notice in the Description page of Project Settings.


#include "../AIPawn.h"
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


	FHitResult result;
	FCollisionQueryParams param(NAME_None, false, AIPawn);

	bool Collision = GetWorld()->SweepSingleByChannel(
		result, 
		AIPawn->GetActorLocation(),
		AIPawn->GetActorLocation(), 
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel8,
		FCollisionShape::MakeSphere(800.f), param);

	
#if ENABLE_DRAW_DEBUG

	FColor DrawColor = Collision ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), AIPawn->GetActorLocation(), 800.f, 20, DrawColor, false, 0.35f);

#endif

}
