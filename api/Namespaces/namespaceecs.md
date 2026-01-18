---
title: ecs

---

# ecs



## Namespaces

| Name           |
| -------------- |
| **[ecs::dir](Namespaces/namespaceecs_1_1dir.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[ecs::VelocitySystem](Classes/classecs_1_1VelocitySystem.md)**  |
| class | **[ecs::Velocity](Classes/classecs_1_1Velocity.md)**  |
| class | **[ecs::Text](Classes/classecs_1_1Text.md)**  |
| class | **[ecs::System](Classes/classecs_1_1System.md)**  |
| class | **[ecs::SpriteAnimationSystem](Classes/classecs_1_1SpriteAnimationSystem.md)**  |
| class | **[ecs::Sprite](Classes/classecs_1_1Sprite.md)**  |
| class | **[ecs::SoundSystem](Classes/classecs_1_1SoundSystem.md)**  |
| class | **[ecs::SoundManager](Classes/classecs_1_1SoundManager.md)**  |
| class | **[ecs::Sound](Classes/classecs_1_1Sound.md)**  |
| class | **[ecs::Shoot](Classes/classecs_1_1Shoot.md)**  |
| class | **[ecs::ScoreTextSystem](Classes/classecs_1_1ScoreTextSystem.md)**  |
| class | **[ecs::Score](Classes/classecs_1_1Score.md)**  |
| class | **[ecs::ResourceManager](Classes/classecs_1_1ResourceManager.md)**  |
| class | **[ecs::RenderSystem](Classes/classecs_1_1RenderSystem.md)**  |
| class | **[ecs::QuadTree](Classes/classecs_1_1QuadTree.md)**  |
| class | **[ecs::Position](Classes/classecs_1_1Position.md)**  |
| class | **[ecs::PlayerAnimationSystem](Classes/classecs_1_1PlayerAnimationSystem.md)**  |
| class | **[ecs::PlayerAnimation](Classes/classecs_1_1PlayerAnimation.md)**  |
| class | **[ecs::MovementSystem](Classes/classecs_1_1MovementSystem.md)**  |
| class | **[ecs::InputSystem](Classes/classecs_1_1InputSystem.md)**  |
| class | **[ecs::InputPlayer](Classes/classecs_1_1InputPlayer.md)**  |
| class | **[ecs::HealthSystem](Classes/classecs_1_1HealthSystem.md)**  |
| class | **[ecs::Health](Classes/classecs_1_1Health.md)**  |
| class | **[ecs::Entity](Classes/classecs_1_1Entity.md)**  |
| class | **[ecs::Enemy](Classes/classecs_1_1Enemy.md)**  |
| class | **[ecs::EcsManager](Classes/classecs_1_1EcsManager.md)**  |
| class | **[ecs::DummySystem](Classes/classecs_1_1DummySystem.md)**  |
| class | **[ecs::DummyComponent](Classes/classecs_1_1DummyComponent.md)**  |
| class | **[ecs::DestroySystem](Classes/classecs_1_1DestroySystem.md)**  |
| class | **[ecs::Destroy](Classes/classecs_1_1Destroy.md)**  |
| class | **[ecs::Component](Classes/classecs_1_1Component.md)**  |
| class | **[ecs::CollisionSystem](Classes/classecs_1_1CollisionSystem.md)**  |
| class | **[ecs::Collision](Classes/classecs_1_1Collision.md)**  |
| class | **[ecs::BackgroundSystem](Classes/classecs_1_1BackgroundSystem.md)** <br>[System](Classes/classecs_1_1System.md) responsible for the infinite scrolling logic of the background.  |
| class | **[ecs::Background](Classes/classecs_1_1Background.md)** <br>A component handling background logic, specifically for scrolling/looping effects.  |
| class | **[ecs::Animation](Classes/classecs_1_1Animation.md)**  |
| class | **[ecs::AABB](Classes/classecs_1_1AABB.md)**  |

## Types

|                | Name           |
| -------------- | -------------- |
| enum| **[TypeCollision](Namespaces/namespaceecs.md#enum-typecollision)** { POWER_UP, PLAYER_PROJECTILE, PLAYER, OBSTACLE, ENEMY_PROJECTILE, ENEMY} |
| using std::shared_ptr< [Entity](Classes/classecs_1_1Entity.md) > | **[EntityRef](Namespaces/namespaceecs.md#using-entityref)**  |
| enum class uint8_t | **[AccessibilityFilter](Namespaces/namespaceecs.md#enum-accessibilityfilter)** { Protanopia, None = 0, Invert, HighContrast} |

## Functions

|                | Name           |
| -------------- | -------------- |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , CreateEntityIncreasesSize ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , DeltaTimeSetAndGetWorks ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , AddSystemStoresSystem ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , UpdateSystemsCallsUpdate ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , GetEntitiesWithComponentWorks ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , GetHealth ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , SetHealth ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , SetNegHealth ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , GetPosition ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , SetPosition ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(SpriteTest , GetSpriteReturnsReference ) |

## Attributes

|                | Name           |
| -------------- | -------------- |
| constexpr uint16_t | **[windowWidth](Namespaces/namespaceecs.md#variable-windowwidth)**  |
| constexpr uint16_t | **[windowHeight](Namespaces/namespaceecs.md#variable-windowheight)**  |
| constexpr int | **[volumeMusic](Namespaces/namespaceecs.md#variable-volumemusic)**  |
| constexpr int | **[scoreKillMonster](Namespaces/namespaceecs.md#variable-scorekillmonster)**  |
| const std::string | **[protanopiaShader](Namespaces/namespaceecs.md#variable-protanopiashader)**  |
| const std::string | **[invertShader](Namespaces/namespaceecs.md#variable-invertshader)**  |
| constexpr std::array< std::string_view, 5 > | **[idToSound](Namespaces/namespaceecs.md#variable-idtosound)**  |
| constexpr int | **[idPowerUpMusic](Namespaces/namespaceecs.md#variable-idpowerupmusic)**  |
| constexpr int | **[idExplosionMusic](Namespaces/namespaceecs.md#variable-idexplosionmusic)**  |
| const std::string | **[highContrastShader](Namespaces/namespaceecs.md#variable-highcontrastshader)**  |
| constexpr std::string_view | **[folderSound](Namespaces/namespaceecs.md#variable-foldersound)**  |
| constexpr int | **[MAX_ENTITIES](Namespaces/namespaceecs.md#variable-max-entities)**  |
| constexpr int | **[MAX_DEPTH](Namespaces/namespaceecs.md#variable-max-depth)**  |

## Types Documentation

### enum TypeCollision

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| POWER_UP | |   |
| PLAYER_PROJECTILE | |   |
| PLAYER | |   |
| OBSTACLE | |   |
| ENEMY_PROJECTILE | |   |
| ENEMY | |   |




### using EntityRef

```cpp
using ecs::EntityRef = typedef std::shared_ptr<Entity>;
```


### enum AccessibilityFilter

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| Protanopia | |   |
| None | 0|   |
| Invert | |   |
| HighContrast | |   |





## Functions Documentation

### function TEST

```cpp
TEST(
    EcsManagerTest ,
    CreateEntityIncreasesSize 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    DeltaTimeSetAndGetWorks 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    AddSystemStoresSystem 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    UpdateSystemsCallsUpdate 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    GetEntitiesWithComponentWorks 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    GetHealth 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    SetHealth 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    SetNegHealth 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    GetPosition 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    SetPosition 
)
```


### function TEST

```cpp
TEST(
    SpriteTest ,
    GetSpriteReturnsReference 
)
```



## Attributes Documentation

### variable windowWidth

```cpp
constexpr uint16_t windowWidth = 1920;
```


### variable windowHeight

```cpp
constexpr uint16_t windowHeight = 1080;
```


### variable volumeMusic

```cpp
constexpr int volumeMusic = 100;
```


### variable scoreKillMonster

```cpp
static constexpr int scoreKillMonster = 100;
```


### variable protanopiaShader

```cpp
const std::string protanopiaShader = R"(
    uniform sampler2D texture;
    void main() {
        vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
        mat3 matrix = mat3(
            0.567, 0.433, 0.0,
            0.558, 0.442, 0.0,
            0.0,   0.242, 0.758
        );
        vec3 color = pixel.rgb * matrix;
        gl_FragColor = vec4(color, pixel.a);
    }
)";
```


### variable invertShader

```cpp
const std::string invertShader = R"(
    uniform sampler2D texture;
    void main() {
        vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
        gl_FragColor = vec4(1.0 - pixel.r, 1.0 - pixel.g, 1.0 - pixel.b, pixel.a);
    }
    )";
```


### variable idToSound

```cpp
constexpr std::array< std::string_view, 5 > idToSound = {"shoot", "theme", "explosion", "boss1", "power_up"};
```


### variable idPowerUpMusic

```cpp
constexpr int idPowerUpMusic = 5;
```


### variable idExplosionMusic

```cpp
constexpr int idExplosionMusic = 3;
```


### variable highContrastShader

```cpp
const std::string highContrastShader = R"(
    uniform sampler2D texture;
    void main() {
        vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
        float gray = dot(pixel.rgb, vec3(0.299, 0.587, 0.114));
        float contrast = step(0.4, gray);
        gl_FragColor = vec4(contrast, contrast, contrast, pixel.a);
    }
    )";
```


### variable folderSound

```cpp
constexpr std::string_view folderSound = "./assets/sound/";
```


### variable MAX_ENTITIES

```cpp
static constexpr int MAX_ENTITIES = 6;
```


### variable MAX_DEPTH

```cpp
static constexpr int MAX_DEPTH = 6;
```





-------------------------------

Updated on 2026-01-18 at 20:39:22 +0000