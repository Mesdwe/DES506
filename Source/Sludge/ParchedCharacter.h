// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DialogueComponent.h"
#include "ParchedCharacter.generated.h"

UCLASS()
class SLUDGE_API AParchedCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParchedCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TEnumAsByte<DialogueMoodType> Mood;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	void InitDialogueQuips();

	UFUNCTION(BlueprintCallable)
	FString GetRandomQuip();

	

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		class UDataTable* DialogueDataTable;
	UPROPERTY()
	TArray<FString> DialogueQuips;

	int PreviousIndex;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
