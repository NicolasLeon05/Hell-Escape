#include "pause_menu.h"

#include "raylib.h"

#include "objects/button.h"
#include "utils/scene_manager.h"
#include "utils/screen_info.h"
#include "scenes/gameplay_scene.h"

namespace PauseScene
{
	Text::Text pauseTitle;
	Button::Button continueButton;
	Button::Button backToMenuButton;

	static float opacity = 0.01f;
	static Color semiTransparentBlack = { 0, 0, 0, static_cast <unsigned char>(opacity * 255) };

	void Init()
	{
		pauseTitle = Text::GetText
		(screenWidth / 2,
			screenHeight / 3 - static_cast<int>(Text::FontSize::big),
			static_cast<int>(Text::FontSize::big),
			"PAUSED", WHITE);

		Text::CenterTextX(pauseTitle);


		continueButton = Button::GetButton
		(pauseTitle.location.x,
			pauseTitle.location.y + pauseTitle.fontSize + static_cast<float>(Text::Padding::big),
			static_cast <float> (Text::GetTextWidth(pauseTitle)),
			static_cast <float> (pauseTitle.fontSize / 2),
			"CONTINUE", BLACK, MAGENTA, WHITE);

		backToMenuButton = Button::GetButton
		(continueButton.shape.x,
			continueButton.shape.y + pauseTitle.fontSize + static_cast<float>(Text::Padding::small),
			static_cast <float>(Text::GetTextWidth(pauseTitle)),
			static_cast <float>(pauseTitle.fontSize / 2),
			"BACK TO MENU", BLACK, SKYBLUE, WHITE);

	}



	void Update()
	{
		if (Button::IsButtonPrssed(continueButton) ||
			IsKeyReleased(KEY_ESCAPE))
		{
			SceneManager::SetCurrentScene(SceneManager::Gameplay);
		}

		if (Button::IsButtonPrssed(backToMenuButton))
		{
			SceneManager::SetCurrentScene(SceneManager::Menu);
		}
	}

	void Draw()
	{
		DrawRectangle(0, 0, screenWidth, screenHeight, semiTransparentBlack);
		Text::DrawText(pauseTitle);
		Button::DrawButton(continueButton);
		Button::DrawButton(backToMenuButton);
	}
}

