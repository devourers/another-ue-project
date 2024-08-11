// Fill out your copyright notice in the Description page of Project Settings.


#include "FadingActor.h"

// Sets default values
AFadingActor::AFadingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetMaterial(0, NormalMaterial);
}

// Called when the game starts or when spawned
void AFadingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFadingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFadingActor::OnPlayerBehind() {
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	Mesh->SetMaterial(0, SeeThroughMaterial);
}


void AFadingActor::OnPlayerNoLongerBehind() {
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	Mesh->SetMaterial(0, NormalMaterial);
}
