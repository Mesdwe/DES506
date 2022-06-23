// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpellClass.generated.h"

UCLASS()
class SLUDGE_API ASpellClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpellClass();
	virtual void EndCasting();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BeginCasting();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SuccessfulCast();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bHasAdditionalInput;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
