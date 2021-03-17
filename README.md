# ENGG 1340

## Team Member

**Zhao Yazhou** 3035772638 

**Li Zicheng** 3035772157

## game_description

"Long long ago, there was a man, flawed and having his back to the wall. The only thing in his bag was a claw and a string. Fortunately, he found a mystery place. Instead of several stones, gold, diamond and something unknown was under the ground."

GOLD MINE is a game for one player. Players will control miniature miners who traverse the mine collecting gold. Players will face several rounds one by one. Each round, players will get 60 seconds to mine and make money. Only when they achieve a specific goal will they get access to enter the next round.


## Game_rules

1.Press `[space]` to shoot your claw

2.If you successfully grab something, the claw will drag back the object, if not, it will return when brush up against the wall

3.The larger the object is, the longer it will take to drag it back, also the more money it will make

4.Price and speed of the objects: 
  
  small stone: $1, quickly
  
  large stone: $20, slowly
  
  small gold: $50, quickly
  
  gold of middiem size: $100, slowly
  
  large gold: $500, very slowly
  
  diamond: $600, very quickly
  
5.If you grab TNTs, it will destroy all surrounding objects and turn into a TNT piece values $5

6.Each round will give you 60 seconds and will set a goal($) which increases round by round. If you fail to reach this goal, you will lose

## Features

### Read maps

The program will read a map from the given directory when a ground start, and will make sure the goal can be reached. 

### claw_statement

record the statement of the claw

| name      | type   | range        |
| --------- | ------ | ------------ |
| speed     | int    | 1 - 5        |
| x         | double | map_length_x |
| y         | double | map_length_y |
| direction | double | 0 - pi       |


### print_map

```cpp
//funtion: print the map
//output: map
void print_map()
```

### timer

```cpp
///funtion: 
void time()
```

### calculate_reward

### game_over_or_not



