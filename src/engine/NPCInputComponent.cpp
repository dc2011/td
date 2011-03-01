#include "NPCInputComponent.h"
#include "NPC.h"

NPCInputComponent::NPCInputComponent() {}

NPCInputComponent::~NPCInputComponent() { }

void NPCInputComponent::update() {
    
}

void NPCInputComponent::setParent(Unit *parent) {
    // Casting Unit* to NPC*.
    parent_ = (NPC*) parent;
}

