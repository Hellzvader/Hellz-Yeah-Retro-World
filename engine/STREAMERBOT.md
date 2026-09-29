# Streamer.bot Integration

Hellz Yeah Retro World has a dedicated Streamer.bot command queue. This is separate from controller input.

Default queue file:

`streamerbot_queue.txt`

Streamer.bot can append one UTF-8 line per action:

`command|viewer|argument|value`

Supported engine commands:
- `spawn_enemy|viewer|enemy_id|count`
- `spawn_five|viewer||5`
- `mega|viewer||10`
- `heal|viewer||amount`
- `damage|viewer||amount`
- `hero|viewer|mario|0`
- `hero|viewer|luigi|0`
- `hero|viewer|bowser|0`
- `restart|viewer||0`

Enemy spawns retain the viewer name in the EnemyActor, ready for on-screen name rendering.

The bridge polls at 100 ms and caps active enemies to protect the game from event floods. Later Streamer.bot actions can write this file directly or use a small websocket/HTTP adapter without changing the gameplay/controller layer.
