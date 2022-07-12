// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "DialogueComponent.generated.h"

UENUM(BlueprintType)
enum DialogueMoodType
{
	Angry     UMETA(DisplayName = "Angry"),
	Depressed      UMETA(DisplayName = "Depressed"),
	Neutral      UMETA(DisplayName = "Neutral"),
	Scared   UMETA(DisplayName = "Scared"),
	Whimsical UMETA(DisplayName = "Whimsical")
};

USTRUCT(BlueprintType)
struct FDialogueStructure : public FTableRowBase
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString DialogueContent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<DialogueMoodType> Mood;

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),Blueprintable )
class SLUDGE_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UDialogueComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
