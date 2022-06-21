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
	if (bIsMenuActivated)
	{
		ResetCurrentSpell();
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

void USpellComponent::ResetCurrentSpell()
{
		
		CurrentSequence = "";
		bIsActivated = false;
		bIsUIActivated = false;
		bIsMenuActivated = false;
		OnDeactivateCastingMenu();
		TSubclassOf<ASpellClass> SpellClass;
		SpellClass = ASpellClass::StaticClass();
		ASpellClass* SpellR = Cast<ASpellClass>(UGameplayStatics::GetActorOfClass(GetWorld(),SpellClass));
		if (SpellR != nullptr)
		{
			SpellR->EndCasting();
		}
		bIsCasting = false;
		
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Deactivate Casting Menu"));
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
			GetWorld()->SpawnActor(Sp.SpellClass,&Loc, &Rot, SpawnInfo);
			
			if (!Sp.bHasAdditionalInput)
			{
				//ResetCurrentSpell();
				ImmediatelyCast();
			}
			else
			{
				//selecting location
				CurrentSequence = "";
				bIsUIActivated = false;
				DelayCast();
				//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Deactivate Casting Menu"));
				//OnDeactivateCastingMenu();
			}
		}
	}
	if (CurrentSequence != "")
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Invalid Spell"));
		InvalidSpell();

		//USpellComponent::ResetCurrentSpell();
		//ActivateSpellCasting();
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
		bIsCasting = true;
		Rune1Behaviour();
	}
	else if (Tone == 2.0f)
	{
		NewTone = "B";
		CurrentRune = Rune2;
		bIsCasting = true;
		Rune2Behaviour();

	}
	else if (Tone == 3.0f)
	{
		NewTone = "C";
		CurrentRune = Rune3;
		bIsCasting = true;
		Rune3Behaviour();

	}
	else if (Tone == 4.0f)
	{
		NewTone = "D";
		CurrentRune = Rune4;
		bIsCasting = true;
		Rune4Behaviour();

	}
	CurrentSequence.Append(NewTone);
	if (CurrentSequence.Len() >= 4)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("CASTING"));
		USpellComponent::CastSpell();
	}
	//else
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, CurrentSequence);

}

