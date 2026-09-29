#include "Engine.hpp"
#include <algorithm>
#include <cmath>
#include <string>

static bool overlap(float x,float y,float w,float h,const Rect& b){return x<b.x+b.w&&b.x<x+w&&y<b.y+b.h&&b.y<y+h;}
static bool overlapE(float x,float y,float w,float h,const EnemyActor&e){return x<e.x+38&&e.x<x+w&&y<e.y+42&&e.y<y+h;}
static void rect(SDL_Renderer*r,float x,float y,float w,float h){SDL_FRect q{x,y,w,h};SDL_RenderFillRect(r,&q);}


struct ArtColor{Uint8 r,g,b,a;};
static void px(SDL_Renderer*r,float x,float y,float s,ArtColor c){SDL_SetRenderDrawColor(r,c.r,c.g,c.b,c.a);rect(r,x,y,s,s);}
static void builtinHero(SDL_Renderer*r,int hero,float x,float y,bool flip){
 const char* p=hero==2?
 "..GGGG....\n.GYYYYG...\nGGYYYYGG..\nGGRYYRGG..\nGGYYYYGG..\n.GGGGGG...\n..RRRR....\n.RRRRRR...\nRRRYYRRR..\nRRRYYRRR..\n.RRRRRR...\n..RRRR....\n..R..R....\n.RR..RR...":
 hero==1?
 "...GGG....\n..GGGGG...\n..SSSS....\n.SSSSSS...\n.SBSSBS...\n.SSSSSS...\n..BBBB....\n.GGGGGG...\nGGGGGGGG..\nGGG..GGG..\n..BBBB....\n..BBBB....\n..B..B....\n.BB..BB...":
 "...RRR....\n..RRRRR...\n..SSSS....\n.SSSSSS...\n.SBSSBS...\n.SSSSSS...\n..BBBB....\n.RRRRRR...\nRRRRRRRR..\nRRR..RRR..\n..BBBB....\n..BBBB....\n..B..B....\n.BB..BB...";
 ArtColor red{220,45,35,255},green{35,180,70,255},skin{244,174,105,255},blue{35,80,205,255},yellow{245,190,45,255},dark{65,35,25,255};
 float s=hero==2?4.5f:3.5f;int row=0,col=0;
 for(const char*q=p;*q;q++){if(*q=='\n'){row++;col=0;continue;}char ch=*q;int cc=flip?9-col:col;ArtColor z=ch=='R'?red:ch=='G'?green:ch=='S'?skin:ch=='B'?blue:ch=='Y'?yellow:dark;if(ch!='.')px(r,x+cc*s,y+row*s,s,z);col++;}
}
static void builtinEnemy(SDL_Renderer*r,const EnemyActor&e,float x,float y){
 const bool boss=e.def().boss;const bool fly=e.def().flying;
 ArtColor body=e.def().id=="king_zing"?ArtColor{245,190,35,255}:e.def().id=="kudgel"?ArtColor{120,80,170,255}:ArtColor{55,175,75,255};
 ArtColor belly{235,205,120,255},dark{35,45,30,255},white{245,245,230,255},wing{150,210,235,255};
 float s=boss?7.f:4.f;
 const char*p=boss?
 "..BBBBBB..\n.BBBBBBBB.\nBBWWBBWWBB\nBBBBBBBBBB\n.BBYYYYBB.\n.BBBBBBBB.\nBBBBBBBBBB\nBBB....BBB\n.BB....BB.\n.B......B.":
 fly?
 ".W......W.\n.W.BBBB.W.\n..BBBBBB..\n.BBWWWWBB.\n.BBBBBBBB.\n..BYYYYB..\n...BBBB...\n..B....B..":
 "...BBBB...\n..BBBBBB..\n.BBWWWWBB.\n.BBBBBBBB.\n.BBYYYYBB.\n..BBBBBB..\n..BB..BB..\n.BB....BB.";
 int row=0,col=0;for(const char*q=p;*q;q++){if(*q=='\n'){row++;col=0;continue;}ArtColor z=*q=='B'?body:*q=='Y'?belly:*q=='W'?(fly?wing:white):dark;if(*q!='.')px(r,x+col*s,y+row*s,s,z);col++;}
}
static void builtinObject(SDL_Renderer*r,const WorldObject&o,float cameraX){
 float x=o.bounds.x-cameraX,y=o.bounds.y;
 if(o.type==ObjectType::Ground||o.type==ObjectType::Platform||o.type==ObjectType::MovingPlatform||o.type==ObjectType::BreakableBlock){
  SDL_SetRenderDrawColor(r,116,72,42,255);rect(r,x,y,o.bounds.w,o.bounds.h);
  SDL_SetRenderDrawColor(r,60,160,65,255);rect(r,x,y,o.bounds.w,std::min(8.f,o.bounds.h));
  SDL_SetRenderDrawColor(r,82,48,32,255);for(float xx=x+8;xx<x+o.bounds.w;xx+=24)rect(r,xx,y+12,8,std::min(8.f,o.bounds.h-12));
 }else if(o.type==ObjectType::Coin){SDL_SetRenderDrawColor(r,250,205,30,255);rect(r,x+6,y,8,o.bounds.h);rect(r,x,y+6,20,std::max(8.f,o.bounds.h-12));SDL_SetRenderDrawColor(r,255,245,150,255);rect(r,x+5,y+6,4,12);}
 else if(o.type==ObjectType::Barrel){SDL_SetRenderDrawColor(r,150,83,38,255);rect(r,x+5,y,o.bounds.w-10,o.bounds.h);SDL_SetRenderDrawColor(r,55,35,25,255);rect(r,x,y+7,o.bounds.w,5);rect(r,x,y+o.bounds.h-12,o.bounds.w,5);}
 else if(o.type==ObjectType::Vine){SDL_SetRenderDrawColor(r,45,165,55,255);rect(r,x+o.bounds.w/2-3,y,6,o.bounds.h);for(float yy=y+12;yy<y+o.bounds.h;yy+=24){rect(r,x,yy,o.bounds.w/2,5);rect(r,x+o.bounds.w/2,yy+10,o.bounds.w/2,5);}}
 else if(o.type==ObjectType::Water){SDL_SetRenderDrawColor(r,35,130,220,210);rect(r,x,y,o.bounds.w,o.bounds.h);SDL_SetRenderDrawColor(r,120,215,250,255);for(float xx=x;xx<x+o.bounds.w;xx+=32)rect(r,xx,y,18,4);}
 else if(o.type==ObjectType::Hazard){SDL_SetRenderDrawColor(r,235,70,35,255);for(float xx=x;xx<x+o.bounds.w;xx+=18){rect(r,xx+6,y,6,o.bounds.h);rect(r,xx+3,y+o.bounds.h*.45f,12,o.bounds.h*.55f);}}
 else if(o.type==ObjectType::Checkpoint){SDL_SetRenderDrawColor(r,225,225,210,255);rect(r,x+4,y,5,o.bounds.h);SDL_SetRenderDrawColor(r,240,55,55,255);rect(r,x+9,y+5,24,16);}
 else if(o.type==ObjectType::Exit){SDL_SetRenderDrawColor(r,95,58,35,255);rect(r,x,y,o.bounds.w,o.bounds.h);SDL_SetRenderDrawColor(r,25,20,18,255);rect(r,x+13,y+18,o.bounds.w-26,o.bounds.h-18);SDL_SetRenderDrawColor(r,245,200,50,255);rect(r,x+45,y+55,5,5);}
 else if(o.type==ObjectType::Peach){ArtColor pink{245,110,170,255},skin{245,185,135,255},gold{250,205,40,255};for(int i=0;i<5;i++)px(r,x+10+i*4,y+8,4,gold);for(int i=0;i<4;i++)px(r,x+12+i*4,y+16,4,skin);SDL_SetRenderDrawColor(r,pink.r,pink.g,pink.b,255);rect(r,x+8,y+32,28,34);rect(r,x,y+54,44,16);}
}
static void builtinPower(SDL_Renderer*r,PowerupType t,float x,float y){
 ArtColor red{230,45,40,255},white{245,245,235,255},gold{250,205,35,255},pink{235,70,110,255};
 if(t==PowerupType::Star){SDL_SetRenderDrawColor(r,gold.r,gold.g,gold.b,255);rect(r,x+10,y,12,32);rect(r,x,y+10,32,12);rect(r,x+5,y+5,22,22);}
 else if(t==PowerupType::Heart){SDL_SetRenderDrawColor(r,pink.r,pink.g,pink.b,255);rect(r,x+4,y+5,10,10);rect(r,x+18,y+5,10,10);rect(r,x+8,y+12,16,12);rect(r,x+12,y+22,8,8);}
 else{ArtColor cap=t==PowerupType::FireFlower?gold:red;SDL_SetRenderDrawColor(r,cap.r,cap.g,cap.b,255);rect(r,x+3,y+4,26,14);rect(r,x+8,y,16,22);SDL_SetRenderDrawColor(r,white.r,white.g,white.b,255);rect(r,x+8,y+6,5,5);rect(r,x+20,y+6,5,5);SDL_SetRenderDrawColor(r,60,175,70,255);rect(r,x+14,y+20,5,12);}
}

