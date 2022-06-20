// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellClass.h"
#include "Kismet/GameplayStatics.h"
#include <Sludge/SludgeCharacter.h>


#include "MovingSpell.generated.h"

/**
 * 
 */
class UCameraComponent;

UCLASS()
class SLUDGE_API AMovingSpell : public ASpellClass
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime);
	virtual void EndCasting() override;
	UFUNCTION(BlueprintImplementableEvent)
		void SetValidState(FHitResult HitResult);

private:
	void FindTargetLocation();

	UCameraComponent* FirstPersonCamera;
	/*UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool bLocationIsValid;*/
};
