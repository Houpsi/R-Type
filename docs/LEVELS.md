# Levels

---
The r-type consists of levels represented by cfg files and interpreted by libconfig. You can create your own level by following this documentation.
There are levels in the Levels folder.

## How add a level

1 - You must create a file named "name_level".cfg, and fill it in according to the level parameters. 

2 - Put it in the Levels folder (at the root of repository)

If your level is not valid, an error will be returned to the console and your level will not be interpreted.
## Parameters level

Here are the types and requirements for creating a level

```
level: {
    id = int, between 1 and 254, unique;  madatory
    name = string;  madatory
    scroll_speed = positif int;  madatory

    waves = (
    {
        time = positif int;  madatory
        enemies = (
            { 
                type = string, see type_enemy;  madatory 
                count = positif int;  madatory
            },
        ); madatory
    } madatory
    );  madatory
    waves_repeat = positif int; madatory

    boss = {
        type = string see type_boss;  madatory
        hp = positif int;  madatory
    }; not madatory
};
```

