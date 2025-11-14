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

	Vx.Z = 0.0f;
	Vy.Z = 0.0f;


	BaseAB = Vx;        // 헤더에 FVector BaseAB, BaseAC 추가
	BaseAC = Vy;

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

	//DCorrection = TileOffsetCoordD - (TileOffsetCoordB + TileOffsetCoordC - TileOffsetCoordA);

	const FVector AB = TileOffsetCoordB - TileOffsetCoordA;
	const FVector AC = TileOffsetCoordC - TileOffsetCoordA;
	UE_LOG(LogTemp, Warning, TEXT("AB=%s | |AB|=%f"), *AB.ToString(), AB.Size());
	UE_LOG(LogTemp, Warning, TEXT("AC=%s | |AC|=%f"), *AC.ToString(), AC.Size());

	const FVector P00 = CellToWorld({ 0,0 });
	const FVector P10 = CellToWorld({ 1,0 });
	const FVector P01 = CellToWorld({ 0,1 });
	UE_LOG(LogTemp, Warning, TEXT("A(0,0)=%s  B(1,0)=%s  C(0,1)=%s"),
		*P00.ToString(), *P10.ToString(), *P01.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Actual A->B dist=%f  A->C dist=%f"),
		(P10 - P00).Size(), (P01 - P00).Size());
	UE_LOG(LogTemp, Warning, TEXT("Check Vx=%s  Vy=%s | |Vx|=%f |Vy|=%f"), *Vx.ToString(), *Vy.ToString(), Vx.Size(), Vy.Size());
	UE_LOG(LogTemp, Warning, TEXT("TileC=%s  TileD=%s"), *TileOffsetCoordC.ToString(), *TileOffsetCoordD.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Vx=%s Vy=%s"), *Vx.ToString(), *Vy.ToString());
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
	// 2x2 슈퍼셀 간 이동 벡터
	const FVector Ux = BaseAB * 2.0f; // A->B 두 칸
	const FVector Uy = BaseAC * 2.0f; // A->C 두 칸

	// 음수 셀도 안정적으로 동작하게 모듈러 정규화
	auto Parity = [](int32 v) { return (v % 2 + 2) % 2; };
	const int32 px = Parity(cell.X); // 0 또는 1
	const int32 py = Parity(cell.Y); // 0 또는 1

	// 이 셀의 슈퍼셀 좌표 (짝수/홀수 성분 제거 후 2로 나눔)
	const int32 sx = FMath::FloorToInt((cell.X - px) / 2.0f);
	const int32 sy = FMath::FloorToInt((cell.Y - py) / 2.0f);

	// 슈퍼셀 기준점
	FVector Pos = GetActorLocation() + Ux * sx + Uy * sy;

	// 슈퍼셀 내부에서 A/B/C/D 오프셋을 한 번만 적용
	switch (GetCellType(cell))
	{
	case ETileType::A: Pos += (TileOffsetCoordA - TileOffsetCoordA); break; // 0
	case ETileType::B: Pos += (TileOffsetCoordB - TileOffsetCoordA); break;
	case ETileType::C: Pos += (TileOffsetCoordC - TileOffsetCoordA); break;
	case ETileType::D: Pos += (TileOffsetCoordD - TileOffsetCoordA); break;
	}

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

