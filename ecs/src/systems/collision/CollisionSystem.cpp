/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** CollisionSystem
*/
#include "CollisionSystem.hpp"

namespace ecs
{
    void CollisionSystem::buildQuadTree(EcsManager &ecs)
    {
        for (const auto &entity : _entity) {
            auto collision = ecs.getComponentManager().getComponent<Collision>(entity);
            auto position = ecs.getComponentManager().getComponent<Position>(entity);
            AABB bound = {position.getX(), position.getY(), collision.getWidth(), collision.getWidth()};
            _quadTree.insert(entity, bound);
        }
    }

    /**
    * Check if the entity can have a collision, and is there is one
    * check if there is a collision with another entity
    * @param ecs
     */
    void CollisionSystem::update(EcsManager &ecs)
    {
        // QuadTree tree(AABB{0,0,16,16});
        buildQuadTree(ecs);

         for (const auto &entity : _entity)
         {
             auto collision = ecs.getComponentManager().getComponent<Collision>(entity);
             auto position = ecs.getComponentManager().getComponent<Position>(entity);
             const AABB& bound = {position.getX(), position.getY(), collision.getWidth(), collision.getWidth()};
             auto closeEntities = _quadTree.getEntities(bound);

             for (const auto &other : closeEntities) {
                 auto otherCollision= ecs.getComponentManager().getComponent<Collision>(other);

                 if (entity == other)
                     continue;
                 if (checkCollision(ecs, entity, other)) {
                     const auto typeA = collision.getTypeCollision();
                     const auto typeB = otherCollision.getTypeCollision();

                     if (typeA == PLAYER_PROJECTILE &&
                         typeB == ENEMY) {
                         auto health = ecs.getComponentManager().getComponent<Health>(other);
                         auto shoot  = ecs.getComponentManager().getComponent<Shoot>(entity);

                         health.setHealth(health.getHealth() - shoot.getDamage());
                         ecs.getComponentManager().addComponent(entity, Destroy());
                     }
                     else if (typeA == PLAYER &&
                         typeB == ENEMY) {

                         ecs.getComponentManager().addComponent(entity, Destroy());
                     }
                 }
             }
         }
        // const auto &entities = ecs.getEntities();

        // for (const auto &entity : _entity) {
        //     auto collision = ecs.getComponentManager().getComponent<Collision>(entity);
        //     auto position = ecs.getComponentManager().getComponent<Position>(entity);
        //     // entity->getComponent<Collision>();
        //     // auto position  = entity->getComponent<Position>();
        //
        //     // if (!collision || !position)
        //     //     continue;
        //
        //     const float x = position.getX();
        //     const float y = position.getY();
        //     const float width  = collision.getWidth();
        //     const float height = collision.getHeight();
        //
        //     for (const auto &other : _entity) {
        //         if (entity == other)
        //             continue;
        //
        //         auto otherCollision = ecs.getComponentManager().getComponent<Collision>(entity);
        //         auto otherPosition = ecs.getComponentManager().getComponent<Position>(entity);
        //         // auto otherCollision = other->getComponent<Collision>();
        //         // auto otherPosition  = other->getComponent<Position>();
        //
        //         // if (!otherCollision || !otherPosition)
        //         //     continue;
        //
        //         if (shouldIgnoreCollision(
        //                 collision.getTypeCollision(),
        //                 otherCollision.getTypeCollision()))
        //             continue;
        //
        //         const float ox = otherPosition.getX();
        //         const float oy = otherPosition.getY();
        //         const float oWidth  = otherCollision.getWidth();
        //         const float oHeight = otherCollision.getHeight();
        //
        //         if (!isColliding(x, y, width, height, ox, oy, oWidth, oHeight))
        //             continue;
        //
        //         collision.setIsTrigger(true);
        //         otherCollision.setIsTrigger(true);
        //
        //         const auto typeA = collision.getTypeCollision();
        //         const auto typeB = otherCollision.getTypeCollision();
        //
        //         if (typeA == TypeCollision::PLAYER_PROJECTILE &&
        //             typeB == TypeCollision::ENEMY) {
        //
        //             auto health = ecs.getComponentManager().getComponent<Health>(other);
        //             auto shoot  = ecs.getComponentManager().getComponent<Shoot>(entity);
        //
        //             health.setHealth(health.getHealth() - shoot.getDamage());
        //
        //             ecs.getComponentManager().addComponent(entity, Destroy());
        //         }
        //
        //         if (typeA == TypeCollision::PLAYER &&
        //             typeB == TypeCollision::ENEMY) {
        //
        //             ecs.getComponentManager().addComponent(entity, Destroy());
        //         }
        //     }
        // }
    }

