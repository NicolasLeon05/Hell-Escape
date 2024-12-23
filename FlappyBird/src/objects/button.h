#pragma once

#include "raylib.h"

#include "objects/text.h"
#include "utils/scene_manager.h"

namespace Button
{
	extern float buttonWidth;

	struct Button
	{
		Rectangle shape;
		Text::Text textShown;
		Color defaultColor;
		Color altColor;
		Color currentColor;
		//This is the color when the user hovers the mouse over the button.
		Color highlightColor;
	};

	//Detects the mouse inside the bounds of a button
	bool IsMouseOnButton(Button& button);
	bool IsButtonPrssed(Button& button);

	void DrawButton(Button button);

	//Create buttons
	Button GetButton(float x, float y, float width, float height, string content, Color mainColor, Color highlightColor, Color textColor, Text::Fonts font);
};

