local Characters=require("src.characters")
local Chaos=require("src.chaos")

local game={platforms={},enemies={},pickups={},coins=0,cameraX=0,charIndex=1}

local function hit(a,b)
 return a.x < b.x+b.w and b.x < a.x+a.w and a.y < b.y+b.h and b.y < a.y+a.h
end

function game:reset()
 self.platforms={{x=-300,y=610,w=2600,h=110},{x=420,y=490,w=220,h=24},{x=780,y=410,w=200,h=24},{x=1120,y=520,w=250,h=24},{x=1510,y=440,w=180,h=24},{x=1840,y=350,w=240,h=24}}
 self.enemies={}
 self.pickups={{x=500,y=445,w=20,h=20},{x=840,y=365,w=20,h=20},{x=1190,y=475,w=20,h=20},{x=1580,y=395,w=20,h=20},{x=1930,y=305,w=20,h=20}}
 self.player={x=120,y=500,w=34,h=48,vx=0,vy=0,onGround=false,hp=3,inv=0}
 self.coins=0 self.cameraX=0
 for i=1,8 do self:spawnEnemy(650+i*190,560) end
end

function game:spawnEnemy(x,y,viewer)
 local kinds={"walker","hopper","heavy"}
 local k=kinds[math.random(#kinds)]
 table.insert(self.enemies,{x=x,y=y,w=k=="heavy" and 46 or 34,h=k=="heavy" and 46 or 34,vx=k=="heavy" and -55 or -90,vy=0,onGround=false,kind=k,viewer=viewer or "",alive=true})
end

local function physics(o,dt,platforms)
 o.vy=o.vy+1450*dt
 o.x=o.x+o.vx*dt
 o.y=o.y+o.vy*dt
 o.onGround=false
 for _,p in ipairs(platforms) do
  if o.x+o.w>p.x and o.x<p.x+p.w and o.y+o.h>=p.y and o.y+o.h-o.vy*dt<=p.y and o.vy>=0 then
   o.y=p.y-o.h o.vy=0 o.onGround=true
  end
 end
end

function love.load()
 love.graphics.setDefaultFilter("nearest","nearest")
 math.randomseed(os.time())
 game:reset()
end

function love.keypressed(k)
 if k=="space" or k=="z" then
  if game.player.onGround then game.player.vy=-Characters.list[game.charIndex].jump end
 elseif k=="q" then game.charIndex=(game.charIndex-2)%#Characters.list+1
 elseif k=="e" then game.charIndex=game.charIndex%#Characters.list+1
 elseif k=="j" then Chaos.random(game,"TEST")
 elseif k=="k" then Chaos.five(game,"TEST")
 elseif k=="l" then Chaos.mega(game,"TEST")
 elseif k=="r" then game:reset() end
end

function love.update(dt)
 dt=math.min(dt,1/30)
 local p=game.player local c=Characters.list[game.charIndex]
 local dir=(love.keyboard.isDown("right","d") and 1 or 0)-(love.keyboard.isDown("left","a") and 1 or 0)
 local run=love.keyboard.isDown("lshift","rshift","x") and c.run or 1
 p.vx=dir*c.speed*run
 physics(p,dt,game.platforms)
 if p.y>850 then game:reset() return end
 p.inv=math.max(0,p.inv-dt)

 for _,e in ipairs(game.enemies) do
  if e.alive then
   physics(e,dt,game.platforms)
   if e.onGround and e.kind=="hopper" and math.random()<0.015 then e.vy=-420 end
   if e.x<0 or e.x>2350 then e.vx=-e.vx end
   if hit(p,e) then
    if p.vy>80 and p.y+p.h-e.y<24 then e.alive=false p.vy=-330 game.coins=game.coins+2
    elseif p.inv<=0 then p.hp=p.hp-1 p.inv=1.5 p.vy=-350 if p.hp<=0 then game:reset() return end end
   end
  end
 end
 for i=#game.pickups,1,-1 do if hit(p,game.pickups[i]) then table.remove(game.pickups,i) game.coins=game.coins+1 end end
 game.cameraX=math.max(0,math.min(1200,p.x-400))
 Chaos.update(game,dt)
end

local function box(x,y,w,h)
 love.graphics.rectangle("fill",math.floor(x-game.cameraX),math.floor(y),w,h)
end

function love.draw()
 love.graphics.clear(.08,.12,.20)
 -- parallax skyline
 for i=0,12 do love.graphics.setColor(.12,.22,.30); box(i*220,360+(i%3)*30,150,250) end
 love.graphics.setColor(.20,.55,.25)
 for _,p in ipairs(game.platforms) do box(p.x,p.y,p.w,p.h) end
 -- pickups
 love.graphics.setColor(1,.85,.15)
 for _,v in ipairs(game.pickups) do love.graphics.circle("fill",v.x-game.cameraX+10,v.y+10,10) end
 -- enemies
 for _,e in ipairs(game.enemies) do if e.alive then
  if e.kind=="heavy" then love.graphics.setColor(.55,.25,.12) elseif e.kind=="hopper" then love.graphics.setColor(.75,.25,.55) else love.graphics.setColor(.75,.35,.15) end
  box(e.x,e.y,e.w,e.h)
  love.graphics.setColor(1,1,1)
  if e.viewer~="" then love.graphics.printf(e.viewer,e.x-game.cameraX-50,e.y-20,e.w+100,"center") end
 end end
 -- player
 local palette={{.9,.15,.12},{.15,.75,.25},{.55,.28,.12},{.85,.25,.25},{.9,.55,.75},{.45,.25,.15}}
 local col=palette[game.charIndex]; love.graphics.setColor(col)
 box(game.player.x,game.player.y,game.player.w,game.player.h)
 love.graphics.setColor(1,1,1)
 local c=Characters.list[game.charIndex]
 love.graphics.print("HELLZ YEAH RETRO WORLD",24,20)
 love.graphics.print("Hero: "..c.name.."  |  Trait: "..c.trait,24,48)
 love.graphics.print("HP: "..game.player.hp.."   Tokens: "..game.coins,24,72)
 love.graphics.print("Move A/D  Jump SPACE  Run SHIFT  Switch Q/E  Chaos J/K/L",24,98)
 if Chaos.timer>0 then love.graphics.printf(Chaos.message,0,145,love.graphics.getWidth(),"center") end
 love.graphics.print("Prototype graphics are original placeholders - gameplay systems are live.",24,love.graphics.getHeight()-35)
end
