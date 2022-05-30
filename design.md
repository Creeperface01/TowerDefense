#Tower Defense

The concept of game is two opponents. One is defending and
the second is attacking the objective. Attacking side has
available various warriors or attacking mobs that walk towards
the objective and try to destroy it.
Defending side may use different kinds of passive obstacles or
static defensive elements such as shooting towers.
Game ends when attacking side destroys the objective
and wins or when attacking side can't make it in time
and then the defending side wins.

The project will implement the following game mechanics:

- Map configuration - will make it possible to load map from file
  including all map components. The game physics would be also part
  of the map configuration. Another feature would be generating a random map.

- Behavior system for mobs. Should be pretty extensible
  to allow adding new types of mobs without changes to existing code

- Mob attributes. There will be some common attributes
  affecting attacks of mobs.

- Pathfinding to search for the shortest path.

- Game will support both single player and two players
  playing as opponents

- Some key parts of the game should be multithreaded
  to increase game performance.


