// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidget.h"

void UStartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	LOG(TEXT("NativeOnInitialized()"));
}

void UStartWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	LOG(TEXT("NativePreConstruct()"));
}

void UStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LOG(TEXT("NativeConstruct()"));

	mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	mExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitButton")));

	mStartButton->OnClicked.AddDynamic(this, &UStartWidget::StartButtonClick);
	mStartButton->OnHovered.AddDynamic(this, &UStartWidget::StartButtonHovered);
	mStartButton->OnUnhovered.AddDynamic(this, &UStartWidget::StartButtonUnHovered);

	mExitButton->OnClicked.AddDynamic(this, &UStartWidget::ExitButtonClick);
	mExitButton->OnHovered.AddDynamic(this, &UStartWidget::ExitButtonHovered);
	mExitButton->OnUnhovered.AddDynamic(this, &UStartWidget::ExitButtonUnHovered);

	// UserWidget이 가지고 있는 모든 Animation을 반복하며 찾는다.
	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();

	for (int32 i = 0; i < WidgetClass->Animations.Num(); i++)
	{
		FString Name = WidgetClass->Animations[i]->GetName();
		LOG(TEXT("Name : %s"), *Name);
	}

}

void UStartWidget::NativeDestruct()
{
	Super::NativeDestruct();

	LOG(TEXT("NativeDestruct()"));
}

void UStartWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}



FReply UStartWidget::NativeOnKeyChar(const FGeometry& InGeometry, const FCharacterEvent& InCharEvent)
{
	FReply Replay = Super::NativeOnKeyChar(InGeometry, InCharEvent);

	return Replay;
}

FReply UStartWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Replay = Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);

	return Replay;
}

FReply UStartWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Replay = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	return Replay;
}

FReply UStartWidget::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Replay = Super::NativeOnKeyUp(InGeometry, InKeyEvent);

	return Replay;
}

FReply UStartWidget::NativeOnAnalogValueChanged(const FGeometry& InGeometry, const FAnalogInputEvent& InAnalogEvent)
{
	FReply Replay = Super::NativeOnAnalogValueChanged(InGeometry, InAnalogEvent);

	return Replay;
}

FReply UStartWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Replay = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return Replay;
}

FReply UStartWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Replay = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

	return Replay;
}

FReply UStartWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Replay = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	return Replay;
}

FReply UStartWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Replay = Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	return Replay;
}

void UStartWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UStartWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

FReply UStartWidget::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Replay = Super::NativeOnMouseWheel(InGeometry, InMouseEvent);

	return Replay;
}

FReply UStartWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Replay = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

	return Replay;
}

void UStartWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

void UStartWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
}

void UStartWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
}

bool UStartWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Replay = Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	return Replay;
}

bool UStartWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Replay = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	return Replay;
}

void UStartWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}

FReply UStartWidget::NativeOnTouchGesture(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	FReply Replay = Super::NativeOnTouchGesture(InGeometry, InGestureEvent);

	return Replay;
}

FReply UStartWidget::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	FReply Replay = Super::NativeOnTouchStarted(InGeometry, InGestureEvent);

	return Replay;
}

FReply UStartWidget::NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	FReply Replay = Super::NativeOnTouchMoved(InGeometry, InGestureEvent);

	return Replay;
}

FReply UStartWidget::NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	FReply Replay = Super::NativeOnTouchEnded(InGeometry, InGestureEvent);

	return Replay;
}

FReply UStartWidget::NativeOnMotionDetected(const FGeometry& InGeometry, const FMotionEvent& InMotionEvent)
{
	FReply Replay = Super::NativeOnMotionDetected(InGeometry, InMotionEvent);

	return Replay;
}

FReply UStartWidget::NativeOnTouchForceChanged(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent)
{
	FReply Replay = Super::NativeOnTouchForceChanged(MyGeometry, TouchEvent);

	return Replay;
}

void UStartWidget::StartButtonClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("CharacterSelect"));
}

void UStartWidget::StartButtonHovered()
{
	PlayAnimation(StartButtonScaleAnim);
}

void UStartWidget::StartButtonUnHovered()
{
	PlayAnimation(StartButtonScaleAnim, 0.f, 1, EUMGSequencePlayMode::Reverse);
}

void UStartWidget::ExitButtonClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, true);
}

void UStartWidget::ExitButtonHovered()
{
	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();

	for (int32 i = 0; i < WidgetClass->Animations.Num(); i++)
	{
		FString Name = WidgetClass->Animations[i]->GetName();
		
		if (Name == TEXT("ExitButtonScaleAnim_INST"))
		{
			PlayAnimation(WidgetClass->Animations[i]);
			break;
		}
	}
}

void UStartWidget::ExitButtonUnHovered()
{
	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();

	for (int32 i = 0; i < WidgetClass->Animations.Num(); i++)
	{
		FString Name = WidgetClass->Animations[i]->GetName();

		if (Name == TEXT("ExitButtonScaleAnim_INST"))
		{
			PlayAnimation(WidgetClass->Animations[i], 0.f, 1, EUMGSequencePlayMode::Reverse);
			break;
		}
	}
}
