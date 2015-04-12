#pragma once

#include "GameFramework/DefaultPawn.h"
#include "EditTool.generated.h"

UCLASS()
class FFMPROJECT_API AEditTool : public ADefaultPawn
{
	GENERATED_BODY()

public:

	AEditTool(const FObjectInitializer& ObjectInitializer);

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