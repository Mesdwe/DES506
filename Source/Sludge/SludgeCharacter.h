// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpellComponent.h"

#include "SludgeCharacter.generated.h"
class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class ASludgeCharacter : public ACharacter
{
	GENERATED_BODY()


	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;



public:
	ASludgeCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MouseRotateSpeed = 0.6f;
	UPROPERTY(BlueprintReadWrite)
		bool bIsClimbing;
	UPROPERTY(BlueprintReadWrite)
		bool bIsOnLedge;
	UPROPERTY(BlueprintReadWrite)
		bool bIsClimbingUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpellComponent* Spell;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bIsCasting;
	//UPROPERTY(EditDefaultOnly)
		//USpellComponentTemplate

	APlayerController* PlayerController;
protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);


public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float CurrentTone;

	UFUNCTION(BlueprintImplementableEvent)
		void ClimbBehaviour(bool ClimbState);
	UFUNCTION(BlueprintImplementableEvent)
		void ClimbMeshBehaviour(FVector Dir,FVector Loc);
protected:
	void Jump();
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnMouse(float Rate);
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	void LookUpMouse(float Rate);
	void SpellCasting();
	void ToneInput(float Rate);
	void Tone1Input();
	void Tone2Input();
	void Tone3Input();
	void Tone4Input();

	void InteractLineTrace();
	void ClimbingEdgeCheck();

	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface


public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

