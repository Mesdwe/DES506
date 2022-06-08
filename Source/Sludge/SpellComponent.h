// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellClass.h"

#include "SpellComponent.generated.h"

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
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

	//	void ActivateSpellCasting();
	//UFUNCTION(BlueprintCallable)
	//	void ReceiveInput(FString CurSequence);
	//UFUNCTION(BlueprintCallable)
	//	void CheckSpellSequence();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};


