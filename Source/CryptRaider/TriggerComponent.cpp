// © SkillCode - All Rights Reserved.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                      FActorComponentTickFunction* const ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Mover)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s's trigger component doesn't have Mover set"), *GetOwner()->GetName());
		return;
	}

	AActor* Actor = GetAcceptableActor();
	if (Actor)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component)
		{
			Component->SetSimulatePhysics(false);
		}
		Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
	}
	else
	{
		Mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* const NewMover)
{
	Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	if (!OverlappingActors.IsEmpty())
	{
		for (AActor* Actor : OverlappingActors)
		{
			if (Actor->ActorHasTag(ActorTag) && !Actor->ActorHasTag("grabbed"))
			{
				return Actor;
			}
		}
	}
	return nullptr;
}
