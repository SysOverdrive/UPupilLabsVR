// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Chifor Tudor

#include "MyTestPupilActor.h"

AMyTestPupilActor::AMyTestPupilActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyTestPupilActor::BeginPlay()
{	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PupilActor>>>>BeginPlay"));
	//SPAWN PAWN
	FVector SpawnLocation(300, 0, 100);
	FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
	AAPupilLabsVisualMarkersPawn* CalibrationScenePawn = GetWorld()->SpawnActor<AAPupilLabsVisualMarkersPawn>(AAPupilLabsVisualMarkersPawn::StaticClass(), SpawnLocation, SpawnRotation, SpawnParameters);
	//SPAWN PAWN
	PupilComm = FPupilMsgWorker::StartListening();
	PupilComm->SetVisualsReference(CalibrationScenePawn); 
	PupilComm->OnNewData().AddUObject(this, &AMyTestPupilActor::OnNewPupilData);
	UE_LOG(LogTemp, Warning, TEXT("[%s][%d]"), TEXT(__FUNCTION__), __LINE__);
}
// Called every frame
void AMyTestPupilActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyTestPupilActor::OnNewPupilData(GazeStruct *GazeStructure)
{
	this->ReceivedGazeStructure = GazeStructure;
	//UE_LOG(LogTemp, Warning, TEXT("[%s][%d]"), TEXT(__FUNCTION__), __LINE__);
	UE_LOG(LogTemp, Warning, TEXT("[%s][%d] Norm Data : %f"), TEXT(__FUNCTION__), __LINE__, this->ReceivedGazeStructure->base_data.pupil.ellipse.center.x);
	UWorld* CurrentWorld = GetWorld();
	PerformRaycast(CurrentWorld);
}

void AMyTestPupilActor::PerformRaycast(UWorld* CurrentWorld)
{
	APlayerController* UPupilPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	FVector TraceStart;
	FVector TraceEnd;
	float XGaze = ReceivedGazeStructure->base_data.pupil.norm_pos.x;
	float YGaze = ReceivedGazeStructure->base_data.pupil.norm_pos.y;
	if (GEngine->GameViewport && GEngine->GameViewport->Viewport)
	{
		const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		FVector WorldLocation;
		FVector WorldDirection;

		if (ReceivedGazeStructure != nullptr && UPupilPlayerController->DeprojectScreenPositionToWorld(ViewportSize.X * XGaze, ViewportSize.Y * (1.0f - YGaze), WorldLocation, WorldDirection))
		{
			const float TraceDistance = 250.0f; // Your desired trace distance (in UU - centimiters)
			TraceStart = WorldLocation;
			TraceEnd = TraceStart + WorldDirection * TraceDistance;
		}
	}

	FHitResult* HitResult = new FHitResult(ForceInit);
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*HitResult, TraceStart, TraceEnd, ECC_Visibility, *TraceParams))
	{
	//	UE_LOG(LogTemp, Warning, TEXT("[%s][%d]RAYTRACE XXX : %f"), TEXT(__FUNCTION__), __LINE__, XGaze);
	//	UE_LOG(LogTemp, Warning, TEXT("[%s][%d]RAYTRACE YYY : %f"), TEXT(__FUNCTION__), __LINE__, YGaze);
		FVector_NetQuantize var = HitResult->ImpactPoint;
		FVector HitPointLocation = var;
		DrawDebugPoint(GetWorld(), TraceEnd, 20, FColor(0, 255, 127), false, 1.03);

		DrawDebugPoint(GetWorld(), HitPointLocation, 20, FColor(0, 0, 238), false, 0.03);
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor(238, 0, 238), true);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("End Point: %d, %d, %d"), TraceEnd.X, TraceEnd.Y, TraceEnd.Z));

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("You hit: %s"), *HitResult->Actor->GetName()));
	}
}

////MOUSE TEST
//FMatrix CameraViewMatrix; //Todo maybe this is the way
//FMatrix CameraProjectionMatrix;
//FMatrix inv = Inverse(CameraProjectionMatrix * CameraViewMatrix);
////