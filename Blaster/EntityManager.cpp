#include "EntityManager.h"

EntityManager::EntityManager() 
{

}

void EntityManager::update()
{
    // TODO: add entities from m_entitesToAdd to the proper location(s)
    //      - add them to the vector of all entites
    //      - add them to the vector inside the map, with the tag as a key

    //remove dead entities from the vector of all entites
    removeDeadEntities(m_entities);

    // remove dead entites from each vector in the entity map
    // C++17 way of iterating through [key, value] pairs in a map
    for (auto& [tag, entityVec] : m_entityMap)
    {
        removeDeadEntities(entityVec);
    }
}

void EntityManager::removeDeadEntities(EntityVec& vec)
{
   // TODO: remove all the dead entities from the input vector
   //       this is called by the update() function 
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{     
    auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

    m_entitiesToAdd.push_back(entity);

    return entity; 
}

const EntityVec& EntityManager::getEntities()
{
    return m_entities;
}

const EntityVec& EntityManager::getEntities(const std::string& tag)
{
    // TODO: this is incorrect, return the correct vector from the map
    return m_entities;
}