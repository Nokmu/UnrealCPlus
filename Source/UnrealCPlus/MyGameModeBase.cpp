// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
	//DefaultPawnClass = AMyCharacter::StaticClass(); 밑에건 왜 DefaultPawnClass = AMyCharacter::StaticClass();로 안했을까?

	static ConstructorHelpers::FClassFinder<AMyCharacter> BP_Player(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_MyCharacter.BP_MyCharacter_C'"));


	if (BP_Player.Succeeded())
	{
		DefaultPawnClass = BP_Player.Class;

	}
}

