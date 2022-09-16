# Space Invaders

A Space Invaders remake using SDL and C++ done in one week.

<p align="center">
  <a>
    <img alt="Made With SDL" src="https://img.shields.io/badge/made%20with-SDL-57b9d3.svg?logo=CPlusPlus">
  </a>
  <a>
    <img alt="License" src="https://img.shields.io/github/license/JoanStinson/SpaceInvaders?&logo=github">
  </a>
  <a>
    <img alt="Last Commit" src="https://img.shields.io/github/last-commit/JoanStinson/SpaceInvaders?logo=Mapbox&color=orange">
  </a>
  <a>
    <img alt="Repo Size" src="https://img.shields.io/github/repo-size/JoanStinson/SpaceInvaders?logo=VirtualBox">
  </a>
  <a>
    <img alt="Downloads" src="https://img.shields.io/github/downloads/JoanStinson/SpaceInvaders/total?color=brightgreen">
  </a>
  <a>
    <img alt="Last Release" src="https://img.shields.io/github/v/release/JoanStinson/SpaceInvaders?include_prereleases&logo=Dropbox&color=yellow">
  </a>
</p>

<p align="center">
  <img width="471" height="716" src="https://github.com/JoanStinson/SpaceInvaders/blob/master/preview.gif">
 </p>

## Installation

1. Unzip "SpaceInvaders.zip".
2. Execute "SpaceInvaders/Space Invaders.exe" and enjoy!

## Usage

- Move: Arrow Keys
- Shoot: Spacebar
- Exit: Escape

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## Basic Features

Player (Spaceship):
- Player can move on the screen (using arrows keys)
- Player can shoot projectiles (using spacebar)

Enemies:
- Enemies move towards the spaceship.
- Enemies have life points (e.g 3, up to you to decide).
- Enemies may shoot as well.

Implement Obstacles (Rocks):
- They are static objects in the level.
- They have life points (up to you to decide).
- They can be hit by the player’s projectiles.
- They CAN NOT be hit by enemies while moving.
- They CAN NOT be hit by enemies’ projectiles.

Player Projectile:
- It is shot from Spaceship.
- It can hit Obstacles.
- It can hit Enemies

Enemy Projectile:
- It is shot from Enemy.
- It can only hit the player.

Basic UI:
- Score
- Hi-Score from the past rounds.

## Credits

Author: [Joan Ginard Mateo](https://github.com/JoanStinson)

## License

[MIT LICENSE](https://github.com/JoanStinson/SpaceInvaders/blob/master/LICENSE)
