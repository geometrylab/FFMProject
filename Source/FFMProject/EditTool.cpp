// Fill out your copyright notice in the Description page of Project Settings.

#include "FFMProject.h"
#include "EditTool.h"
#include "BoxPrimitiveModel.h"

AEditTool::AEditTool(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEditTool::BeginPlay()
{
	Super::BeginPlay();
	if (GetController())
		GetController()->bShowMouseCursor = true;
}

void AEditTool::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveCursorX", EKeys::MouseX, 1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveCursorY", EKeys::MouseY, -1.f));
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("LMB", EKeys::LeftMouseButton));

	InputComponent->BindAction("LMB", IE_Pressed, this, &AEditTool::OnMouseLeftButtonDown);
	InputComponent->BindAction("LMB", IE_Released, this, &AEditTool::OnMouseLeftButtonUp);
	InputComponent->BindAxis("MoveCursorX", this, &AEditTool::OnMouseMove);
	InputComponent->BindAxis("MoveCursorY", this, &AEditTool::OnMouseMove);
}

void AEditTool::PlaceCube()
{
	if (!GetController())
		return;

	FVector vLoc;
	FVector vDir;
	GetController()->DeprojectMousePositionToWorld(vLoc, vDir);

	FCollisionQueryParams lineParams;
	TArray<FHitResult> hitResults;

	vLoc += vDir * 50.0f;

	bool bHit = GetWorld()->LineTraceMulti(hitResults, vLoc, vLoc + vDir*100000.0f, ECC_WorldStatic, lineParams);
	if (bHit)
	{
		for (int i = 0, iCount(hitResults.Num()); i < iCount; ++i)
		{
			if (hitResults[i].bBlockingHit)
			{
				if( GEngine )
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Hit!!!!"));
				GetWorld()->SpawnActor<ABoxPrimitiveModel>(hitResults[i].Location, FRotator::ZeroRotator);
			}
		}
	}
}

APlayerController* AEditTool::GetController()
{
	if (!GEngine)
		return NULL;

	return GEngine->GetFirstLocalPlayerController(GetWorld());
}

void AEditTool::OnMouseMove(float val)
{
	if (GEngine)
	{
		FVector2D screenPos = GetScreenPos();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, screenPos.ToString());
	}
}

void AEditTool::OnMouseLeftButtonDown()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("LMB Down"));
	PlaceCube();
}

void AEditTool::OnMouseLeftButtonUp()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("LMB Up"));
}

FVector2D AEditTool::GetScreenPos()
{
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(GetController()->Player);
	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		FVector2D ScreenPosition;
		if (LocalPlayer->ViewportClient->GetMousePosition(ScreenPosition))
			return ScreenPosition;
	}
	return FVector2D(-1.0f, -1.0f);
}