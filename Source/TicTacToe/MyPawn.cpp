// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <UObject/ConstructorHelpers.h>
#include "Containers/Array.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Spheres.Init(NULL, 9);
	Spheres[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	Spheres[1] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	Spheres[2] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh3"));
	Spheres[3] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh4"));
	Spheres[4] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh5"));
	Spheres[5] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh6"));
	Spheres[6] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh7"));
	Spheres[7] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh8"));
	Spheres[8] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh9"));

	RootComponent = Spheres[4];
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	for (int i=0; i < 9; i++)
	{
		if (i != 4)
		{
			Spheres[i]->SetupAttachment(GetRootComponent());
		}
		Spheres[i]->SetStaticMesh(MeshComponentAsset.Object);
	}



	Red = CreateDefaultSubobject<UMaterial>(TEXT("RedMaterial"));
	Blue = CreateDefaultSubobject<UMaterial>(TEXT("BlueMaterial"));
	White = CreateDefaultSubobject<UMaterial>(TEXT("WhiteMaterial"));


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 500.f;

	// Attach the Camera to SpringArm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);



	Spheres[0]->SetRelativeLocation(FVector(200.f, -200.f, 0.f));
	Spheres[1]->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
	Spheres[2]->SetRelativeLocation(FVector(200.f, 200.f, 0.f));
	Spheres[3]->SetRelativeLocation(FVector(0.f, -200.f, 0.f));
	Spheres[4]->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	Spheres[5]->SetRelativeLocation(FVector(0.f, 200.f, 0.f));
	Spheres[6]->SetRelativeLocation(FVector(-200.f, -200.f, 0.f));
	Spheres[7]->SetRelativeLocation(FVector(-200.f, 0.f, 0.f));
	Spheres[8]->SetRelativeLocation(FVector(-200.f, 200.f, 0.f));

	TurnCounter = 0;
	won = false;
	SphereStatus.Init(NULL, 9);
	SphereN.Init(0, 9);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	for (int i=0; i < 9; i++)
	{
		Spheres[i]->SetMaterial(0, White);
	}
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("1", IE_Pressed, this, &AMyPawn::OnePressed);
	PlayerInputComponent->BindAction("2", IE_Pressed, this, &AMyPawn::TwoPressed);
	PlayerInputComponent->BindAction("3", IE_Pressed, this, &AMyPawn::ThreePressed);
	PlayerInputComponent->BindAction("4", IE_Pressed, this, &AMyPawn::FourPressed);
	PlayerInputComponent->BindAction("5", IE_Pressed, this, &AMyPawn::FivePressed);
	PlayerInputComponent->BindAction("6", IE_Pressed, this, &AMyPawn::SixPressed);
	PlayerInputComponent->BindAction("7", IE_Pressed, this, &AMyPawn::SevenPressed);
	PlayerInputComponent->BindAction("8", IE_Pressed, this, &AMyPawn::EightPressed);
	PlayerInputComponent->BindAction("9", IE_Pressed, this, &AMyPawn::NinePressed);

}

void AMyPawn::OnePressed()
{
	TurnController(0);

}

void AMyPawn::TwoPressed()
{
	TurnController(1);
}

void AMyPawn::ThreePressed()
{
	TurnController(2);
}

void AMyPawn::FourPressed()
{
	TurnController(3);
}

void AMyPawn::FivePressed()
{
	TurnController(4);
}

void AMyPawn::SixPressed()
{
	TurnController(5);
}

void AMyPawn::SevenPressed()
{
	TurnController(6);
}

void AMyPawn::EightPressed()
{
	TurnController(7);
}

void AMyPawn::NinePressed()
{
	TurnController(8);
}

void AMyPawn::checkIfWon() {
	if (TurnCounter > 2) {
		if (SphereN[0] == 1 && SphereN[1] == 1 && SphereN[2] == 1 ||
			SphereN[0] == 2 && SphereN[1] == 2 && SphereN[2] == 2 ||

			SphereN[3] == 1 && SphereN[4] == 1 && SphereN[5] == 1 ||
			SphereN[3] == 2 && SphereN[4] == 2 && SphereN[5] == 2 ||

			SphereN[6] == 1 && SphereN[7] == 1 && SphereN[8] == 1 ||
			SphereN[6] == 2 && SphereN[7] == 2 && SphereN[8] == 2 ||

			SphereN[0] == 1 && SphereN[3] == 1 && SphereN[6] == 1 ||
			SphereN[0] == 2 && SphereN[3] == 2 && SphereN[6] == 2 ||

			SphereN[1] == 1 && SphereN[4] == 1 && SphereN[7] == 1 ||
			SphereN[1] == 2 && SphereN[4] == 2 && SphereN[7] == 2 ||

			SphereN[2] == 1 && SphereN[5] == 1 && SphereN[8] == 1 ||
			SphereN[2] == 2 && SphereN[5] == 2 && SphereN[8] == 2 ||

			SphereN[0] == 1 && SphereN[4] == 1 && SphereN[8] == 1 ||
			SphereN[0] == 2 && SphereN[4] == 2 && SphereN[8] == 2 ||

			SphereN[6] == 1 && SphereN[4] == 1 && SphereN[2] == 1 ||
			SphereN[6] == 2 && SphereN[4] == 2 && SphereN[2] == 2) {
			won = true;
		}
	}
}

void AMyPawn::TurnController(int sphereindex)
{
	if (SphereStatus[sphereindex] == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("That index is already taken"));

		return;
	}

	if (won == false) {
		if (TurnCounter % 2 == 0)
		{
			Spheres[sphereindex]->SetMaterial(0, Blue);
			SphereN[sphereindex] = 1;
			checkIfWon();
			if (won == true) {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Blue won!"));
			}
		}
		else if (TurnCounter % 2 == 1)
		{
			Spheres[sphereindex]->SetMaterial(0, Red);
			SphereN[sphereindex] = 2;
			checkIfWon();
			if (won == true) {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Red won!"));
			}
		}
		
		SphereStatus[sphereindex] = true;

		TurnCounter++;

		if (TurnCounter == 9 && won == false) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Draw!"));
		}
	}
}