// Fill out your copyright notice in the Description page of Project Settings.

#include "FFMProject.h"
#include "MyDefaultPawn.h"
#include "BoxPrimitiveModel.h"

AMyDefaultPawn::AMyDefaultPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AMyDefaultPawn::BeginPlay()
{
	Super::BeginPlay();
	if (GetController())
		GetController()->bShowMouseCursor = true;
}

void AMyDefaultPawn::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAction("Manipulate", IE_Pressed, this, &AMyDefaultPawn::Manipulate);
}

void AMyDefaultPawn::Manipulate()
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
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Hit!!!!"));
				GetWorld()->SpawnActor<ABoxPrimitiveModel>(hitResults[i].Location, FRotator::ZeroRotator);
			}
		}
	}
}

APlayerController* AMyDefaultPawn::GetController()
{
	if (!GEngine)
		return NULL;

	return GEngine->GetFirstLocalPlayerController(GetWorld());
}