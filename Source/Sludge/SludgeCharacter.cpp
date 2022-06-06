// Copyright Epic Games, Inc. All Rights Reserved.

#include "SludgeCharacter.h"
#include "SludgeProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ASludgeCharacter

ASludgeCharacter::ASludgeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;


	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);

	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

}

void ASludgeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}

void ASludgeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InteractLineTrace();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASludgeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//// Bind fire event
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASludgeCharacter::OnFire);

	//// Enable touchscreen input
	//EnableTouchscreenMovement(PlayerInputComponent);

	//PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ASludgeCharacter::OnResetVR);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ASludgeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASludgeCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &ASludgeCharacter::TurnMouse);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASludgeCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASludgeCharacter::LookUpAtRate);
}


void ASludgeCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		if (bIsClimbing)
		{
					// add movement in that direction
			AddMovementInput(GetActorUpVector(), Value);

		}
		else
		AddMovementInput(GetActorForwardVector(), Value);

	}
}

void ASludgeCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ASludgeCharacter::TurnAtRate(float Rate)
{
	if (bIsClimbing)
	{

	}
	if(!bIsClimbing)
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}
void ASludgeCharacter::TurnMouse(float Rate)
{
	if (bIsClimbing)
	{

	}
	if (!bIsClimbing)
		// calculate delta for this frame from the rate information
		AddControllerYawInput(Rate);
}

void ASludgeCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASludgeCharacter::InteractLineTrace()
{
	if (bIsClimbingUp) return;
	FVector Loc;
	FRotator Rot;
	FHitResult Hit;
	
	GetController()->GetPlayerViewPoint(Loc, Rot);

	FVector StartP = Loc;
	FVector EndP = StartP + (Rot.Vector() * 100);

	FCollisionQueryParams TraceParam;
	GetWorld()->LineTraceSingleByChannel(Hit, StartP, EndP, ECC_Visibility, TraceParam);

	//Climbing walls
	if (Hit.GetActor()!=nullptr&&Hit.GetActor()->ActorHasTag("Walls"))
	{
		ASludgeCharacter::ClimbingEdgeCheck();
		this->SetActorRotation(FRotator(0.0f, 0.0f, Hit.Normal.Rotation().Vector().Z));
		if (!bIsClimbing)
		{
			bIsClimbing = true;
			DrawDebugLine(GetWorld(), StartP, EndP, FColor::Green, false, 0.2f);

			GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);
			GetCharacterMovement()->MovementMode = MOVE_Flying;

			//GetCharacterMovement()->bOrientRotationToMovement = false;
			return;

		}
	}
	else if (bIsClimbing)
	{
		bIsClimbing = false;
		GetCharacterMovement()->MovementMode = MOVE_Walking;
	}
	DrawDebugLine(GetWorld(), StartP, EndP, FColor::Red, false, 0.2f);

	
}

void ASludgeCharacter::ClimbingEdgeCheck()
{
	FHitResult Hit;
	FVector Start = GetActorLocation() + FVector(0.0f, 0.0f, 110.0f);
	FVector Direction = GetActorForwardVector() * 100.0f;
	FVector End = Start + Direction;
	DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 0.2f);

	FCollisionQueryParams TraceParam;
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParam);

	if (Hit.GetActor() == nullptr && bIsClimbing)
	{
		bIsOnLedge = true;
	}
	else
	{
		bIsOnLedge = false;
	}
}
