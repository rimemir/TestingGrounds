// Fill out your copyright notice in the Description page of Project Settings.

#include "ChoosePatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Classes/AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChoosePatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ensure(ControlledPawn)) { return EBTNodeResult::Aborted; }
	UPatrolRoute* PatrolRouteComponent = Cast<UPatrolRoute>(ControlledPawn->FindComponentByClass<UPatrolRoute>());

	if (!ensure(PatrolRouteComponent)) { return EBTNodeResult::Aborted; }
	TArray<AActor*> PatrolPoints = PatrolRouteComponent->TargetPoints;

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComponent->GetValueAsInt(IndexSelector.SelectedKeyName);
	if (!ensure(BlackboardComponent)) { return EBTNodeResult::Aborted; }
	BlackboardComponent->SetValueAsObject(PointSelector.SelectedKeyName, PatrolPoints[Index]);
	BlackboardComponent->SetValueAsInt(IndexSelector.SelectedKeyName, ++Index % PatrolPoints.Num());

	return EBTNodeResult::Succeeded;
}
