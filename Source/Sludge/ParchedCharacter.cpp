// Fill out your copyright notice in the Description page of Project Settings.


#include "ParchedCharacter.h"

// Sets default values
AParchedCharacter::AParchedCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//InitDialogueQuips();
}

// Called when the game starts or when spawned
void AParchedCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitDialogueQuips();
	PreviousIndex = -1;

	
}
void AParchedCharacter::InitDialogueQuips()
{
	if (DialogueDataTable)
	{
		TArray<FName> RowNames = DialogueDataTable->GetRowNames();
		for(FName names : RowNames)
		{
			FDialogueStructure* Item = DialogueDataTable->FindRow<FDialogueStructure>(names, "");
			if (Item != nullptr && Item->Mood == Mood)
			{
				DialogueQuips.Add(Item->DialogueContent);
				UE_LOG(LogTemp, Warning, TEXT("I just started running"));
			}
		}
	}
}

FString AParchedCharacter::GetRandomQuip()
{
	//PreviousIndex=FMath::RandRange(0, DialogueQuips.Num() - 1);
	int RandN = FMath::RandRange(0, DialogueQuips.Num() - 1);
	while (PreviousIndex == RandN)
	{
		RandN = FMath::RandRange(0, DialogueQuips.Num() - 1);
	}
	PreviousIndex = RandN;
	return DialogueQuips[PreviousIndex];
}
// Called every frame
void AParchedCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

