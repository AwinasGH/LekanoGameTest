// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/LT_PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Character/Components/LT_MovementComponent.h"
#include "Character/Player/LT_PlayerController.h"
#include "Character/Player/LT_PlayerInputActions.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameMode/LT_GameHUD.h"
#include "GameMode/LT_GameInstance.h"


ALT_PlayerCharacter::ALT_PlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CharacterMovementComponent->bOrientRotationToMovement = true;
	CharacterMovementComponent->GravityScale = 1.0f;

	AddDefaultComponent(SpringArmComponent, USpringArmComponent, "SpringArmComponent", false)
	SpringArmComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	SpringArmComponent->SocketOffset = FVector(0, 50, 50);
	SpringArmComponent->SetRelativeLocation(FVector(0, 0, 100));
	SpringArmComponent->bUsePawnControlRotation = true;

	AddDefaultComponent(ThirdPersonCameraComponent, UCameraComponent, "ThirdPersonCameraComponent", false)
	ThirdPersonCameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
	ThirdPersonCameraComponent->bUsePawnControlRotation = false;
	ThirdPersonCameraComponent->SetActive(true);
}

void ALT_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//................Moving................//

	PlayerInputComponent->BindAxis(FPlayerInputActionNames::MoveForwardAxis, this, &ALT_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FPlayerInputActionNames::MoveRightAxis, this, &ALT_PlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis(FPlayerInputActionNames::LookRightAxis, this, &ALT_PlayerCharacter::LookRight);
	PlayerInputComponent->BindAxis(FPlayerInputActionNames::LookUpAxis, this, &ALT_PlayerCharacter::LookUp);
	
	PlayerInputComponent->BindAction(FPlayerInputActionNames::SprintAction, IE_Pressed, this, &ALT_PlayerCharacter::OnPressSprint);
	PlayerInputComponent->BindAction(FPlayerInputActionNames::SprintAction, IE_Released, this, &ALT_PlayerCharacter::OnReleaseSprint);

	PlayerInputComponent->BindAction(FPlayerInputActionNames::WalkAction, IE_Pressed, this, &ALT_PlayerCharacter::OnPressWalk);
	PlayerInputComponent->BindAction(FPlayerInputActionNames::WalkAction, IE_Released, this, &ALT_PlayerCharacter::OnReleaseWalk);

	//......................................//

	//..........Gameplay Actions............//

	PlayerInputComponent->BindAction(FPlayerInputActionNames::ParkourAction, IE_Pressed, this, &ALT_PlayerCharacter::OnPressParkourAction);

	//......................................//

	//................Open Menus.............//

	PlayerInputComponent->BindAction(FPlayerInputActionNames::OpenMenuAction, IE_Pressed, this, &ALT_PlayerCharacter::OnPressOpenMenu);

	//......................................//
	
}


void ALT_PlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ALT_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterMovementComponent->ChangeLegMoveType(ELegMoveType::Jog);
}

//....................................................Methods to bind with Input Actions.........................................................................//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//.....................Moving..................................//

void ALT_PlayerCharacter::MoveForward(float AxisValue)
{
	if( FMath::IsNearlyZero(AxisValue) || !GetCanMove() ) return;

	FVector ForwardVector;

	if( GetMovementComponent()->IsSwimming() || GetMovementComponent()->IsFlying() )
	{
		const FRotator LookRotate = FRotator(0.0f, GetActorRotation().Yaw, 0.0f);
		ForwardVector = FRotationMatrix(LookRotate).GetUnitAxis(EAxis::X);
	}
	else
	{
		ForwardVector = ThirdPersonCameraComponent->GetForwardVector();
	}

	AddMovementInput(ForwardVector, AxisValue);
}

void ALT_PlayerCharacter::MoveRight(float AxisValue)
{
	if( FMath::IsNearlyZero(AxisValue) || !GetCanMove() ) return;
	
	FVector RightVector;

	if( GetMovementComponent()->IsSwimming() || GetMovementComponent()->IsFlying() )
	{
		const FRotator LookRotate = FRotator(0.0f, GetActorRotation().Yaw, 0.0f);
		RightVector = FRotationMatrix(LookRotate).GetUnitAxis(EAxis::X);
	}
	else
	{
		RightVector = ThirdPersonCameraComponent->GetRightVector();
	}

	AddMovementInput(RightVector, AxisValue);
}



void ALT_PlayerCharacter::LookRight(float AxisValue)
{
	if( AxisValue != 0.0f )
	{
		this->AddControllerYawInput(AxisValue);
	}
}

void ALT_PlayerCharacter::LookUp(float AxisValue)
{
	if( AxisValue != 0.0f )
	{
		this->AddControllerPitchInput(AxisValue);
	}
}


void ALT_PlayerCharacter::OnPressWalk()
{
	CharacterMovementComponent->ChangeLegMoveType(ELegMoveType::Walk);
}

void ALT_PlayerCharacter::OnReleaseWalk()
{
	CharacterMovementComponent->ChangeLegMoveType(ELegMoveType::Jog);
}


void ALT_PlayerCharacter::OnPressSprint()
{
	CharacterMovementComponent->ChangeLegMoveType(ELegMoveType::Sprint);
}

void ALT_PlayerCharacter::OnReleaseSprint()
{
	CharacterMovementComponent->ChangeLegMoveType(ELegMoveType::Jog);
}



//............................................................//


//.....................Gameplay Actions.......................//

void ALT_PlayerCharacter::OnPressParkourAction()
{
	if( !GetCanMove() ) return;
	
	DoJump();
}

void ALT_PlayerCharacter::OnPressOpenMenu()
{
	const ULT_GameInstance* LGameInstance = Cast<ULT_GameInstance>(GetGameInstance());
	const ALT_PlayerController* LPlayerController = Cast<ALT_PlayerController>(GetController());
	
	if( !IsValid(LGameInstance) || !LGameInstance->GetIsGameStarted() || !IsValid(LPlayerController) ) return;
	

	if( ALT_GameHUD* LGameHUD = Cast<ALT_GameHUD>(LPlayerController->GetHUD()) ) LGameHUD->CreatePauseMenuWD();
}



//............................................................//

