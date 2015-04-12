// Fill out your copyright notice in the Description page of Project Settings.

#include "FFMProject.h"
#include "ModelObject.h"

// Sets default values
AModelObject::AModelObject() :
	 m_pModel(new FFMGeometry::Model)
	,m_pBrush(new FFMGeometry::Brush)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AModelObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AModelObject::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}