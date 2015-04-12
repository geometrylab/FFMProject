// Fill out your copyright notice in the Description page of Project Settings.

#include "FFMProject.h"
#include "EditTool.h"
#include "BoxPrimitiveModel.h"

EditTool::EditTool(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void EditTool::BeginPlay()
{
	Super::BeginPlay();
	if (GetController())
		GetController()->bShowMouseCursor = true;
}

void EditTool::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveCursorX", EKeys::MouseX, 1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveCursorY", EKeys::MouseY, -1.f));
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("LMB", EKeys::LeftMouseButton));

	InputComponent->BindAction("LMB", IE_Pressed, this, &EditTool::OnMouseLeftButtonDown);
	InputComponent->BindAction("LMB", IE_Released, this, &EditTool::OnMouseLeftButtonUp);
	InputComponent->BindAxis("MoveCursorX", this, &EditTool::OnMouseMove);
	InputComponent->BindAxis("MoveCursorY", this, &EditTool::OnMouseMove);
}

void EditTool::PlaceCube()
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

APlayerController* EditTool::GetController()
{
	if (!GEngine)
		return NULL;

	return GEngine->GetFirstLocalPlayerController(GetWorld());
}

void EditTool::OnMouseMove(float val)
{
	if (GEngine)
	{
		FVector2D screenPos = GetScreenPos();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, screenPos.ToString());
	}
}

void EditTool::OnMouseLeftButtonDown()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("LMB Down"));
	PlaceCube();
}

void EditTool::OnMouseLeftButtonUp()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("LMB Up"));
}

FVector2D EditTool::GetScreenPos()
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