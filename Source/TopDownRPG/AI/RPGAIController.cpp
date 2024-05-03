


#include "RPGAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ARPGAIController::ARPGAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackBoardComponent");
	check(Blackboard);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviourTreeComponent");
	check(BehaviorTreeComponent)

}
