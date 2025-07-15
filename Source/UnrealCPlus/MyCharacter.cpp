// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyAnimInstance.h"




// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));

	}

	//static ConstructorHelpers::FClassFinder<UMyAnimInstance> AI(TEXT("/Script/Engine.AnimBlueprint'/Game/Animation/ABP_MyCharacter.ABP_MyCharacter_C'"));
	//if (AI.Succeeded())
	//{
	//	GetMesh()->SetAnimClass(AI.Class);
	//} //BP에서 설정해주기 때문에 주석처리

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	CameraBoom->SetupAttachment(RootComponent);
	FollowCamera->SetupAttachment(CameraBoom);

	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	//Todo
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("ForwardBackward"), this, &AMyCharacter::KeyForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::KeyLeftRight);

	PlayerInputComponent->BindAxis(TEXT("LookUpDown"), this, &AMyCharacter::LookUpDown);
	PlayerInputComponent->BindAxis(TEXT("LookLeftRight"), this, &AMyCharacter::LookLeftRight);


	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyCharacter::KeyAttack);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyCharacter::KeyJump);
}

void AMyCharacter::KeyForwardBackward(float Value) {
	AddMovementInput(GetActorForwardVector(), Value, false);
}

void AMyCharacter::KeyLeftRight(float Value) {
	AddMovementInput(GetActorRightVector(), Value, false);
}

void AMyCharacter::LookUpDown(float Value)
{
	AddControllerPitchInput(Value);
}

void AMyCharacter::LookLeftRight(float Value)
{
	AddControllerYawInput(Value);
}

void AMyCharacter::KeyAttack()
{
	UE_LOG(LogTemp, Log, TEXT("Attack"));
}

void AMyCharacter::KeyJump()
{
	UE_LOG(LogTemp, Log, TEXT("Jump"));
}