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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginCasting();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
