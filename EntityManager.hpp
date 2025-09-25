#pragma once

#include "Entity.hpp"
#include <map>
#include <string>

using EntityVec = std::vector<std::shared_ptr<Entity>>;

class EntityManager
{
    EntityVec m_entities;
    EntityVec m_entitiesToAdd;
    std::map<std::string, EntityVec> m_entityMap;
    size_t m_totalEntities = 0;

    void removeDeadEntittes(EntityVec &vec)
    {
        // TODO:remove all the dead entities form the input vector
        //  this is called by the update() function
        std::erase_if(vec,[](auto& e){
            return e->m_active == false;
        });
    }

public:
    EntityManager() = default;

    void update()
    {
        // TOdo: add entities form m_entitesToAdd the proper location(s)
        //  -- add them to the vector of al entities
        m_entities.insert(m_entities.end(), m_entitiesToAdd.begin(), m_entitiesToAdd.end());
        //  -- add them to the vector inside the map, with the tag as a key
        for (auto& add : m_entitiesToAdd)
        {
            m_entityMap[add->m_tag].push_back(add);
        }
        m_entitiesToAdd.clear();
    

        // remove dead entities form the vector of all entities
        removeDeadEntittes(m_entities);
        // remove dead entites form each vector in the  entity map
        // C++20 way of iterating through[key,value ] paris in a map

        for (auto &[tag, entityVec] : m_entityMap)
        {
            removeDeadEntittes(entityVec);
        }
    }
    std::shared_ptr<Entity> addEntity(const std::string &tag)
    {
        // create the entity shared pointer
        auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

        // add it to the vec of all entities
        m_entitiesToAdd.push_back(entity);

        // add it to the entity map
        if (m_entityMap.find(tag) == m_entityMap.end())
        {
            m_entityMap[tag] = EntityVec();
        }
        m_entityMap[tag].push_back(entity);
        return entity;
    }

    const EntityVec& getEntities()
    {
        return m_entities;
    }
    
    const EntityVec& getEntities(const std::string& tag)
    {
        if(m_entityMap.find(tag) == m_entityMap.end()){m_entityMap[tag] = EntityVec();}
        return m_entityMap[tag];
    }
    const std::map<std::string, EntityVec>& getEntityMap(){
        return m_entityMap;
    }
};