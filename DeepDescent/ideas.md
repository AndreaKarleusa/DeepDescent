# Ideas

## Polishing
- Make the bat flap its wings every N seconds so it looks like it is really flying (physics)

## Optimizations:
- Every class has its own random generator which is just stupid
- Move random generators to the constructor (they are cost heavy)
- Collision manager that takes care of all the collision logic.
- Only check the 9 tiles around the player for colissions

## Quality Of Life
- Better random tile algorithm (one that returns a random float between 0.0f and 1.0f)
- Utils file with random number functions and useful shit
- Static gamestate object that will make using variables 100x easier

## Cleaner code
- Better tile state and sprite managing (in the form of an array)
- Better file structuring
