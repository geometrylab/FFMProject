// Fill out your copyright notice in the Description page of Project Settings.

#include "FFMProject.h"
#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();

	if( camera )
	{
		APlayerController* player = UGameplayStatics::GetPlayerController(this, 0);
		player->SetViewTarget(camera);
	}

	if( GEngine )
		GEngine->GetFirstLocalPlayerController(GetWorld());
}

// Called every frame
void ACameraDirector::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

