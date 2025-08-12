#pragma once

UENUM(BlueprintType)
enum class EConfirmScreenType : uint8
{
	OK,
	YesNo,
	OkCancel,
	Unknown UMETA(Hidden) //这个只用于C++中，蓝图中隐藏
};

UENUM(BlueprintType)
enum class EConfirmScreenButtonType : uint8
{
	Confirmed,
	Cancelled,
	Close,
	Unknown UMETA(Hidden)
};