bool Engine::init(){
 if(!SDL_Init(SDL_INIT_VIDEO|SDL_INIT_GAMEPAD))return false;
 window=SDL_CreateWindow("Hellz Yeah Retro World - Mario + Bowser Rescue",1280,720,SDL_WINDOW_RESIZABLE);
 if(!window)return false; renderer=SDL_CreateRenderer(window,nullptr);if(!renderer)return false;
 sprites.setRenderer(renderer);gamepads.scan();saveData.load("hellzyeah_save.dat");hero.heroIndex=std::clamp(saveData.selectedHero,0,2);SDL_SetRenderVSync(renderer,1);loadStage(std::clamp(saveData.unlockedStage,0,(int)campaign.stages.size()-1));return true;
}
void Engine::shutdown(){if(renderer)SDL_DestroyRenderer(renderer);if(window)SDL_DestroyWindow(window);SDL_Quit();}
void Engine::loadStage(int i){
 stageIndex=(i+(int)campaign.stages.size())%campaign.stages.size();
 auto b=buildStage(stageIndex);world=std::move(b.world);enemies=std::move(b.enemies);bossStates.assign(enemies.size(),BossState{});
 hero.x=b.spawnX;hero.y=b.spawnY;hero.vx=hero.vy=0;hero.hp=hero.def().hp;shots.clear();powerups.clear();firePower=false;starTimer=0;cameraX=0;
 traversal=TraversalState{};traversal.checkpointX=b.spawnX;traversal.checkpointY=b.spawnY;
 barrels.clear();movingPlatforms.clear();carriedBarrel=-1;
 for(const auto&o:world.objects){
  if(o.type==ObjectType::Barrel)barrels.push_back({o.bounds.x,o.bounds.y,0,0,false,true});
  if(o.type==ObjectType::MovingPlatform)movingPlatforms.push_back({o.bounds,o.bounds.x,o.bounds.y,120.f,1.15f,(stageIndex%2)==0});
 }
 // Seed useful pickups through every stage so power-ups are part of normal play.
 powerups.push_back({PowerupType::Mushroom,b.spawnX+360,520,true});
 powerups.push_back({PowerupType::FireFlower,b.spawnX+760,500,true});
 powerups.push_back({PowerupType::Star,b.spawnX+1180,480,true});
 powerups.push_back({PowerupType::Heart,b.spawnX+1580,500,true});
 std::string title="Hellz Yeah Retro World - "+campaign.stages[stageIndex].title+" - "+hero.def().name;
 SDL_SetWindowTitle(window,title.c_str());
}
void Engine::fire(){
 if((!hero.def().fire&&!firePower)||attackTimer>0)return;
 shots.push_back({hero.x+(hero.facing>0?34:-12),hero.y+18,hero.facing*520,1.5f,true});attackTimer=.28f;
}
void Engine::smash(){
 if(!hero.def().smash||attackTimer>0)return;attackTimer=.5f;
 for(auto&e:enemies)if(e.alive&&std::abs((e.x+19)-(hero.x+17))<95&&std::abs(e.y-hero.y)<70){e.hp-=3;if(e.hp<=0)e.alive=false;}
}
void Engine::event(const SDL_Event&e){
 if(e.type==SDL_EVENT_QUIT)running=false;
 // Keyboard/mouse are editor tools only. Gameplay is controller-only.
 if(!playMode&&e.type==SDL_EVENT_KEY_DOWN)switch(e.key.key){
  case SDLK_ESCAPE:playMode=true;break;
  case SDLK_F5:playMode=true;break;
  case SDLK_1:brush=ObjectType::Ground;break;case SDLK_2:brush=ObjectType::Platform;break;
  case SDLK_3:brush=ObjectType::Enemy;break;case SDLK_4:brush=ObjectType::Coin;break;
  case SDLK_5:brush=ObjectType::Barrel;break;case SDLK_6:brush=ObjectType::Vine;break;
  case SDLK_7:brush=ObjectType::Exit;break;case SDLK_F2:world.save("level1.hyrworld");break;
 }
 if(!playMode&&e.type==SDL_EVENT_MOUSE_BUTTON_DOWN&&e.button.button==SDL_BUTTON_LEFT)placeObject(e.button.x+cameraX,e.button.y);
}
void Engine::placeObject(float x,float y){
 WorldObject o{brush,{std::floor(x/16)*16,std::floor(y/16)*16,48,48},"Object"};
 if(brush==ObjectType::Ground||brush==ObjectType::Platform)o.bounds.w=96,o.bounds.h=24;
 if(brush==ObjectType::Vine)o.bounds.w=20,o.bounds.h=160;if(brush==ObjectType::Exit)o.bounds.w=64,o.bounds.h=110;
 world.objects.push_back(o);
}
void Engine::updateHero(float dt){
 // Controller-only platform movement: acceleration, braking, air control and variable jump height.
 float d=(pad.right?1.f:0.f)-(pad.left?1.f:0.f);
 if(d)hero.facing=d;
 const float maxSpeed=hero.def().speed;
 // Mario is balanced, Luigi is floatier/slipperier, Bowser is heavy with stronger traction.
 const float accel=hero.heroIndex==2?(hero.grounded?1850.f:650.f):hero.heroIndex==1?(hero.grounded?1320.f:900.f):(hero.grounded?1550.f:820.f);
 const float brake=hero.heroIndex==2?(hero.grounded?2350.f:620.f):hero.heroIndex==1?(hero.grounded?1450.f:460.f):(hero.grounded?1900.f:520.f);
 const float target=d*maxSpeed;
 if(d!=0.f){
  if(hero.vx<target)hero.vx=std::min(target,hero.vx+accel*dt);
  else if(hero.vx>target)hero.vx=std::max(target,hero.vx-accel*dt);
 }else{
  if(hero.vx>0)hero.vx=std::max(0.f,hero.vx-brake*dt);
  else if(hero.vx<0)hero.vx=std::min(0.f,hero.vx+brake*dt);
 }
 const bool jumpPressed=pad.jump&&!previousPad.jump;
 const bool jumpReleased=!pad.jump&&previousPad.jump;
 if(jumpPressed&&hero.grounded){hero.vy=-hero.def().jump;hero.grounded=false;}
 // Releasing jump early cuts upward velocity for short hops.
 if(jumpReleased&&hero.vy<0)hero.vy*=0.45f;
 // Slightly lighter gravity while holding jump upward, heavier on the fall.
 const float baseUp=hero.heroIndex==1?1020.f:hero.heroIndex==2?1380.f:1180.f;
 const float baseDown=hero.heroIndex==1?1450.f:hero.heroIndex==2?1900.f:1650.f;
 const float gravity=(pad.jump&&hero.vy<0)?baseUp:baseDown;
 hero.vy=std::min(hero.vy+gravity*dt,hero.heroIndex==2?1050.f:900.f);
 if(pad.attack&&!previousPad.attack)fire();
 if(pad.special&&!previousPad.special){
  smash();
  if(hero.def().id==HeroId::Bowser)for(auto&o:world.objects)if(o.type==ObjectType::BreakableBlock&&o.bounds.w>0&&std::abs((o.bounds.x+o.bounds.w*.5f)-(hero.x+16))<85&&std::abs((o.bounds.y+o.bounds.h*.5f)-(hero.y+24))<75){o.bounds.w=0;o.bounds.h=0;}
 }
 if(pad.interact&&!previousPad.interact){
  if(carriedBarrel>=0&&carriedBarrel<(int)barrels.size()){throwBarrel(barrels[carriedBarrel],hero);carriedBarrel=-1;}
  else{int n=nearestBarrel(barrels,hero);if(n>=0){barrels[n].carried=true;carriedBarrel=n;}}
 }
 if(pad.prevHero&&!previousPad.prevHero){hero.switchPrev();saveData.selectedHero=hero.heroIndex;}
 if(pad.nextHero&&!previousPad.nextHero){hero.switchNext();saveData.selectedHero=hero.heroIndex;}
 float oldX=hero.x,oldY=hero.y;
 hero.x+=hero.vx*dt;
 // Resolve horizontal solids so movement cannot simply pass through terrain.
 for(const auto&o:world.objects)if(o.type==ObjectType::Ground){
  if(overlap(hero.x,hero.y,34,48,o.bounds)){
   if(hero.vx>0)hero.x=o.bounds.x-34;else if(hero.vx<0)hero.x=o.bounds.x+o.bounds.w;
   hero.vx=0;
  }
 }
 hero.y+=hero.vy*dt;hero.grounded=false;
 for(const auto&o:world.objects)if(o.type==ObjectType::Ground||o.type==ObjectType::Platform)
  if(overlap(hero.x,hero.y,34,48,o.bounds)&&hero.vy>=0&&oldY+48<=o.bounds.y+8){hero.y=o.bounds.y-48;hero.vy=0;hero.grounded=true;}
 hero.x=std::clamp(hero.x,0.f,std::max(0.f,(float)world.width-34.f));
 if(hero.y>800)respawnAtCheckpoint(hero,traversal);
 for(const auto&o:world.objects)if(o.type==ObjectType::Exit&&overlap(hero.x,hero.y,34,48,o.bounds)){
  bool bossAlive=false;for(auto&e:enemies)if(e.alive&&e.def().boss)bossAlive=true;
  if(!bossAlive){
   if(stageIndex<(int)campaign.stages.size()-1){
    saveData.unlockedStage=std::max(saveData.unlockedStage,stageIndex+1);
    saveData.selectedHero=hero.heroIndex;saveData.save("hellzyeah_save.dat");
    loadStage(stageIndex+1);
   }
  }
 }
 cameraX=std::clamp(hero.x-450.f,0.f,std::max(0.f,(float)world.width-1280));
}
void Engine::updateBarrelGameplay(float dt){
 updateBarrels(barrels,hero,dt);
 for(auto&b:barrels)if(b.active&&!b.carried&&std::abs(b.vx)>120.f){
  for(auto&e:enemies)if(e.alive&&overlapE(b.x,b.y,42,50,e)){
   e.hp-=2;b.active=false;b.vx=0;if(e.hp<=0)e.alive=false;break;
  }
 }
 if(carriedBarrel>=0&&(carriedBarrel>=(int)barrels.size()||!barrels[carriedBarrel].active))carriedBarrel=-1;
}
void Engine::updatePowerups(float dt){
 starTimer=std::max(0.f,starTimer-dt);
 for(auto&p:powerups)if(p.active&&overlap(hero.x,hero.y,34,48,Rect{p.x,p.y,30,30})){
  if(p.type==PowerupType::FireFlower){firePower=true;hero.hp=std::min(hero.def().hp,hero.hp+1);attackTimer=0;}
  else if(p.type==PowerupType::Star){starTimer=8.f;hurtTimer=0;}
  else applyPowerup(hero,p.type);
  p.active=false;
 }
}
void Engine::updateStageMechanics(float dt){
 updateMovingPlatforms(movingPlatforms,visualTime);
 for(const auto&m:movingPlatforms){
  const float feet=hero.y+48.f;
  if(hero.vy>=0&&hero.x+30>m.bounds.x&&hero.x<m.bounds.x+m.bounds.w&&feet>=m.bounds.y-10&&feet<=m.bounds.y+18){hero.y=m.bounds.y-48.f;hero.vy=0;hero.grounded=true;}
 }
 updateTraversal(hero,traversal,world,dt,pad.up,pad.down);
 for(const auto&o:world.objects){
  if(o.type==ObjectType::Hazard&&inside(hero,o.bounds)&&hurtTimer<=0&&starTimer<=0){
   hero.hp--;hurtTimer=1.2f;hero.vy=-360.f;
   if(hero.hp<=0)respawnAtCheckpoint(hero,traversal);
  }
 }
 if(hero.y>800)respawnAtCheckpoint(hero,traversal);
}
void Engine::updateEnemies(float dt){
 const float aiTime=visualTime;
 for(auto&e:enemies)if(e.alive){
  enemyBrain(e,hero.x,hero.y,dt,aiTime);
  e.vy+=e.def().flying?0:1300*dt;e.x+=e.vx*dt;e.y+=e.vy*dt;
   if(!e.def().flying)for(const auto&o:world.objects)if((o.type==ObjectType::Ground||o.type==ObjectType::Platform)&&overlap(e.x,e.y,38,42,o.bounds)&&e.vy>=0){e.y=o.bounds.y-42;e.vy=0;}
  if(e.x<40||e.x>world.width-40)e.vx=-e.vx;
  if(overlapE(hero.x,hero.y,34,48,e)){
   if(starTimer>0){e.alive=false;hero.vy=-180;}
   else if(hero.vy>70&&hero.y+42<e.y+18){e.hp-=hero.def().smash?2:1;hero.vy=pad.jump?-390.f:-315.f;if(e.hp<=0)e.alive=false;}
   else if(hurtTimer<=0){hero.hp--;hurtTimer=1.2f;hero.vx=-hero.facing*240.f;hero.vy=-330;if(hero.hp<=0)respawnAtCheckpoint(hero,traversal);}
  }
 }
}
void Engine::updateCombat(float dt){
 attackTimer=std::max(0.f,attackTimer-dt);hurtTimer=std::max(0.f,hurtTimer-dt);
 bool bossAlive=false;for(const auto&e:enemies)if(e.alive&&e.def().boss)bossAlive=true;
 if(stageIndex==(int)campaign.stages.size()-1){updateRescue(hero,world,rescue,bossAlive);if(rescue.rescued){ending=true;saveData.peachRescued=true;saveData.unlockedStage=stageIndex;saveData.selectedHero=hero.heroIndex;saveData.save("hellzyeah_save.dat");}}
 for(auto&s:shots)if(s.alive){s.x+=s.vx*dt;s.life-=dt;if(s.life<=0)s.alive=false;for(auto&e:enemies)if(e.alive&&overlapE(s.x,s.y,14,10,e)){e.hp--;s.alive=false;if(e.hp<=0)e.alive=false;break;}}
}
void Engine::applyStreamCommand(const StreamCommand& c){
 auto active=[&](){int n=0;for(const auto&e:enemies)if(e.alive)n++;return n;};
 auto spawn=[&](int count,const std::string&id,const std::string&viewer){
  count=std::clamp(count,1,10);
  for(int i=0;i<count&&active()<28;i++){
   EnemyActor a;int found=-1;
   if(!id.empty())for(int z=0;z<(int)ENEMIES.size();z++)if(ENEMIES[z].id==id){found=z;break;}
   a.defIndex=found>=0?found:8+(i%8);a.x=hero.x+280+i*58;a.y=hero.y-80-(i%3)*30;
   a.hp=a.def().hp;a.vx=-a.def().speed;a.viewer=viewer;enemies.push_back(a);
  }
 };
 if(c.command=="spawn_enemy")spawn(c.value>0?c.value:1,c.argument,c.viewer);
 else if(c.command=="spawn_five")spawn(5,c.argument,c.viewer);
 else if(c.command=="mega")spawn(10,c.argument,c.viewer);
 else if(c.command=="heal")hero.hp=std::min(hero.def().hp,hero.hp+std::max(1,c.value));
 else if(c.command=="damage"){hero.hp-=std::max(1,c.value);if(hero.hp<=0)respawnAtCheckpoint(hero,traversal);}
 else if(c.command=="hero"){
  if(c.argument=="mario")hero.heroIndex=0;else if(c.argument=="luigi")hero.heroIndex=1;else if(c.argument=="bowser")hero.heroIndex=2;
  hero.hp=std::min(hero.hp,hero.def().hp);
 }
 else if(c.command=="restart")loadStage(stageIndex);
}
void Engine::update(float dt){
 visualTime+=dt;
 gamepads.scan();previousPad=pad;pad=gamepads.read(0);
 if(pad.start&&!previousPad.start)paused=!paused;
 if(paused||ending)return;
 for(const auto&command:streamerBot.poll(dt))applyStreamCommand(command);
 if(playMode){updateHero(dt);updateStageMechanics(dt);updateBarrelGameplay(dt);updatePowerups(dt);updateEnemies(dt);updateCombat(dt);}
 else{const auto*k=SDL_GetKeyboardState(nullptr);if(k[SDL_SCANCODE_A]||k[SDL_SCANCODE_LEFT])cameraX=std::max(0.f,cameraX-500*dt);if(k[SDL_SCANCODE_D]||k[SDL_SCANCODE_RIGHT])cameraX=std::min(std::max(0.f,(float)world.width-1280),cameraX+500*dt);}
}
static std::string imported(const std::string& p){return "assets/imported/"+p;}

