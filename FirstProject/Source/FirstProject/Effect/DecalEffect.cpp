
#include "DecalEffect.h"


ADecalEffect::ADecalEffect()
{
 	PrimaryActorTick.bCanEverTick = true;

	mDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));

	SetRootComponent(mDecal);

	mDecal->bVisualizeComponent = true;
	mDecal->DecalSize = FVector(128.0, 256.0, 256.0);
	mDecal->SetRelativeRotation(FRotator(-90.0, 0.0, 0.0));
}


void ADecalEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADecalEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADecalEffect::SetDecalMaterial(const FString& Path)
{
	UMaterialInterface* Material = LoadObject<UMaterialInterface>(this, *Path);

	if (IsValid(Material))
		mDecal->SetDecalMaterial(Material);
}

