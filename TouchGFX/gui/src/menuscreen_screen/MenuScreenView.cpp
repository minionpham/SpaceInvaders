#include <gui/menuscreen_screen/MenuScreenView.hpp>

MenuScreenView::MenuScreenView()
{
	backgroundPosition = 0;
}

void MenuScreenView::setupScreen()
{
    MenuScreenViewBase::setupScreen();
}

void MenuScreenView::tearDownScreen()
{
    MenuScreenViewBase::tearDownScreen();
}

void MenuScreenView::handleTickEvent()
{
	MenuScreenViewBase::handleTickEvent();
	backgroundPosition++;
	if (backgroundPosition > 430) backgroundPosition = 0;
	backgroundStar1.setY(backgroundPosition);
	backgroundStar2.setY(backgroundPosition - 430);
	invalidate();
}
