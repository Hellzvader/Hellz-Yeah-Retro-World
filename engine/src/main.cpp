#include "Engine.hpp"
int main(int,char**){ Engine e; if(!e.init()) return 1; int r=e.run(); e.shutdown(); return r; }
