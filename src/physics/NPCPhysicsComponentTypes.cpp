#include "NPCPhysicsComponentTypes.h"
#include "../util/defines.h"

namespace td {

NormNPCPhysicsComponent::NormNPCPhysicsComponent()
    : NPCPhysicsComponent(NPC_NORM_ACCEL, NPC_NORM_DECEL, NPC_NORM_MAX_V) {}

SlowNPCPhysicsComponent::SlowNPCPhysicsComponent()
    : NPCPhysicsComponent(NPC_SLOW_ACCEL, NPC_SLOW_DECEL, NPC_SLOW_MAX_V) {}

ArmNPCPhysicsComponent::ArmNPCPhysicsComponent()
    : NPCPhysicsComponent(NPC_ARM_ACCEL, NPC_ARM_DECEL, NPC_ARM_MAX_V) {}

FastNPCPhysicsComponent::FastNPCPhysicsComponent()
    : NPCPhysicsComponent(NPC_FAST_ACCEL, NPC_FAST_DECEL, NPC_FAST_MAX_V) {}

SwarmNPCPhysicsComponent::SwarmNPCPhysicsComponent()
    : NPCPhysicsComponent(NPC_SWARM_ACCEL, NPC_SWARM_DECEL, NPC_SWARM_MAX_V) {}

FlyNPCPhysicsComponent::FlyNPCPhysicsComponent()
    : NPCPhysicsComponent(NPC_FLY_ACCEL, NPC_FLY_DECEL, NPC_FLY_MAX_V) {}

BossNPCPhysicsComponent::BossNPCPhysicsComponent()
    : NPCPhysicsComponent(NPC_BOSS_ACCEL, NPC_BOSS_DECEL, NPC_BOSS_MAX_V) {}

} /* end namespace td */

