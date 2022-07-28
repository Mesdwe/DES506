// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingSpell.h"
#include "Camera/CameraComponent.h"

void AMovingSpell::BeginPlay()
{
	Super::BeginPlay();
	AActor* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ASludgeCharacter* FPCharacter = Cast<ASludgeCharacter>(PlayerCharacter);
	BeginPlayBehaviour();
	if (FPCharacter != nullptr)
	{
		FirstPersonCamera = FPCharacter->GetFirstPersonCameraComponent();
	}
	else
		FirstPersonCamera = nullptr;

}
void AMovingSpell::Tick(float DeltaTime)
{
	AMovingSpell::FindTargetLocation();
}
void AMovingSpell::FindTargetLocation()
{
	FVector Loc;
	FRotator Rot;
	FHitResult Hit;

	Loc = FirstPersonCamera->GetComponentLocation();
	Rot = FirstPersonCamera->GetComponentRotation();
	FVector StartP = Loc;
	FVector EndP = StartP + (Rot.Vector() * MoveableRange);
	FCollisionQueryParams TraceParam;
	GetWorld()->LineTraceSingleByChannel(Hit, StartP, EndP, ECC_Visibility, TraceParam);

	if (Hit.GetActor() != nullptr)
	{
		
		SetValidState(Hit);
		this->SetActorLocationAndRotation(Hit.Location, FRotationMatrix::MakeFromZ(Hit.ImpactNormal).Rotator());
		return;
	}
	else
	{
		SetActorLocation(EndP);

		FVector Start2 = this->GetActorLocation();

		FVector End2 = Start2 + FVector(0.0f, 0.0f, -10000.0f);
		FHitResult Hit2;

		FCollisionQueryParams TraceParam2;
		GetWorld()->LineTraceSingleByChannel(Hit2, Start2, End2, ECC_Visibility, TraceParam2);
		if (Hit2.GetActor() != nullptr)
		{
			SetValidState(Hit2);

			//this->SetActorLocation(Hit2.Location);
			this->SetActorLocationAndRotation(Hit2.Location, FRotationMatrix::MakeFromZ(Hit2.ImpactNormal).Rotator());

		}
	}
}

void AMovingSpell::EndCasting()
{
	Super::EndCasting();
}
