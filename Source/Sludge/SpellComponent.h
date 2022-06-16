// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "SpellClass.h"
#include "SpellComponent.generated.h"


UENUM(BlueprintType)
enum Rune
{
	Rune1     UMETA(DisplayName = "Rune1"),
	Rune2      UMETA(DisplayName = "Rune2"),
	Rune3      UMETA(DisplayName = "Rune3"),
	Rune4   UMETA(DisplayName = "Rune4"),
	Default UMETA(DisplayName = "Default")
};

USTRUCT(BlueprintType)
struct FSpell
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName SpellName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SpellSequence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ASpellClass>  SpellClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bHasAdditionalInput;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class SLUDGE_API USpellComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpellComponent();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		TArray<FSpell> Spells;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString CurrentSequence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsActivated;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsUIActivated;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsCasting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<Rune> CurrentRune;
	void ActivateSpellCasting();

	UFUNCTION(BlueprintCallable)
		void ResetCurrentSpell();
	UFUNCTION(BlueprintImplementableEvent)
		void InvalidSpell();
	UFUNCTION(BlueprintImplementableEvent)
		void OnActivateCastingMenu();
	UFUNCTION(BlueprintImplementableEvent)
		void OnDeactivateCastingMenu();
	void ReceiveInput(float Tone);
	//UFUNCTION(BlueprintCallable)
	void CastSpell();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
 
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};


