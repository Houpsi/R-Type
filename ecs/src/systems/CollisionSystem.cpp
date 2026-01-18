/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"
#include "components/Sound.hpp"

namespace ecs
{
    void CollisionSystem::_buildQuadTree(const std::vector<std::shared_ptr<Entity>> &entities)
    {
        _quadTree = std::make_unique<QuadTree>(AABB{0, 0, ecs::windowWidth, ecs::windowHeight});
        for (const auto &entity : entities) {
            auto collision = entity->getComponent<Collision>();
            auto position = entity->getComponent<Position>();

            if (!collision || !position) {
                continue;
            };

            AABB bound = {position->getX(), position->getY(), collision->getWidth(), collision->getHeight()};
            _quadTree->insert(entity, bound);
        }
    }

    /**
    * Check if the entity can have a collision, and is there is one
    * check if there is a collision with another entity
    * @param ecs
     */
    void CollisionSystem::update(EcsManager &ecs)
    {
        const auto &entities = ecs.getEntities();
        _buildQuadTree(entities);

        for (const auto &entity : entities) {
            auto collision = entity->getComponent<Collision>();
            auto position = entity->getComponent<Position>();

            if (!collision || !position) continue;

            AABB bound{
                position->getX(),
                position->getY(),
                collision->getWidth(),
                collision->getHeight()
            };
            auto closeEntities = _quadTree->getEntities(bound);

            for (const auto& other : closeEntities) {
                auto otherCollision = other->getComponent<Collision>();

                if (!otherCollision) continue;
                if (entity == other)
                    continue;
                if (_shouldIgnoreCollision(
                    collision->getTypeCollision(),
                    otherCollision->getTypeCollision()))
                    continue;
                if (_checkCollision(ecs, *entity, *other)) {
                    const auto typeA = collision->getTypeCollision();
                    const auto typeB = otherCollision->getTypeCollision();

                    if (typeA == PLAYER_PROJECTILE &&
                        typeB == ENEMY) {
                        auto health = other->getComponent<Health>();
                        auto shoot = entity->getComponent<Shoot>();

                        if (!health || !shoot) continue;
                        health->setHealth(health->getHealth() - shoot->getDamage());
                        entity->addComponent<Sound>(3, false);
                        entity->addComponent<Destroy>();
                    }
                    else if (typeA == PLAYER &&
                        typeB == ENEMY) {
                        entity->addComponent<Sound>(idExplosionMusic, false);
                        entity->addComponent<Destroy>();
                    }
                    else if (typeA == ENEMY_PROJECTILE &&
                        typeB == PLAYER) {
                        entity->addComponent<Sound>(idExplosionMusic, false);
                        entity->addComponent<Destroy>();
                        other->addComponent<Destroy>();
                    } else if (typeA == PLAYER &&
                        typeB == POWER_UP) {
                        entity->addComponent<Sound>(idPowerUpMusic, false);
                        auto shoot = entity->getComponent<Shoot>();
                        if (shoot) {
                            shoot->setActiveShootingType(shoot->getRandomShootingType());
                        }
                        other->addComponent<Destroy>();
                    }
                }
            }
        }
    }

    bool CollisionSystem::_shouldIgnoreCollision(const TypeCollision a, const TypeCollision b)
    {
        if (a == TypeCollision::PLAYER && b == TypeCollision::PLAYER)
            return true;
        if (a == TypeCollision::ENEMY && b == TypeCollision::OBSTACLE)
            return true;
        if (a == TypeCollision::PLAYER && b == TypeCollision::PLAYER_PROJECTILE)
            return true;
        if (a == TypeCollision::PLAYER_PROJECTILE && b == TypeCollision::PLAYER)
            return true;
        if (a == TypeCollision::ENEMY && b == TypeCollision::ENEMY_PROJECTILE)
            return true;
        if (a == TypeCollision::ENEMY && b == TypeCollision::ENEMY)
            return true;
        if (a == TypeCollision::ENEMY && b == TypeCollision::PLAYER_PROJECTILE)
            return true;
        if (a == TypeCollision::ENEMY && b == TypeCollision::PLAYER)
            return true;
        if (a == ENEMY_PROJECTILE && b == ENEMY)
            return true;
        if ((a == TypeCollision::PLAYER_PROJECTILE || a == ENEMY_PROJECTILE) && b == TypeCollision::POWER_UP)
            return true;
        if (a == TypeCollision::POWER_UP && (b == TypeCollision::PLAYER_PROJECTILE || b == ENEMY_PROJECTILE))
            return true;
        return false;
    }

    bool CollisionSystem::_isColliding(
        float x1, float y1, float w1, float h1,
        float x2, float y2, float w2, float h2)
    {
        return x1 < x2 + w2 &&
               x1 + w1 > x2 &&
               y1 < y2 + h2 &&
               y1 + h1 > y2;
    }

    bool CollisionSystem::_checkCollision(EcsManager& ecs, Entity a, Entity b)
    {
        const auto& posA = a.getComponent<Position>();
        const auto& colA = a.getComponent<Collision>();

        const auto& posB = b.getComponent<Position>();
        const auto& colB = b.getComponent<Collision>();

        if (!posA || !colA || !posB || !colB) return false;

        return _isColliding(
            posA->getX(), posA->getY(), colA->getWidth(), colA->getHeight(),
            posB->getX(), posB->getY(), colB->getWidth(), colB->getHeight()
        );
    }

    void QuadTree::insert(EntityRef entity, const AABB& bound)
    {
        if (!_bound.intersects(bound)) {
            return;
        }
        if (_entities.size() < ecs::MAX_ENTITIES || _depth >= ecs::MAX_DEPTH) {
            _entities.push_back({entity, bound});
            return;
        }
        if (!_northWest) {
            _subdivide();
        }

        if (_northWest->_bound.contains(bound)) _northWest->insert(entity, bound);
        else if (_northEast->_bound.contains(bound)) _northEast->insert(entity, bound);
        else if (_southWest->_bound.contains(bound)) _southWest->insert(entity, bound);
        else if (_southEast->_bound.contains(bound)) _southEast->insert(entity, bound);
        else _entities.push_back({entity, bound});
    }

    std::vector<EntityRef> QuadTree::getEntities(const AABB& bound) const
    {
        std::vector<EntityRef> targetEntity;

        if (!_bound.intersects(bound)) {
            return targetEntity;
        }
        for (auto& p : _entities)
            if (p.second.intersects(bound))
                targetEntity.push_back(p.first);

        if (_northWest) {
            auto nw = _northWest->getEntities(bound);
            targetEntity.insert(targetEntity.end(), nw.begin(), nw.end());
        }
        if (_northEast) {
            auto ne = _northEast->getEntities(bound);
            targetEntity.insert(targetEntity.end(), ne.begin(), ne.end());
        }
        if (_southWest) {
            auto sw = _southWest->getEntities(bound);
            targetEntity.insert(targetEntity.end(), sw.begin(), sw.end());
        }
        if (_southEast) {
            auto se = _southEast->getEntities(bound);
            targetEntity.insert(targetEntity.end(), se.begin(), se.end());
        }
        return targetEntity;
    }

    void QuadTree::_subdivide()
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