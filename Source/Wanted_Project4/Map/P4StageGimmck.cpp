// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/P4StageGimmck.h"
#include "Kismet/GameplayStatics.h"
#include "Character/P4CharacterBase.h"
#include "Math/Vector.h"
#include "Math/UnrealMathUtility.h"
// Sets default values
AP4StageGimmck::AP4StageGimmck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AP4StageGimmck::BeginPlay()
{
	Super::BeginPlay();
	

	Vx = (TileOffsetCoordB - TileOffsetCoordA);
	Vy = (TileOffsetCoordC - TileOffsetCoordA);

	//Vx.Z = 0.f;
	//Vy.Z = 0.f;

	//플레이어 가져오기.
	//AP4CharacterBase* PlayerCharacter 
	//	= Cast<AP4CharacterBase>(UGameplayStatics::GetPlayerPawn(this,0));
	// 일단 임시로 테스트를 위해 이걸로 설정.
	APawn* PlayerCharacter 
		= Cast<APawn>(UGameplayStatics::GetPlayerPawn(this,0));

	if (PlayerCharacter != nullptr)
	{
		CurrentCenter = WorldToCell(PlayerCharacter->GetActorLocation());
	}

	RefreshTiles();
}

// Called every frame
void AP4StageGimmck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerCharacter
		= Cast<APawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (PlayerCharacter == nullptr)
	{
		return;
	}

	const FIntPoint NewCenter = WorldToCell(PlayerCharacter->GetActorLocation());

	if (NewCenter != CurrentCenter)
	{
		CurrentCenter = NewCenter;
		RefreshTiles();
	}
}

FIntPoint AP4StageGimmck::WorldToCell(const FVector& world) const
{
	const FVector Relative = world - GetActorLocation();

	const FVector2D vx = FVector2D(Vx.X, Vx.Y);
	const FVector2D vy = FVector2D(Vy.X, Vy.Y);
	const FVector2D PlayerXY = FVector2D(Relative.X, Relative.Y);


	const float det = vx.X * vy.Y - vx.Y * vy.X;

	if (FMath::IsNearlyZero(det) == true)
	{
		const float SafeVx = FMath::IsNearlyZero(Vx.X) ? 1.0f : Vx.X;
		const float SafeVy = FMath::IsNearlyZero(Vy.Y) ? 1.0f : Vy.Y;

		int32 i = FMath::FloorToInt(Relative.X / SafeVx);
		int32 j = FMath::FloorToInt(Relative.Y / SafeVy);
		return { i,j };
	}
	
	const float invDet = 1.0f / det;

	const float iFloat = (PlayerXY.X * vy.Y - PlayerXY.Y * vy.X) * invDet;
	const float jFloat = (-PlayerXY.X * vx.Y + PlayerXY.Y * vx.X) * invDet;


	return FIntPoint(FMath::FloorToInt(iFloat), FMath::FloorToInt(jFloat));

}

FVector AP4StageGimmck::CellToWorld(const FIntPoint& cell) const
{
	//셀 기반 맵파츠 A의 위치.
	FVector Pos = GetActorLocation() + (Vx * cell.X) + (Vy * cell.Y);

	//switch (GetCellType(cell))
	//{
	//case ETileType::A:
	//	Pos += TileOffsetCoordA;
	//	break;

	//case ETileType::B:
	//	Pos += TileOffsetCoordB;
	//	break;

	//case ETileType::C:
	//	Pos += TileOffsetCoordC;
	//	break;

	//case ETileType::D:
	//	Pos += TileOffsetCoordD;
	//	break;
	//}

	return Pos;
}

void AP4StageGimmck::RefreshTiles()
{
	TSet<FIntPoint> Wanted;

	for (int32 j = -GridRadiusY; j <= GridRadiusY; ++j)
	{
		for (int32 i = -GridRadiusX; i <= GridRadiusX; ++i)
		{
			const FIntPoint Cell = CurrentCenter + FIntPoint(i, j);
			Wanted.Add(Cell);
			SpawnTileAt(Cell);
		}
	}

	TArray<FIntPoint> Keys;
	ActiveTilesMap.GenerateKeyArray(Keys);

	for (const FIntPoint& K : Keys)
	{
		if (Wanted.Contains(K) == false)
		{
			if (AActor* MapActor = ActiveTilesMap[K].Get())
			{
				MapActor->Destroy();
			}

			ActiveTilesMap.Remove(K);
		}
	}
}

AActor* AP4StageGimmck::SpawnTileAt(const FIntPoint& cell)
{
	if (TWeakObjectPtr<AActor>* Found = ActiveTilesMap.Find(cell))
	{
		if (Found->IsValid() == true)
		{
			return Found->Get();
		}
	}

	TSubclassOf<AActor> Cls = PickTileClass(cell);

	if (Cls == nullptr)
	{
		return nullptr;
	}
	
	const FVector NewLocation = CellToWorld(cell);
	const FRotator NewRotation = FRotator::ZeroRotator;

	FActorSpawnParameters Params;
	Params.Owner = this;

	AActor* SpawnedMapActor = GetWorld()->SpawnActor<AActor>(Cls, NewLocation, NewRotation, Params);

	if (SpawnedMapActor != nullptr)
	{
		ActiveTilesMap.Add(cell, SpawnedMapActor);
	}
	return SpawnedMapActor;	
}

TSubclassOf<AActor> AP4StageGimmck::PickTileClass(const FIntPoint& cell) const
{
	switch (GetCellType(cell))
	{
	case ETileType::A:
		return TileA;

	case ETileType::B:
		return TileB;

	case ETileType::C:
		return TileC;

	case ETileType::D:
		return TileD;

	default:
		return TileD;
	}
}

