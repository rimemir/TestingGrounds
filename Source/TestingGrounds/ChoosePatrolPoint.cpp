// Fill out your copyright notice in the Description page of Project Settings.

#include "ChoosePatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Classes/AIController.h"
#include "PatrollingGuard.h"

EBTNodeResult::Type UChoosePatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ensure(ControlledPawn)) { return EBTNodeResult::Aborted; }
	APatrollingGuard* Guard = Cast<APatrollingGuard>(ControlledPawn);
	if (!ensure(Guard)) { return EBTNodeResult::Aborted; }
	TArray<AActor*> PatrolPoints = Guard->TargetPointsCPP;

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComponent->GetValueAsInt(IndexSelector.SelectedKeyName);
	if (ensure(BlackboardComponent == nullptr)) { return EBTNodeResult::Aborted; }
	BlackboardComponent->SetValueAsObject(PointSelector.SelectedKeyName, PatrolPoints[Index]);
	BlackboardComponent->SetValueAsInt(IndexSelector.SelectedKeyName, ++Index % PatrolPoints.Num());

	return EBTNodeResult::Succeeded;
}