    // bool CollisionSystem::shouldIgnoreCollision(const TypeCollision a, const TypeCollision b)
    // {
    //     if (a == TypeCollision::PLAYER && b == TypeCollision::PLAYER)
    //         return true;
    //     if (a == TypeCollision::ENEMY && b == TypeCollision::OBSTACLE)
    //         return true;
    //     if (a == TypeCollision::PLAYER && b == TypeCollision::PLAYER_PROJECTILE)
    //         return true;
    //     if (a == TypeCollision::PLAYER_PROJECTILE && b == TypeCollision::PLAYER)
    //         return true;
    //     if (a == TypeCollision::ENEMY && b == TypeCollision::ENEMY_PROJECTILE)
    //         return true;
    //     if (a == TypeCollision::ENEMY && b == TypeCollision::ENEMY)
    //         return true;
    //     if (a == TypeCollision::ENEMY && b == TypeCollision::PLAYER_PROJECTILE)
    //         return true;
    //     if (a == TypeCollision::ENEMY && b == TypeCollision::PLAYER)
    //         return true;
    //
    //     return false;
    // }
    //
    bool CollisionSystem::isColliding(
        float x1, float y1, float w1, float h1,
        float x2, float y2, float w2, float h2)
    {
        return x1 < x2 + w2 &&
               x1 + w1 > x2 &&
               y1 < y2 + h2 &&
               y1 + h1 > y2;
    }

    bool CollisionSystem::checkCollision(EcsManager& ecs, Entity a, Entity b)
    {
        const auto& posA = ecs.getComponentManager().getComponent<Position>(a);
        const auto& colA = ecs.getComponentManager().getComponent<Collision>(a);

        const auto& posB = ecs.getComponentManager().getComponent<Position>(b);
        const auto& colB = ecs.getComponentManager().getComponent<Collision>(b);

        // if (shouldIgnoreCollision(colA..getType(), colB.getType()))
            // return false;

        return isColliding(
            posA.getX(), posA.getY(), colA.getWidth(), colA.getHeight(),
            posB.getX(), posB.getY(), colB.getWidth(), colB.getHeight()
        );
    }


    void QuadTree::insert(Entity entity, AABB& bound)
    {
        if (!_bound.intersects(bound)) {
            return;
        }
        if (_entities.size() < MAX_ENTITIES || _depth >= MAX_DEPTH) {
            _entities.push_back({entity, bound});
            return;
        }
        if (!_northWest) {
            subdivide();
        }

        if (_northWest->_bound.contains(bound)) _northWest->insert(entity, bound);
        else if (_northEast->_bound.contains(bound)) _northEast->insert(entity, bound);
        else if (_southWest->_bound.contains(bound)) _southWest->insert(entity, bound);
        else if (_southEast->_bound.contains(bound)) _southEast->insert(entity, bound);
    }

    std::vector<Entity> QuadTree::getEntities(const AABB& bound) const
    {
        std::vector<Entity> targetEntity;

        if (!_bound.intersects(bound)) {
            return targetEntity;
        }
        for (auto& p : _entities)
            if (p.second.intersects(bound))
                targetEntity.push_back(p.first);

        // targetEntity.appendArray(_northWest->queryRange(bound));
        // targetEntity.appendArray(_northEast->queryRange(bound));
        // targetEntity.appendArray(_southWest->queryRange(bound));
        // targetEntity.appendArray(_southEast->queryRange(bound));
        return targetEntity;
    }

    void QuadTree::subdivide()
    {
        float hx = _bound.width / 2;
        float hy = _bound.height / 2;
        float x = _bound.x;
        float y = _bound.y;

        _northWest = std::make_unique<QuadTree>(AABB{x, y, hx, hy}, _depth + 1);
        _northEast = std::make_unique<QuadTree>(AABB{x + hx, y, hx, hy}, _depth + 1);
        _southWest = std::make_unique<QuadTree>(AABB{x, y + hy, hx, hy}, _depth + 1);
        _southEast = std::make_unique<QuadTree>(AABB{x + hx, y + hy, hx, hy}, _depth + 1);
    }
}
