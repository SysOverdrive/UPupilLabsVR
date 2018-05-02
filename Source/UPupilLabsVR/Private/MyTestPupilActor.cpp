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
	PupilComm = FPupilMsgWorker::StartListening();
	PupilComm->OnNewData().AddUObject(this, &AMyTestPupilActor::OnNewPupilData);


}
// Called every frame
void AMyTestPupilActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FConstCameraActorIterator MyTestCameraIterator = GetWorld()->GetAutoActivateCameraIterator();
	UWorld* CurrentWorld = GetWorld();
	PerformRaycast(CurrentWorld);
}

void AMyTestPupilActor::OnNewPupilData(GazeStruct *GazeStructure)
{
	this->ReceivedGazeStructure = GazeStructure;
	//UE_LOG(LogTemp, Warning, TEXT("[%s][%d]"), TEXT(__FUNCTION__), __LINE__);
	UE_LOG(LogTemp, Warning, TEXT("[%s][%d] Norm Data : %f"), TEXT(__FUNCTION__), __LINE__, this->ReceivedGazeStructure->base_data.pupil.ellipse.center.x);
}

void AMyTestPupilActor::PerformRaycast(UWorld* CurrentWorld)
{
	APlayerController* UPupilPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FVector CameraLocation;
	FRotator CameraRotator;

	UPupilPlayerController->GetPlayerViewPoint(CameraLocation, CameraRotator);
	FHitResult* HitResult = new FHitResult(ForceInit);
	const FVector StartTrace = CameraLocation;
	const FVector ForwardVector = CameraRotator.Vector();
	FVector EndTrace = ((ForwardVector *5000.f) + StartTrace);
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	if(GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(238, 0, 238), true);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("You hit: %s"), *HitResult->Actor->GetName()));
	}
}
