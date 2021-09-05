// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"


void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDOverlayClass)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayClass);
		if (HUDOverlay)
		{
			HUDOverlay->AddToViewport();
			HUDOverlay->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AShooterPlayerController::GameModeOnly()
{
	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
	bShowMouseCursor = false;
}

void AShooterPlayerController::MouseCursorVisible()
{
	
	FInputModeGameAndUI InputModeGameAndUI;
	SetInputMode(InputModeGameAndUI);
	bShowMouseCursor = true;
}
