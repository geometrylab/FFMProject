// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ModelObjet.generated.h"
#include "Geometry/Model.h"
#include "Geometry/Brush.h"

UCLASS()
class FFMPROJECT_API AModelObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AModelObject();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:
    
    FFMGeometry::ModelPtr m_pModel;
    FFMGeometry::BrushPtr m_pBrush;
};
