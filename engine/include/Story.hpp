#pragma once
#include <string>
#include <vector>
struct StoryBeat { int stage; std::string speaker,text; };
inline const std::vector<StoryBeat> STORY={
 {0,"Mario","Peach is gone. These barrels lead toward Kong territory."},
 {0,"Bowser","They hit my fortress too. I am coming with you."},
 {0,"Luigi","Mario... we're really teaming up with Bowser?"},
 {2,"Bowser","Enough guards. Tell us where Peach is!"},
 {5,"Mario","The trail goes deeper through the mines."},
 {8,"Luigi","Those ships are heading toward the factory!"},
 {11,"Bowser","Nobody steals a princess before I do! Move!"},
 {13,"Peach","Mario! Luigi! ...Bowser? This is complicated."},
 {14,"Mario","We finish this together."}
};
