// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerExtend.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AAIControllerExtend::AAIControllerExtend()
{
	SetGenericTeamId(FGenericTeamId(5));
	perceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("sightConfig"));

	if (perceptionComp && sightConfig)
	{
		perceptionComp->ConfigureSense(*sightConfig);
		perceptionComp->SetDominantSense(sightConfig->GetSenseImplementation());

		sightConfig->SightRadius = 2000.f;
		sightConfig->LoseSightRadius = 2200.f;
		sightConfig->PeripheralVisionAngleDegrees = 90.f;

		sightConfig->DetectionByAffiliation.bDetectNeutrals = false;
		sightConfig->DetectionByAffiliation.bDetectEnemies = true;
		sightConfig->DetectionByAffiliation.bDetectFriendlies = false;	
	}
}


ETeamAttitude::Type AAIControllerExtend::GetTeamAttitudeTowards(const AActor& Other) const
{

	if (const APawn* OtherPawn = Cast<APawn>(&Other)) {

		// DEFAULT BEHAVIOR---------------------------------------------------
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
		}

		//OR CUSTOM BEHAVIOUR--------------------------------------------------
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			//Create an alliance with Team with ID 10 and set all the other teams as Hostiles:
			FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();
			if (OtherTeamID == 10) {
				return ETeamAttitude::Neutral;
			}
			else {
				return ETeamAttitude::Hostile;
			}
		}
	}

	return ETeamAttitude::Neutral;
}
