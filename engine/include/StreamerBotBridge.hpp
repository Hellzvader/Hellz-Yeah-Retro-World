#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct StreamCommand{
 std::string command;
 std::string viewer;
 std::string argument;
 int value{};
};

// Streamer.bot writes one command per line:
// command|viewer|argument|value
// Examples:
// spawn_enemy|SomeViewer|kritter|1
// spawn_five|SomeViewer||5
// mega|SomeViewer||10
// heal|SomeViewer||2
// damage|SomeViewer||1
// hero|SomeViewer|bowser|0
class StreamerBotBridge{
public:
 std::string queuePath{"streamerbot_queue.txt"};
 float pollInterval{0.10f};
 float elapsed{};
 bool enabled{true};

 std::vector<StreamCommand> poll(float dt){
  std::vector<StreamCommand> out;if(!enabled)return out;
  elapsed+=dt;if(elapsed<pollInterval)return out;elapsed=0;
  std::ifstream f(queuePath);if(!f)return out;
  std::string line;
  while(std::getline(f,line)){
   std::stringstream s(line);std::string cmd,user,arg,val;
   if(!std::getline(s,cmd,'|'))continue;
   std::getline(s,user,'|');std::getline(s,arg,'|');std::getline(s,val);
   int n=0;try{if(!val.empty())n=std::stoi(val);}catch(...){}
   if(!cmd.empty())out.push_back({cmd,user,arg,n});
  }
  f.close();if(!out.empty()){std::ofstream clear(queuePath,std::ios::trunc);}
  return out;
 }
};