bool Engine::drawWorldObject(const WorldObject&o){
 std::string id,path;SpriteClip clip{32,32,1,1};
 switch(o.type){
  case ObjectType::Ground:id="tile_ground";path=imported("tiles/ground.bmp");break;
  case ObjectType::Platform:id="tile_platform";path=imported("tiles/platform.bmp");break;
  case ObjectType::Coin:id="item_coin";path=imported("items/coin.bmp");break;
  case ObjectType::Barrel:id="prop_barrel";path=imported("props/barrel.bmp");break;
  case ObjectType::Vine:id="prop_vine";path=imported("props/vine.bmp");break;
  case ObjectType::Exit:id="prop_exit";path=imported("props/exit.bmp");break;
  default:return false;
 }
 return sprites.draw(id,path,clip,visualTime,o.bounds.x-cameraX,o.bounds.y,o.bounds.w,o.bounds.h);
}
void Engine::drawHero(){
 const char*name=hero.heroIndex==0?"mario":hero.heroIndex==1?"luigi":"bowser";
 const bool moving=std::abs(hero.vx)>5;
 const char*state=!hero.grounded?"jump":moving?"run":"idle";
 std::string key=std::string(name)+"_"+state;
 const VisualDef*v=visualFor(key);
 if(v&&sprites.draw("hero_"+key,imported(v->path),v->clip,visualTime,hero.x-cameraX,hero.y-(v->drawH-48),v->drawW,v->drawH,hero.facing<0))return;
 // Missing art is intentionally conspicuous in development builds.
 builtinHero(renderer,hero.heroIndex,hero.x-cameraX,hero.y,hero.facing<0);
}
void Engine::drawEnemy(const EnemyActor&e){
 const VisualDef*v=visualFor(e.def().id);
 if(v&&sprites.draw("enemy_"+e.def().id,imported(v->path),v->clip,visualTime,e.x-cameraX,e.y-(v->drawH-42),v->drawW,v->drawH,e.vx>0))return;
 builtinEnemy(renderer,e,e.x-cameraX,e.y);
}
void Engine::drawGame(){
 SDL_SetRenderDrawColor(renderer,15,27,48,255);SDL_RenderClear(renderer);
 // Layered retro sky and distant silhouettes, visible even before local sprite imports.
 SDL_SetRenderDrawColor(renderer,24,55,82,255);for(int i=0;i<10;i++)rect(renderer,i*180.f-std::fmod(cameraX*.18f,180.f),300+(i%3)*35,150,420);
 SDL_SetRenderDrawColor(renderer,30,82,72,255);for(int i=0;i<12;i++)rect(renderer,i*145.f-std::fmod(cameraX*.35f,145.f),430+(i%2)*24,110,290);
 for(const auto&o:world.objects)if(!drawWorldObject(o))builtinObject(renderer,o,cameraX);
 for(const auto&m:movingPlatforms){SDL_SetRenderDrawColor(renderer,110,110,120,255);rect(renderer,m.bounds.x-cameraX,m.bounds.y,m.bounds.w,m.bounds.h);}
 for(const auto&b:barrels)if(b.active){SpriteClip bc{32,32,1,1};if(!sprites.draw("barrel_live",imported("props/barrel.bmp"),bc,visualTime,b.x-cameraX,b.y,42,50)){WorldObject bo{ObjectType::Barrel,{b.x,b.y,42,50},"Barrel"};builtinObject(renderer,bo,cameraX);}}
 for(const auto&p:powerups)if(p.active){
  const char*file=p.type==PowerupType::Mushroom?"mushroom.bmp":p.type==PowerupType::FireFlower?"fireflower.bmp":p.type==PowerupType::Star?"star.bmp":p.type==PowerupType::Heart?"heart.bmp":"banana.bmp";
  SpriteClip pc{32,32,1,1};if(!sprites.draw(std::string("power_")+file,imported(std::string("items/")+file),pc,visualTime,p.x-cameraX,p.y,32,32))builtinPower(renderer,p.type,p.x-cameraX,p.y);
 }
 for(const auto&e:enemies)if(e.alive)drawEnemy(e);
 SDL_SetRenderDrawColor(renderer,255,145,35,255);for(const auto&s:shots)if(s.alive)rect(renderer,s.x-cameraX,s.y,14,10);
 drawHero();
 SDL_SetRenderDrawColor(renderer,0,0,0,190);rect(renderer,12,12,430,52);
 SDL_SetRenderDrawColor(renderer,220,50,50,255);rect(renderer,26,28,hero.hp*34,18);
 SDL_SetRenderDrawColor(renderer,70,170,245,255);rect(renderer,250,28,(stageIndex+1)*11,18);
}
void Engine::drawEditor(){drawGame();SDL_SetRenderDrawColor(renderer,10,10,14,220);rect(renderer,0,0,1280,76);SDL_SetRenderDrawColor(renderer,60,170,240,255);rect(renderer,16,16,210,44);}
void Engine::draw(){if(playMode)drawGame();else drawEditor();if(paused){SDL_SetRenderDrawColor(renderer,0,0,0,170);rect(renderer,0,0,1280,720);SDL_SetRenderDrawColor(renderer,230,230,230,255);rect(renderer,500,300,280,90);}if(ending){SDL_SetRenderDrawColor(renderer,10,18,42,230);rect(renderer,0,0,1280,720);SDL_SetRenderDrawColor(renderer,245,190,80,255);rect(renderer,390,220,500,220);}SDL_RenderPresent(renderer);}
int Engine::run(){Uint64 last=SDL_GetTicks();while(running){SDL_Event e;while(SDL_PollEvent(&e))event(e);Uint64 now=SDL_GetTicks();float dt=std::min((now-last)/1000.f,.033f);last=now;update(dt);draw();}return 0;}
