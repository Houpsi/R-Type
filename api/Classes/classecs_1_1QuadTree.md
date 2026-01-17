---
title: ecs::QuadTree

---

# ecs::QuadTree






`#include <CollisionSystem.hpp>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[~QuadTree](Classes/classecs_1_1QuadTree.md#function-~quadtree)**() =default |
| void | **[insert](Classes/classecs_1_1QuadTree.md#function-insert)**([EntityRef](Namespaces/namespaceecs.md#using-entityref) entity, const [AABB](Classes/classecs_1_1AABB.md) & bound) |
| std::vector< [EntityRef](Namespaces/namespaceecs.md#using-entityref) > | **[getEntities](Classes/classecs_1_1QuadTree.md#function-getentities)**(const [AABB](Classes/classecs_1_1AABB.md) & bound) const |
| | **[QuadTree](Classes/classecs_1_1QuadTree.md#function-quadtree)**(const [AABB](Classes/classecs_1_1AABB.md) & bound, const int depth =0) |

## Public Functions Documentation

### function ~QuadTree

```cpp
~QuadTree() =default
```


### function insert

```cpp
void insert(
    EntityRef entity,
    const AABB & bound
)
```


### function getEntities

```cpp
std::vector< EntityRef > getEntities(
    const AABB & bound
) const
```


### function QuadTree

```cpp
inline QuadTree(
    const AABB & bound,
    const int depth =0
)
```


-------------------------------

Updated on 2026-01-17 at 16:36:40 +0000