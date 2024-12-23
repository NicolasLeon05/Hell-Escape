#include "credits_scene.h"

#include "objects/button.h"
#include "utils/screen_info.h"
#include "utils/sound_manager.h"

//NOTE: All of the above are used

namespace CreditsScene
{
	struct Credit
	{
		string name;
		string url;
		string role;
		Text::Text text;
		Button::Button button;
	};

	enum Roles
	{
		dev1,
		dev2,
		artist1,
		artist2,
		artist3,
		music1,
		sfx1,
		sfx2,
		sfx3,
		sfx4,
		sfx5,
		font1,
		font2,
		font3,
		language,
		library,
		artTool
	};

	enum class Pages
	{
		page1,
		page2,
		page3
	};

	struct Page
	{
		Button::Button button;
		Pages number;
	};

	static const int maxCredits = artTool + 1;

	static Page page1{};
	static Page page2{};
	static Page page3{};

	static Text::Text devTitle;
	static Text::Text artTitle;
	static Text::Text musicAndSoundsTitle;
	static Text::Text fontsTitle;
	static Text::Text toolsTitle;

	static Text::Text soundSubTitle;

	static Button::Button backToMenuButton;

	static Credit creditsInfo[maxCredits];
	static Pages currentPage = Pages::page1;

	static void CheckURLButton(Credit& credit)
	{
		if (Button::IsMouseOnButton(credit.button))
		{
			credit.button.currentColor = credit.button.highlightColor;

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				PlaySound(SoundManager::clickButtonSfx);
				OpenURL(credit.url.c_str());
			}
		}
		else
			credit.button.currentColor = credit.button.defaultColor;
	}

	static void CheckURLButtons()
	{
		switch (currentPage)
		{
		case CreditsScene::Pages::page1:

			for (int i = dev1; i < artist3 + 1; i++)
				CheckURLButton(creditsInfo[i]);

			break;
		case CreditsScene::Pages::page2:

			for (int i = music1; i < sfx5 + 1; i++)
				CheckURLButton(creditsInfo[i]);

			break;
		case CreditsScene::Pages::page3:

			for (int i = font1; i < maxCredits; i++)
				CheckURLButton(creditsInfo[i]);

			break;
		default:
			break;
		}

	}

	static void CheckPagesButton(Page& page)
	{
		if (Button::IsMouseOnButton(page.button))
		{
			page.button.currentColor = page.button.highlightColor;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				PlaySound(SoundManager::clickButtonSfx);
				if (currentPage != page.number)
					currentPage = page.number;
			}
		}
		else if (currentPage == page.number)
			page.button.currentColor = page.button.highlightColor;
		else
			page.button.currentColor = page.button.defaultColor;
	}

	static void InitCredit(Credit& credit, float y)
	{
		Color highlightColor = SKYBLUE;

		if (credit.name == creditsInfo[dev1].name || credit.name == creditsInfo[dev2].name)
			highlightColor = MAGENTA;

		credit.text = Text::GetText
		(screenWidth / 2,
			y,
			Text::Fonts::Default,
			static_cast<int>(Text::FontSize::small),
			credit.role,
			WHITE);
		Text::CenterTextX(credit.text);

		credit.button = Button::GetButton
		(screenWidth / 2,
			credit.text.location.y + credit.text.fontSize + static_cast<int>(Text::Padding::minimum),
			Button::buttonWidth,
			static_cast<float>(credit.text.fontSize) * 2.0f,
			credit.name,
			BLACK, highlightColor, WHITE,
			Text::Fonts::Default);

		credit.button.shape.x -= credit.button.shape.width / 2;
	}

	static void InitCredit(Credit& credit, float y, float x)
	{
		InitCredit(credit, y);
		credit.button.shape.x = x;
		credit.text.location.x = x + credit.button.shape.width / 2 - Text::GetTextWidth(credit.text) / 2;
	}

	static void InitCredits()
	{

#pragma region PAGE_1

		devTitle = Text::GetText
		(screenWidth / 2,
			static_cast<int>(Text::Padding::medium) - static_cast<int>(Text::Padding::tiny),
			Text::Fonts::Title2,
			static_cast<int> (Text::FontSize::medium) * 3/4,
			"DEVELOPMENT",
			MAGENTA);
		Text::CenterTextX(devTitle);

		InitCredit(creditsInfo[dev1], devTitle.location.y + devTitle.fontSize);
		InitCredit(creditsInfo[dev2], creditsInfo[dev1].button.shape.y + creditsInfo[dev1].text.fontSize);

		artTitle = Text::GetText
		(screenWidth / 2,
			creditsInfo[dev2].button.shape.y + creditsInfo[dev2].button.shape.height + static_cast<int>(Text::Padding::small),
			Text::Fonts::Title2,
			devTitle.fontSize,
			"ART",
			YELLOW);
		Text::CenterTextX(artTitle);

		InitCredit(creditsInfo[artist1], artTitle.location.y + artTitle.fontSize + static_cast<int>(Text::Padding::small));
		InitCredit(creditsInfo[artist2], creditsInfo[artist1].button.shape.y + creditsInfo[artist1].text.fontSize + static_cast<int>(Text::Padding::small));
		InitCredit(creditsInfo[artist3], creditsInfo[artist2].button.shape.y + creditsInfo[artist2].text.fontSize + static_cast<int>(Text::Padding::small));

#pragma endregion

#pragma region PAGE_2

		musicAndSoundsTitle = Text::GetText
		(screenWidth / 2,
			devTitle.location.y,
			Text::Fonts::Title2,
			artTitle.fontSize,
			"MUSIC AND SOUNDS",
			artTitle.currentColor);
		Text::CenterTextX(musicAndSoundsTitle);

		float posY = musicAndSoundsTitle.location.y + musicAndSoundsTitle.fontSize + static_cast<float>(Text::Padding::small);

		for (int i = music1; i < sfx5 + 1; i++)
		{
			float posX = static_cast <float> ((i % 2 == 0) ? screenWidth / 20 : screenWidth / 20 * 11);

			InitCredit(creditsInfo[i], posY, posX);

			if (i % 2 == 0)
			{
				posY += creditsInfo[i].button.shape.height + static_cast<int>(Text::Padding::medium);
			}

		}

#pragma endregion

#pragma region PAGE_3

		fontsTitle = Text::GetText
		(screenWidth / 20,
			devTitle.location.y,
			Text::Fonts::Title2,
			artTitle.fontSize,
			"FONTS",
		artTitle.currentColor);
		fontsTitle.location.x += Text::GetTextWidth(fontsTitle) * 1.5f;

		posY = fontsTitle.location.y + fontsTitle.fontSize + static_cast<int>(Text::Padding::small);

		for (int i = font1; i < font3 + 1; i++)
		{
			InitCredit(creditsInfo[i], posY, screenWidth / 20);
			posY += creditsInfo[i].button.shape.height + static_cast<int>(Text::Padding::medium);
		}


		toolsTitle = Text::GetText
		(screenWidth / 20 * 11,
			devTitle.location.y,
			Text::Fonts::Title2,
			artTitle.fontSize,
			"TOOLS",
			artTitle.currentColor);
		toolsTitle.location.x += Text::GetTextWidth(toolsTitle) * 1.5f;

		posY = toolsTitle.location.y + toolsTitle.fontSize + static_cast<int>(Text::Padding::small);

		for (int i = language; i < maxCredits; i++)
		{
			InitCredit(creditsInfo[i], posY, screenWidth / 20 * 11);
			posY += creditsInfo[i].button.shape.height + static_cast<int>(Text::Padding::medium);
		}

#pragma endregion

	}

	static void DrawCredit(Credit& credit, bool drawRole)
	{
		if (drawRole)
		{
			Text::DrawText(credit.text);

		}

		Button::DrawButton(credit.button);
	}


	void Init()
	{
#pragma region CREDITS_INFO

#pragma region DEV_ROLE
		//DEV (ME)
		creditsInfo[dev1].name = "Sofia Alvarez";
		creditsInfo[dev1].url = "https://gensofi24.itch.io/";
		creditsInfo[dev1].role = "DEV";

		creditsInfo[dev2].name = "Nicolas Leon";
		creditsInfo[dev2].url = "https://leon-05.itch.io/";
		creditsInfo[dev2].role = "DEV";
#pragma endregion

#pragma region ART_ROLE
		//ART
		creditsInfo[artist1].name = "Sofia Alvarez";
		creditsInfo[artist1].url = "https://gensofi24.itch.io/";
		creditsInfo[artist1].role = "PIXEL ART";

		creditsInfo[artist2].name = "Ansimuz";
		creditsInfo[artist2].url = "https://ansimuz.itch.io/industrial-parallax-background";
		creditsInfo[artist2].role = "PARALLAX";

		creditsInfo[artist3].name = "ACTG";
		creditsInfo[artist3].url = "https://actg.itch.io/old-pipes-tileset";
		creditsInfo[artist3].role = "PIPES";
#pragma endregion

#pragma region MUSIC_AND_SOUNDS
		//MUSIC_AND_SOUNDS
		//title1
		creditsInfo[music1].name = "Suno AI";
		creditsInfo[music1].url = "https://suno.com/";
		creditsInfo[music1].role = "Music";

		//default text
		creditsInfo[sfx1].name = "Player jumping";
		creditsInfo[sfx1].url = "https://mixkit.co/free-sound-effects/game/";
		creditsInfo[sfx1].role = "Jump SFX";

		//default text
		creditsInfo[sfx2].name = "Select click";
		creditsInfo[sfx2].url = "https://mixkit.co/free-sound-effects/click/";
		creditsInfo[sfx2].role = "Button Click SFX";

		//default text
		creditsInfo[sfx3].name = "Soft quick punch";
		creditsInfo[sfx3].url = "https://mixkit.co/free-sound-effects/hit/";
		creditsInfo[sfx3].role = "Crash SFX";

		//default text
		creditsInfo[sfx4].name = "Musical game over";
		creditsInfo[sfx4].url = "https://mixkit.co/free-sound-effects/game-over/";
		creditsInfo[sfx4].role = "Game Over SFX";

		//default text
		creditsInfo[sfx5].name = "Winning a coin";
		creditsInfo[sfx5].url = "https://mixkit.co/free-sound-effects/video-game/";
		creditsInfo[sfx5].role = "Score Up SFX";
#pragma endregion

#pragma region FONTS
		creditsInfo[font1].name = "NECK ROMANCER";
		creditsInfo[font1].url = "https://www.dafont.com/es/neck-romancer.font";
		creditsInfo[font1].role = "Ttile1";

		creditsInfo[font2].name = "Swamp Witch";
		creditsInfo[font2].url = "https://www.dafont.com/es/swamp-witch.font";
		creditsInfo[font2].role = "Title2";

		creditsInfo[font3].name = "YokoInkScratchy";
		creditsInfo[font3].url = "https://www.dafont.com/es/yoko-ink-scratchy.font";
		creditsInfo[font3].role = "Default";
#pragma endregion

#pragma region LANGUAGE_TOOL

		creditsInfo[language].name = "GITHUB";
		creditsInfo[language].url = "https://github.com/NicolasLeon05/Flappy-Bird-Sofi-";
		creditsInfo[language].role = "SOURCE CODE";

#pragma endregion

#pragma region LIBRARY_TOOL

		creditsInfo[library].name = "RAYLIB";
		creditsInfo[library].url = "https://www.raylib.com/index.html";
		creditsInfo[library].role = "LIBRARY";

#pragma endregion

#pragma region ART_TOOL

		creditsInfo[artTool].name = "PISKEL";
		creditsInfo[artTool].url = "https://www.piskelapp.com/";
		creditsInfo[artTool].role = "ART TOOL";

#pragma endregion


		InitCredits();

#pragma region PAGES

		page2.button = Button::GetButton
		(screenWidth / 2,
			screenHeight,
			40.0f, 40.0f,
			"2",
			WHITE, SKYBLUE, BLACK,
			Text::Fonts::Default);

		page2.button.shape.x -= page2.button.shape.width / 2;
		page2.button.shape.y -= page2.button.shape.height + static_cast<float>(Text::Padding::tiny);
		page2.number = Pages::page2;

		page1.button = page2.button;
		page1.button.textShown.content = "1";
		page1.button.shape.x -= page1.button.shape.width * 2;
		page1.number = Pages::page1;

		page3.button = page1.button;
		page3.button.textShown.content = "3";
		page3.button.shape.x += page3.button.shape.width * 3 + page2.button.shape.width;
		page3.number = Pages::page3;

#pragma endregion

		backToMenuButton = Button::GetButton
		(static_cast<float>(Text::Padding::tiny),
			screenHeight,
			90, 40,
			"BACK",
			BLACK, YELLOW, WHITE,
			Text::Fonts::Default);
		backToMenuButton.shape.y -= backToMenuButton.shape.height + static_cast<float>(Text::Padding::tiny);

	}

	void Update()
	{
		CheckURLButtons();

		if (Button::IsButtonPrssed(backToMenuButton) ||
			IsKeyReleased(KEY_ESCAPE))
		{
			SceneManager::SetCurrentScene(SceneManager::Menu);
		}

		CheckPagesButton(page1);
		CheckPagesButton(page2);
		CheckPagesButton(page3);
	}

	void Draw()
	{
		switch (currentPage)
		{
		case CreditsScene::Pages::page1:

			Text::DrawText(devTitle);
			DrawCredit(creditsInfo[dev1], false);

			DrawCredit(creditsInfo[dev2], false);

			Text::DrawText(artTitle);
			DrawCredit(creditsInfo[artist1], true);

			Text::DrawText(artTitle);
			DrawCredit(creditsInfo[artist2], true);

			Text::DrawText(artTitle);
			DrawCredit(creditsInfo[artist3], true);

			break;
		case CreditsScene::Pages::page2:

			Text::DrawText(musicAndSoundsTitle);

			for (int i = music1; i < sfx5 + 1; i++)
				DrawCredit(creditsInfo[i], true);

			break;
		case CreditsScene::Pages::page3:

			Text::DrawText(fontsTitle);
			for (int i = font1; i < font3 + 1; i++)
				DrawCredit(creditsInfo[i], true);


			Text::DrawText(toolsTitle);

			for (int i = language; i < maxCredits; i++)
				DrawCredit(creditsInfo[i], true);

			break;
		default:
			break;
		}

		Button::DrawButton(page1.button);
		Button::DrawButton(page2.button);
		Button::DrawButton(page3.button);
		Button::DrawButton(backToMenuButton);
	}
}