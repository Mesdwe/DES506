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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCastingDelegate);

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
		bool bIsActivated;		//is able to cast runes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsUIActivated;	//show ui on staff
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsMenuActivated;	//show menu (button of the screen)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsCasting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ASpellClass* CurrentSpell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<Rune> CurrentRune;
	UFUNCTION(BlueprintCallable)
	void ActivateSpellCasting();

	UFUNCTION(BlueprintCallable)
		void ResetCurrentSpell();
	UFUNCTION(BlueprintImplementableEvent)
		void InvalidSpell();

	UPROPERTY(BlueprintAssignable)
		FCastingDelegate OnActivateCastingMenu;
	UPROPERTY(BlueprintAssignable)
		FCastingDelegate OnDeactivateCastingMenu;

	//Rune behaviour
	UFUNCTION(BlueprintImplementableEvent)
		void Rune1Behaviour();
	UFUNCTION(BlueprintImplementableEvent)
		void Rune2Behaviour();
	UFUNCTION(BlueprintImplementableEvent)
		void Rune3Behaviour();	
	UFUNCTION(BlueprintImplementableEvent)
		void Rune4Behaviour();

	void ReceiveInput(float Tone);

	//Different modes of casting
	UFUNCTION(BlueprintCallable)
	void CastSpell();
	UFUNCTION(BlueprintImplementableEvent)
		void ImmediatelyCast();

	UFUNCTION(BlueprintCallable)
	void CancelSelecting();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
 
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};


