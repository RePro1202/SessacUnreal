// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "AIController.h"
#include "../AIPawn.h"
#include "../DefaultAIAnimInstance.h"
#include "../AIStateComponent.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");

	// TickTask 함수를 호출한다.
	bNotifyTick = true;

	// OnTaskFinished 함수를 호출한다.
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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


	AIPawn->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Attack);

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_Attack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	// 공격 모션이 끝났는지를 판단한다.
	if (AIPawn->GetAttackEnd())
	{
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

		if (Distance > AIPawn->GetAIState()->GetAttackDistance())
		{
			// Task를 종료시킨다.
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		// 여전히 공격거리 안에 존재할 경우 타켓쪽으로 방향을 전환한다.
		else
		{
			FVector Dir = TargetLoc - AILoc;
			Dir.Z = 0.0;

			Dir.Normalize();

			AIPawn->SetActorRotation(FRotator(0.0, Dir.Rotation().Yaw, 0.0));
		}

		AIPawn->SetAttackEnd(false);
	}
}

void UBTTask_Attack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
