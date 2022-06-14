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
	if (!bIsActivated)
	{
		ResetCurrentSpell();
		bIsActivated = true;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Activate Casting Menu"));
	}
	else
	{
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
		//TODO: Get all spell actors::EndCasting();
		/*TSubclassOf<AEnemy> classToFind;
		classToFind = AEnemy::StaticClass();
		TArray<AActor*> foundEnemies;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, foundEnemies);*/
	
		TSubclassOf<ASpellClass> SpellClass;
		SpellClass = ASpellClass::StaticClass();
		ASpellClass* SpellR = Cast<ASpellClass>(UGameplayStatics::GetActorOfClass(GetWorld(),SpellClass));
		if (SpellR != nullptr)
		{
			SpellR->EndCasting();
		}
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Deactivate Casting Menu"));
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
				ResetCurrentSpell();
			}
			else
			{
				CurrentSequence = "";
				bIsActivated = false;
			}
		}
	}
	if (CurrentSequence != "")
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Invalid Spell"));
		USpellComponent::ResetCurrentSpell();
		//ActivateSpellCasting();

	}
}
void USpellComponent::ReceiveInput(float Tone)
{
	FString NewTone = "";
	if (Tone == 1.0f)
	{
		NewTone = "A";
	}
	else if (Tone == 2.0f)
	{
		NewTone = "B";
	}
	else if (Tone == 3.0f)
	{
		NewTone = "C";
	}
	else if (Tone == 4.0f)
	{
		NewTone = "D";
	}
	CurrentSequence.Append(NewTone);
	if (CurrentSequence.Len() >= 4)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("CASTING"));
		//CurrentSequence = "";
		USpellComponent::CastSpell();

	}
	else
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, CurrentSequence);

}

