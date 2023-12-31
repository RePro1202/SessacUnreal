// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveInteraction.h"
#include "AIController.h"
#include "../AIPawn.h"
#include "../DefaultAIAnimInstance.h"
#include "../AIStateComponent.h"

UBTTask_MoveInteraction::UBTTask_MoveInteraction()
{
	NodeName = TEXT("MoveInteraction");

	// TickTask 함수를 호출한다.
	bNotifyTick = true;

	// OnTaskFinished 함수를 호출한다.
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_MoveInteraction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* AIPawn = Cast<AAIPawn>(Controller->GetPawn());


	if (!IsValid(AIPawn))
		return EBTNodeResult::Failed;

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));


	if (!IsValid(Target))
	{
		Controller->StopMovement();

		AIPawn->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Idle);

		return EBTNodeResult::Failed;
	}
	
	// 타겟의 위치로 NavMesh를 활용하여 길을 찾아 이동시킨다.
	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);
	AIPawn->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Run);

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_MoveInteraction::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_MoveInteraction::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* AIPawn = Cast<AAIPawn>(Controller->GetPawn());


	if (!IsValid(AIPawn))
	{
		// Task를 종료시킨다.
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Controller->StopMovement();

		AIPawn->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Idle);

		return;
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));


	if (!IsValid(Target))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Controller->StopMovement();

		AIPawn->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Idle);

		return;
	}

	// 현재 이동 방향을 향하도록 AI를 회전시킨다.
	FVector Dir = AIPawn->GetMovementComponent()->Velocity;
	Dir.Z = 0.f;

	// Dir은 현재 크기까지 가지고 있다. 그러므로 방향만 남기기 위해서 벡터를 정규화 시켜준다.
	Dir.Normalize();

	AIPawn->SetActorRotation(FRotator(0.0, Dir.Rotation().Yaw, 0.0));

	// 타겟과 AI폰과의 거리를 구한다.
	FVector	AILoc = AIPawn->GetActorLocation();
	FVector	TargetLoc = Target->GetActorLocation();

	AILoc.Z -= AIPawn->GetHalfHeight();
	TargetLoc.Z -= AIPawn->GetHalfHeight();

	float Distance = FVector::Distance(AILoc, TargetLoc);

	// 거리에서 각 물체들의 캡슐 반경을 빼준다.
	Distance -= AIPawn->GetCapsuleRadius();

	// Target의 RootComponent를 얻어와서 Capsule인지 확인한다.
	UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

	if (IsValid(Capsule))
	{
		Distance -= Capsule->GetScaledCapsuleRadius();
	}

	if (Distance <= AIPawn->GetAIState()->GetAttackDistance())
	{
		// Task를 종료시킨다.
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		Controller->StopMovement();
	}

}

void UBTTask_MoveInteraction::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
