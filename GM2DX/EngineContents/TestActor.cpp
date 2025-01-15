#include "PreCompile.h"
#include "TestActor.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/Collision.h>
#include "MyCustomRenderer.h"
#include "TestRenderer.h"

ATestActor::ATestActor()
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
	Renderer = CreateDefaultSubObject<TestRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetRelativeScale3D({ 100.0f, 100.0f, 100.0f });
}

ATestActor::~ATestActor()
{
}

void ATestActor::BeginPlay()
{
	AActor::BeginPlay();


}

void ATestActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorRotation({ 0.0f, 0.0f, 200.0f * _DeltaTime });
}