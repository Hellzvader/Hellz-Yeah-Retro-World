#pragma once
enum class ScreenState{Title,Story,CharacterSelect,Playing,Paused,GameOver,Ending,Editor};
struct GameState{ScreenState screen{ScreenState::Title};int menuIndex{};int storyIndex{};bool peachRescued{};};
