// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop.h"
#include "StarChaserGameMode.h"


bool UShop::Initialize()
{
	if (!Super::Initialize()) return false;
	if (!BuyMagnet || !BuyBoots) return false;

	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());

	BuyMagnet->OnClicked.AddDynamic(this, &UShop::UpgradeMagnet);
	BuyBoots->OnClicked.AddDynamic(this, &UShop::UpgradeBoots);
	Skin->OnClicked.AddDynamic(this, &UShop::UpgradeSkin);
	if (GameMode)
	{
		if (GameMode->MagnetUpgradeLevel == 1)
		{
			MagnetPrice->SetText(FText::FromString("Cost: 75 Stars"));
		}
		else if(GameMode->MagnetUpgradeLevel == 2)
		{
			MagnetPrice->SetText(FText::FromString("Cost: 200 Stars"));
		}
		else if (GameMode->MagnetUpgradeLevel == 3)
		{
			MagnetPrice->SetText(FText::FromString("MAX"));
		}
		else
		{
			MagnetPrice->SetText(FText::FromString("MAX"));
		}

		if (GameMode->BootsUpgradeLevel == 1)
		{
			BootsPrice->SetText(FText::FromString("Cost: 50 Stars"));
		}
		else if (GameMode->BootsUpgradeLevel == 2)
		{
			BootsPrice->SetText(FText::FromString("Cost: 150 Stars"));
		}
		else if (GameMode->BootsUpgradeLevel == 3)
		{
			BootsPrice->SetText(FText::FromString("MAX"));
		}
		else
		{
			BootsPrice->SetText(FText::FromString("MAX"));
		}

		if (GameMode->bNovaSkin) SkinPriceText->SetText(FText::FromString("Purchased!"));

	}
	return true;
}

void UShop::UpgradeMagnet()
{
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode->MagnetUpgradeLevel == 1 && GameMode->TotalStars > 74)
	{
		GameMode->MagnetCooldown = 12.f;
		GameMode->MagnetUpgradeLevel = 2;
		GameMode->TotalStars += -75;
		MagnetPrice->SetText(FText::FromString("Cost: 200 Stars"));
		GameMode->Save();
		return;
	}
	if (GameMode->MagnetUpgradeLevel == 2 && GameMode->TotalStars > 199)
	{
		GameMode->MagnetCooldown = 20.f;
		GameMode->MagnetUpgradeLevel = 3;
		GameMode->TotalStars += -200;
		MagnetPrice->SetText(FText::FromString("MAX"));
		GameMode->Save();
		return;
	}
}

void UShop::UpgradeBoots()
{
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode->BootsUpgradeLevel == 1 && GameMode->TotalStars > 49)
	{
		GameMode->BootsCooldown = 12.f;
		GameMode->BootsUpgradeLevel = 2;
		GameMode->TotalStars += -50;
		BootsPrice->SetText(FText::FromString("Cost: 150 Stars"));
		GameMode->Save();
		return;
	}
	if (GameMode->BootsUpgradeLevel == 2 && GameMode->TotalStars > 149)
	{
		GameMode->BootsCooldown = 20.f;
		GameMode->BootsUpgradeLevel = 3;
		GameMode->TotalStars += -150;
		BootsPrice->SetText(FText::FromString("MAX"));
		GameMode->Save();
		return;
	}
}

void UShop::UpgradeSkin()
{
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode && !GameMode->bNovaSkin && GameMode->TotalStars > 199)
	{
		GameMode->bNovaSkin = true;
		GameMode->TotalStars += -200;
		SkinPriceText->SetText(FText::FromString("Purchased!"));
		GameMode->Save();
	}
}
