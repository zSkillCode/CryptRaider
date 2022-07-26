// © SkillCode - All Rights Reserved.

#include "Mover.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
}


// Called every frame
void UMover::TickComponent(const float DeltaTime, const ELevelTick TickType,
                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector TargetLocation = OriginalLocation;

	if (bShouldMove)
	{
		TargetLocation += MoveOffset;
	}

	const AActor* Owner = GetOwner();
	const FVector CurrentLocation = Owner->GetActorLocation();
	const float Speed = MoveOffset.Length() / MoveTime;
	const FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

	GetOwner()->SetActorLocation(NewLocation);
}

void UMover::SetShouldMove(const bool bNewShouldMove)
{
	bShouldMove = bNewShouldMove;
}
