// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BehaviorTree/BTAuxiliaryNode.h"
#include "BehaviorTree/BTCompositeNode.h"

UBTAuxiliaryNode::UBTAuxiliaryNode() : UBTNode()
{
	NodeType |= (uint32)BTNodeTypes_AuxiliaryNode;
	NextTickRemainingTime = 0.0f;
	AccumulatedDeltaTime = 0.0f;
	bNotifyBecomeRelevant = false;
	bNotifyCeaseRelevant = false;
	bNotifyTick = false;
	bTickIntervals = false;
	ChildIndex = BTSpecialChild::OwnedByComposite;
}


uint32 UBTAuxiliaryNode::sNodeTypeFlag = (uint32)BTNodeTypes_AuxiliaryNode;

void UBTAuxiliaryNode::WrappedOnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (bNotifyBecomeRelevant)
	{
		const UBTNode* NodeOb = HasInstance() ? GetNodeInstance(OwnerComp, NodeMemory) : this;
		if (NodeOb)
		{
			((UBTAuxiliaryNode*)NodeOb)->OnBecomeRelevant(OwnerComp, NodeMemory);
		}
	}
}

void UBTAuxiliaryNode::WrappedOnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (bNotifyCeaseRelevant)
	{
		const UBTNode* NodeOb = HasInstance() ? GetNodeInstance(OwnerComp, NodeMemory) : this;
		if (NodeOb)
		{
			((UBTAuxiliaryNode*)NodeOb)->OnCeaseRelevant(OwnerComp, NodeMemory);
		}
	}
}

void UBTAuxiliaryNode::WrappedTickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) const
{
	if (bNotifyTick || HasInstance())
	{
		const UBTAuxiliaryNode* NodeOb = HasInstance() ? static_cast<const UBTAuxiliaryNode*>(GetNodeInstance(OwnerComp, NodeMemory)) : this;
		
		//assert(NodeOb);

		if (NodeOb != nullptr && NodeOb->bNotifyTick)
		{
			float UseDeltaTime = DeltaSeconds;

			if (NodeOb->bTickIntervals)
			{
				NextTickRemainingTime -= DeltaSeconds;
				AccumulatedDeltaTime += DeltaSeconds;

				//UE_VLOG("%s::WrappedTickNode NextTickRemainingTime:%.2f\n", mName.c_str(), NextTickRemainingTime);
				if (NextTickRemainingTime > 0.0f)
				{
					return;
				}

				UseDeltaTime = AccumulatedDeltaTime;
				AccumulatedDeltaTime = 0.0f;
			}

			const_cast<UBTAuxiliaryNode*>(NodeOb)->TickNode(OwnerComp, NodeMemory, UseDeltaTime);

		}
	}
}

void UBTAuxiliaryNode::SetNextTickTime(uint8* NodeMemory, float RemainingTime) const
{
	if (bTickIntervals)
	{
		NextTickRemainingTime = RemainingTime;
	}
}

float UBTAuxiliaryNode::GetNextTickRemainingTime(uint8* NodeMemory) const
{
	if (bTickIntervals)
	{
		return FMath::Max(0.0f, NextTickRemainingTime);
	}

	return 0.0f;
}
// 
// void UBTAuxiliaryNode::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, std::vector<FString>& Values) const
// {
// 	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);
// 
// 	if (Verbosity == EBTDescriptionVerbosity::Detailed && bTickIntervals)
// 	{
// 		FBTAuxiliaryMemory* AuxMemory = GetSpecialNodeMemory<FBTAuxiliaryMemory>(NodeMemory);
// 		Values.Add(FString::Printf(TEXT("next tick: %ss"), *FString::SanitizeFloat(AuxMemory->NextTickRemainingTime)));
// 	}
// }

void UBTAuxiliaryNode::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// empty in base class
}

void UBTAuxiliaryNode::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// empty in base class
}

void UBTAuxiliaryNode::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// empty in base class
}

// uint16 UBTAuxiliaryNode::GetSpecialMemorySize() const
// {
// 	return bTickIntervals ? sizeof(FBTAuxiliaryMemory) : Super::GetSpecialMemorySize();
// }

void UBTAuxiliaryNode::InitializeParentLink(uint8 MyChildIndex)
{
	ChildIndex = MyChildIndex;
}

const UBTNode* UBTAuxiliaryNode::GetMyNode() const
{
	return (ChildIndex == BTSpecialChild::OwnedByComposite) ? GetParentNode() : (GetParentNode() ? GetParentNode()->GetChildNode(ChildIndex) : nullptr);
}

//----------------------------------------------------------------------//
// DEPRECATED
//----------------------------------------------------------------------//
