
#include "DecalEffect.h"


ADecalEffect::ADecalEffect()
{
 	PrimaryActorTick.bCanEverTick = true;

	mDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));

	SetRootComponent(mDecal);

	mDecal->bVisualizeComponent = true;
	mDecal->DecalSize = FVector(128.0, 256.0, 256.0);
	mDecal->SetRelativeRotation(FRotator(-90.0, 0.0, 0.0));

	mTime = 0.f;
	mFadeEnable = true;
}


void ADecalEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADecalEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mFadeEnable && IsValid(mDecalMaterial))
	{
		mTime += DeltaTime;

		float Opacity = 1.f - mTime / InitialLifeSpan;

		mDecalMaterial->SetScalarParameterValue(TEXT("Opacity"), Opacity);
	}
}

void ADecalEffect::SetDecalMaterial(const FString& Path)
{
	UMaterialInterface* Material = LoadObject<UMaterialInterface>(this, *Path);

	if (IsValid(Material))
	{
		mDecal->SetDecalMaterial(Material);

		mDecalMaterial = mDecal->CreateDynamicMaterialInstance();
	}
		
}

