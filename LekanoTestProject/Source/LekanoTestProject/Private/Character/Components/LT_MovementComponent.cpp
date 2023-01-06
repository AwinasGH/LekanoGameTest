// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/LT_MovementComponent.h"

#include "Character/LT_CharacterBase.h"
#include "GameFramework/Character.h"


ULT_MovementComponent::ULT_MovementComponent()
{
	
}


FNetworkPredictionData_Client* ULT_MovementComponent::GetPredictionData_Client() const
{
	if( ClientPredictionData == nullptr )
	{
		// Return custom client prediction class instead
		ULT_MovementComponent* LCharacterMoveComp = const_cast<ULT_MovementComponent*>(this);
		LCharacterMoveComp->ClientPredictionData = new FNetworkPredictionData_Client_LT(*this);
	}

	return ClientPredictionData;
}

void ULT_MovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	/*  There are 4 custom move flags for us to use. Below is what each is currently being used for:
		FLAG_Custom_0		= 0x10, // Sprinting
		FLAG_Custom_1		= 0x20, // Jog
		FLAG_Custom_2		= 0x40, // Walk
		FLAG_Custom_3		= 0x80, // Unused
	*/

	// Read the values from the compressed flags
	bWantsToSprint = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
	bWantsToJog = (Flags & FSavedMove_Character::FLAG_Custom_1) != 0;
	bWantsToWalk = (Flags & FSavedMove_Character::FLAG_Custom_2) != 0;
}

float ULT_MovementComponent::GetMaxSpeed() const
{
	const ALT_CharacterBase* LOwnerCharacter = Cast<ALT_CharacterBase>(GetCharacterOwner());
	if( !IsValid(LOwnerCharacter) ) return 0.f;

	switch(MovementMode)
	{
		case MOVE_Walking:
		{
			if( bWantsToSprint )
			{
				return LOwnerCharacter->SprintSpeed;
			}
				
			if( bWantsToJog )
			{
				return LOwnerCharacter->JogSpeed;
			}
				
			if( bWantsToWalk )
			{
				return LOwnerCharacter->WalkSpeed;
			}
		}
		case MOVE_Falling: return Super::GetMaxSpeed();
	
		default: return 0.f;
	}
}

float ULT_MovementComponent::GetMaxAcceleration() const
{
	if( IsMovingOnGround() == true )
	{
		const ALT_CharacterBase* LOwnerCharacter = Cast<ALT_CharacterBase>(GetCharacterOwner());
		if( !IsValid(LOwnerCharacter) ) return 0.f;
		
		return LOwnerCharacter->MovingAcceleration;
	}
	
	return Super::GetMaxAcceleration();
}


void ULT_MovementComponent::ChangeLegMoveType_Client(ELegMoveType NewLegMoveType)
{
	ALT_CharacterBase* LOwnerCharacter = Cast<ALT_CharacterBase>(GetCharacterOwner());
	
	if( !IsValid(LOwnerCharacter) || !LOwnerCharacter->CanChangeLegMoveType(NewLegMoveType) ) return;
	
	ChangeLegMoveTypeContext(NewLegMoveType);
	
	LOwnerCharacter->OnLegMoveTypeChanged(NewLegMoveType);
	OnLegMoveTypeChangedBind.Broadcast(NewLegMoveType);
}

void ULT_MovementComponent::ChangeLegMoveType_ServerToAll_Implementation(ELegMoveType NewLegMoveTyp)
{
	ALT_CharacterBase* LOwnerCharacter = Cast<ALT_CharacterBase>(GetCharacterOwner());
	if( !IsValid(LOwnerCharacter) ) return;
	
	if( !LOwnerCharacter->IsLocallyControlled() )
	{
		LOwnerCharacter->OnLegMoveTypeChanged(NewLegMoveTyp);
		OnLegMoveTypeChangedBind.Broadcast(NewLegMoveTyp);
	}
}

void ULT_MovementComponent::ChangeLegMoveType(ELegMoveType NewLegMoveType)
{
	ChangeLegMoveType_Client(NewLegMoveType);
	
	ChangeLegMoveType_Server(NewLegMoveType);
}

void ULT_MovementComponent::ChangeLegMoveType_Server_Implementation(ELegMoveType NewLegMoveType)
{
	ALT_CharacterBase* LOwnerCharacter = Cast<ALT_CharacterBase>(GetCharacterOwner());
	if( !IsValid(LOwnerCharacter) || !LOwnerCharacter->CanChangeLegMoveType(NewLegMoveType) ) return;

	ChangeLegMoveTypeContext(NewLegMoveType);

	ChangeLegMoveType_ServerToAll(NewLegMoveType); 
}

void ULT_MovementComponent::ChangeLegMoveTypeContext(ELegMoveType NewLegMoveType)
{
	switch(NewLegMoveType)
	{
	case ELegMoveType::Walk:
		{
			bWantsToWalk = true;

			bWantsToJog = false;
			bWantsToSprint = false;
				
			break;
		}
	case ELegMoveType::Jog:
		{
			bWantsToJog = true;

			bWantsToSprint = false;
			bWantsToWalk = false;
				
			break;
		}
	case ELegMoveType::Sprint:
		{
			bWantsToSprint = true;

			bWantsToJog = false;
			bWantsToWalk = false;
				
			break;
		}
	default: ;
	}
}


void FSavedMove_LT::Clear()
{
	Super::Clear();

	// Clear all values
	SavedWantsToSprint = 0;
	SavedWantsToJog = 0;
	SavedWantsToWalk = 0;
}

uint8 FSavedMove_LT::GetCompressedFlags() const
{
	uint8 Result = FSavedMove_Character::GetCompressedFlags();

	/*  There are 4 custom move flags for us to use. Below is what each is currently being used for:
		FLAG_Custom_0		= 0x10, // Sprinting
		FLAG_Custom_1		= 0x20, // Jog
		FLAG_Custom_2		= 0x40, // Walk
		FLAG_Custom_3		= 0x80, // Unused
	*/

	// Write to the compressed flags 
	if( SavedWantsToSprint ) Result |= FLAG_Custom_0;
	if( SavedWantsToJog ) Result |= FLAG_Custom_1;
	if( SavedWantsToWalk ) Result |= FLAG_Custom_2;

	return Result;
}

void FSavedMove_LT::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	const ULT_MovementComponent* CharMoveComp = Cast<ULT_MovementComponent>(Character->GetCharacterMovement());
	if( !IsValid(CharMoveComp) ) return;

	SavedWantsToSprint = CharMoveComp->bWantsToSprint;
	SavedWantsToJog = CharMoveComp->bWantsToJog;
	SavedWantsToWalk = CharMoveComp->bWantsToWalk;
}

void FSavedMove_LT::PrepMoveFor(ACharacter* Character)
{
	Super::PrepMoveFor(Character);

	ULT_MovementComponent* CharMoveComp = Cast<ULT_MovementComponent>(Character->GetCharacterMovement());
	if( !IsValid(CharMoveComp) ) return;

	CharMoveComp->bWantsToSprint = SavedWantsToSprint;
	CharMoveComp->bWantsToJog = SavedWantsToJog;
	CharMoveComp->bWantsToWalk = SavedWantsToWalk;
}

FNetworkPredictionData_Client_LT::FNetworkPredictionData_Client_LT(const UCharacterMovementComponent& ClientMovement) : Super(ClientMovement)
{
	
}

FSavedMovePtr FNetworkPredictionData_Client_LT::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_LT);
}

