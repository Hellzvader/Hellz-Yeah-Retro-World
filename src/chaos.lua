local Chaos = {}
Chaos.queueFile = "tikfinity_queue.txt"
Chaos.timer = 0
Chaos.message = ""

local function label(name, text)
  Chaos.message = (name and name ~= "" and (name .. ": ") or "") .. text
  Chaos.timer = 3
end

function Chaos.spawnEnemy(game, viewer)
  game:spawnEnemy(game.player.x + math.random(260,520), game.player.y - math.random(20,120), viewer)
end

function Chaos.random(game, viewer)
  local n=math.random(1,4)
  if n==1 then
    Chaos.spawnEnemy(game,viewer); label(viewer,"ENEMY DROP!")
  elseif n==2 then
    game.player.vy=-650; label(viewer,"SUPER JUMP!")
  elseif n==3 then
    game.coins=game.coins+10; label(viewer,"BONUS x10!")
  else
    for i=1,3 do Chaos.spawnEnemy(game,viewer) end; label(viewer,"MINI SWARM!")
  end
end

function Chaos.five(game,viewer)
  for i=1,5 do Chaos.spawnEnemy(game,viewer) end
  label(viewer,"5 ENEMY ATTACK!")
end

function Chaos.mega(game,viewer)
  for i=1,10 do Chaos.spawnEnemy(game,viewer) end
  game.player.vy=-720
  label(viewer,"MEGA EVENT!")
end

function Chaos.processLine(game,line)
  local user,gift,value=line:match("^([^|]*)|([^|]*)|(%d+)")
  if not user then return end
  value=tonumber(value) or 1
  if value>=1000 then Chaos.mega(game,user)
  elseif value>=100 then Chaos.five(game,user)
  else Chaos.random(game,user) end
end

function Chaos.update(game,dt)
  Chaos.timer=math.max(0,Chaos.timer-dt)
  local info=love.filesystem.getInfo(Chaos.queueFile)
  if not info then return end
  local data=love.filesystem.read(Chaos.queueFile)
  if data and data~="" then
    for line in data:gmatch("[^\r\n]+") do Chaos.processLine(game,line) end
    love.filesystem.write(Chaos.queueFile,"")
  end
end
return Chaos
