// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/DefaultPawn.h"
#include "MyDefaultPawn.generated.h"

UCLASS()
class FFMPROJECT_API AMyDefaultPawn : public ADefaultPawn
{
	GENERATED_BODY()

public:

	AMyDefaultPawn(const FObjectInitializer& ObjectInitializer);

	void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	void BeginPlay() override;

public:
	void PlaceCube();
	APlayerController* GetController();
	FVector2D GetScreenPos();

private:

	void OnMouseMove( float val );
	void OnMouseLeftButtonDown();
	void OnMouseLeftButtonUp();
};