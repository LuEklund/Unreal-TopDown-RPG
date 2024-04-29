


#include "AttributeInfo.h"

FRPGAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag AttributeTag, bool bLogNotFound) const
{
	for (const FRPGAttributeInfo &info : AttributeInformation)
	{
		if (info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag |%s| on AttributeInfo |%s|."), *AttributeTag.ToString(), *GetNameSafe(this));
	}
	return FRPGAttributeInfo();
}
