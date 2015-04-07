// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "MainScene.generated.h"

UCLASS()
class FFMPROJECT_API AMainScene : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainScene();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void Manipulate();
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	APlayerController* GetPlayerController();
};
