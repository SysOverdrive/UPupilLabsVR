// Fill out your copyright notice in the Description page of Project Settings.

#include "APupilLabsVisualMarkersPawn.h"


// Sets default values
AAPupilLabsVisualMarkersPawn::AAPupilLabsVisualMarkersPawn()
{	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CalibrationCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = CalibrationCamera;

	// Our root component will be a sphere that reacts to physics todo change the root component to square
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Sphere"));

	VRWorldAlignedPosition = CreateDefaultSubobject<USceneComponent>(TEXT("VRWorldAlignedPosition"));
	VRWorldAlignedPosition->SetAbsolute(true, true, true);
	VRWorldAlignedPosition->SetupAttachment(RootComponent);
	VRWorldAlignedPosition->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	///Static Mesh How the sphere looks
	SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(SphereComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(400.0f, 0.0f, 0.0f));
		SphereVisual->SetWorldScale3D(FVector(0.2f));
	}
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AAPupilLabsVisualMarkersPawn::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTarget(this);
	i = 1;
}

// Called every frame
void AAPupilLabsVisualMarkersPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAPupilLabsVisualMarkersPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("StartCalibration", IE_Released, this, &AAPupilLabsVisualMarkersPawn::StartCalibration);

}

void AAPupilLabsVisualMarkersPawn::UpdatePosition(int CurrentCalibrationPoint)
{
	UWorld* CurrentWorld = GetWorld();
	RedrawSphere(CurrentWorld, CurrentCalibrationPoint);
}

void AAPupilLabsVisualMarkersPawn::StartCalibration()
{
	UWorld* CurrentWorld = GetWorld();
	if (i<9) {
		RedrawSphere(CurrentWorld, i);
	}
	i++;
}


void AAPupilLabsVisualMarkersPawn::RedrawSphere(UWorld* CurrentWorld, int CurrentCalibrationPoint)
{
	FVector SphereNewPosition;
	int CalibrationType2DPointsNumber = 8;
	int Radius = 210;
	float CurrentCalibrationPointPositionX = 0.5, CurrentCalibrationPointPositionY = 0.5;
	if (GEngine->GameViewport && GEngine->GameViewport->Viewport)
	{
		CurrentCalibrationPointPositionX += Radius * (float)FMath::Cos(2 * PI * (float)(CurrentCalibrationPoint - 1) / (float)(CalibrationType2DPointsNumber - 1));
		CurrentCalibrationPointPositionY += Radius * (float)FMath::Sin(2 * PI * (float)(CurrentCalibrationPoint - 1) / (float)(CalibrationType2DPointsNumber - 1)) - 10;
		const float Distance = 100.0f;
		SphereNewPosition = FVector(Distance, CurrentCalibrationPointPositionX, CurrentCalibrationPointPositionY);
		SphereComponent->SetRelativeLocation(SphereNewPosition);

	}
	if (CurrentCalibrationPoint == 8)
	{
		SphereComponent->SetVisibility(false, true);	
	}
}
