// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellClass.h"

// Sets default values
ASpellClass::ASpellClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpellClass::BeginPlay()
{
	Super::BeginPlay();
	BeginCasting();
}

void ASpellClass::BeginCasting()
{
	UE_LOG(LogTemp, Warning, TEXT("Spell Class begin casting"));
}

// Called every frame
void ASpellClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

