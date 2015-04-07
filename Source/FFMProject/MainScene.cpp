// Fill out your copyright notice in the Description page of Project Settings.

#include "FFMProject.h"
#include "MainScene.h"

// Sets default values
AMainScene::AMainScene()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMainScene::BeginPlay()
{
	Super::BeginPlay();
	if (GetPlayerController() )
		GetPlayerController()->bShowMouseCursor = true;	
}

// Called every frame
void AMainScene::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Called to bind functionality to input
void AMainScene::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("Manipulate", IE_Pressed, this, &AMainScene::Manipulate);
	InputComponent->BindAxis("MoveForward", this, &AMainScene::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMainScene::MoveRight);
}

void AMainScene::Manipulate()
{
	if (!GetPlayerController())
		return;

	FVector vLoc;
	FVector vDir;
	GetPlayerController()->DeprojectMousePositionToWorld(vLoc, vDir);

	FCollisionQueryParams lineParams;
	FHitResult hitResult;

	bool bHit = GetWorld()->LineTraceSingle(hitResult, vLoc, vLoc + vDir*100000.0f, ECC_WorldStatic, lineParams);
	if (bHit)
	{
		MessageBox(NULL, TEXT("AAA"), TEXT("AAAAA"), MB_OK);
		//GetWorld()->SpawnActor<ABoxPrimitiveModel>(vLoc, FRotator::ZeroRotator);
	}
}

void AMainScene::MoveForward(float AxisValue)
{
}

void AMainScene::MoveRight(float AxisValue)
{

}

APlayerController* AMainScene::GetPlayerController()
{
	if (!GEngine)
		return NULL;

	return GEngine->GetFirstLocalPlayerController(GetWorld());
}