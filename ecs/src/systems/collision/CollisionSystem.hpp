/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** CollisionSystem
*/

#ifndef BOOTSTRAP_COLLISIONSYSTEM_HPP
    #define BOOTSTRAP_COLLISIONSYSTEM_HPP
#include "components/collision/Collision.hpp"
#include "components/position/Position.hpp"
#include "components/sprite/Sprite.hpp"
#include "managers/EcsManager.hpp"
#include "systems/system/ASystem.hpp"
#include "components/destroy/Destroy.hpp"

namespace ecs {
    struct AABB {
        float x, y;
        float width, height;

        bool intersects(const AABB& other) const {
            return !(x + width < other.x || other.x + other.width < x ||
                y + height < other.y || other.y + other.height < y);
        }
        bool contains(const AABB& other) const {
            return other.x >= x && other.x + other.width <= x + width &&
                other.y >= y && other.y + other.height <= y + height;
        }
    };

    class QuadTree {
    public:
        QuadTree(const AABB& bound, const int depth = 0): _bound(bound), _depth(depth) {};
        ~QuadTree() = default;

        void insert(Entity entity, AABB &bound);
        std::vector<Entity> getEntities(const AABB&) const;

    private:
        void subdivide();

        static constexpr int MAX_ENTITIES = 6;
        static constexpr int MAX_DEPTH = 6;

        AABB _bound;
        int _depth;

        std::vector<std::pair<Entity, AABB>> _entities;

        std::unique_ptr<QuadTree> _northWest;
        std::unique_ptr<QuadTree> _northEast;
        std::unique_ptr<QuadTree> _southWest;
        std::unique_ptr<QuadTree> _southEast;
    };

    class CollisionSystem: public ASystem {
      public:
        explicit CollisionSystem();
        void update(EcsManager &ecs) override;

    private:
        // static bool shouldIgnoreCollision(TypeCollision a, TypeCollision b);
        static bool isColliding( float x1, float y1, float w1, float h1,
            float x2, float y2, float w2, float h2);
        void buildQuadTree(EcsManager &ecs);
        // void detectCollisions();
        static bool checkCollision(EcsManager& ecs, Entity a, Entity b);

        QuadTree _quadTree;
    };
}

#endif //BOOTSTRAP_COLLISIONSYSTEM_HPP