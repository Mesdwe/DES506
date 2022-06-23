// Fill out your copyright notice in the Description page of Project Settings.

#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Kismet/GameplayStatics.h"
#include "SpellComponent.h"

// Sets default values for this component's properties
USpellComponent::USpellComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentSpell = nullptr;
	// ...
}


// Called when the game starts
void USpellComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USpellComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpellComponent::ActivateSpellCasting()
{
	if (bIsMenuActivated && !bIsUIActivated)
	{
		//ResetCurrentSpell();
		return;
	}
	if (!bIsUIActivated)
	{
		//ResetCurrentSpell();
		CurrentRune = Default;
		bIsActivated = true;
		bIsUIActivated = true;
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Activate Casting Menu"));
		OnActivateCastingMenu();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Deactivate Casting Menu"));
		OnDeactivateCastingMenu();
		/*CurrentSequence = "";
		bIsActivated = false;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Deactivate Casting Menu"));*/

		USpellComponent::ResetCurrentSpell();
	}
}

void USpellComponent::CancelSelecting()
{
	if (bIsMenuActivated && !bIsUIActivated)
	{
		ResetCurrentSpell();
		//Remove spell instance
		TSubclassOf<ASpellClass> SpellClass;
		SpellClass = ASpellClass::StaticClass();
		ASpellClass* SpellR = Cast<ASpellClass>(UGameplayStatics::GetActorOfClass(GetWorld(), SpellClass));
		if (SpellR != nullptr)
		{
			SpellR->EndCasting();
		}
		return;
	}
}
void USpellComponent::ResetCurrentSpell()
{
		
		CurrentSequence = "";
		bIsActivated = false;
		bIsUIActivated = false;
		bIsMenuActivated = false;

		CurrentSpell = nullptr;
		OnDeactivateCastingMenu();

		bIsCasting = false;
}
void USpellComponent::CastSpell()
{

	for (FSpell Sp : Spells)
	{
		if (Sp.SpellSequence == CurrentSequence)
		{
			
			FVector Loc = GetOwner()->GetActorLocation();
			FRotator Rot = GetOwner()->GetActorRotation();
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			CurrentSpell = Cast<ASpellClass>(GetWorld()->SpawnActor(Sp.SpellClass,&Loc, &Rot, SpawnInfo));
			
			if (!Sp.bHasAdditionalInput)
			{
				ImmediatelyCast();
			}
			else
			{
				//selecting location
				CurrentSequence = "";
				bIsUIActivated = false;
				DelayCast();
			}
		}
	}
	if (CurrentSequence != "")
	{
		InvalidSpell();
	}
}



void USpellComponent::ReceiveInput(float Tone)
{
	if (bIsCasting) return;
	FString NewTone = "";
	if (Tone == 1.0f)
	{
		NewTone = "A";
		CurrentRune = Rune1;
		Rune1Behaviour();
	}
	else if (Tone == 2.0f)
	{
		NewTone = "B";
		CurrentRune = Rune2;
		Rune2Behaviour();

	}
	else if (Tone == 3.0f)
	{
		NewTone = "C";
		CurrentRune = Rune3;
		Rune3Behaviour();

	}
	else if (Tone == 4.0f)
	{
		NewTone = "D";
		CurrentRune = Rune4;
		Rune4Behaviour();

	}
	CurrentSequence.Append(NewTone);
	if (CurrentSequence.Len() >= 4)
	{
		//Enter casting mode, wait for animation stop playing
		bIsCasting = true;
	}

}

