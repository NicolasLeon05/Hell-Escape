#pragma once

namespace SceneManager
{
	//Saves every scene in the game
	enum Scene
	{
		None,
		Menu,
		Gameplay,
		Pause,
		Result,
		Credits,
		HowToPlay
	};
 
	//changes the current scene
	void SetCurrentScene(Scene scene);
	//returns the current scene
	Scene GetCurrentScene();

}

