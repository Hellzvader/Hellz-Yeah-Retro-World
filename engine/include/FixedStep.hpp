#pragma once
struct FixedStep{
 static constexpr double STEP=1.0/60.0;
 double accumulator{};
 template<class F>void update(double elapsed,F&&tick){
  if(elapsed>.25)elapsed=.25;accumulator+=elapsed;
  while(accumulator>=STEP){tick((float)STEP);accumulator-=STEP;}
 }
 float alpha()const{return(float)(accumulator/STEP);}
};
