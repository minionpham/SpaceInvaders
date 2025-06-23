#include <gui/gamescreen_screen/GameScreenView.hpp>
#include <D:\Download\SpaceInvaders_HeNhung\SpaceInvaders\STM32CubeIDE\Application\User\src\app.hpp>
#include <BitmapDatabase.hpp>
#include <cmsis_os2.h>
#include <cmsis_os.h>
#include <cstring>

extern void gameTask(void *argument);
osThreadId_t gameTaskHandle;
uint8_t hearts = 7;
bool shouldStopScreen;
extern osMessageQueueId_t RightKeyQueueHandle;
extern osMessageQueueId_t LeftKeyQueueHandle;
extern osMessageQueueId_t UpKeyQueueHandle;
extern osMessageQueueId_t DownKeyQueueHandle;

GameScreenView::GameScreenView()
{
  backgroundPosition = 0;
  gameInstance = Game();
  remove(star1);
  remove(star2);
  remove(star3);
  remove(record);
  remove(menu_button);
  // Prepare ship
  shipImage.setBitmap(touchgfx::Bitmap(BITMAP_SHIP_MAIN_ID));
  shipImage.setXY(gameInstance.ship.coordinateX, gameInstance.ship.coordinateY);
  add(shipImage);

  for(int i=0;i<MAX_BULLET;i++) {
    enemyBulletImage[i].setXY(321, 33);
    enemyBulletImage[i].setBitmap(touchgfx::Bitmap(BITMAP_ENEMY_BULLET_RED_ID));
    shipBulletImage[i].setXY(321, 33);
    shipBulletImage[i].setBitmap(touchgfx::Bitmap(BITMAP_BULLET_DOUBLE_ID));
  }

  for(int i=0;i<MAX_ENEMY;i++) {
    switch(i%3) {
    case 0:
      enemyImage[i].setBitmaps(BITMAP_ENEMY_GREEN_01_ID, BITMAP_ENEMY_GREEN_02_ID);
      break;
    case 1:
      enemyImage[i].setBitmaps(BITMAP_ENEMY_RED_01_ID, BITMAP_ENEMY_RED_02_ID);
      break;
    default:
      break;
    }
    enemyImage[i].setUpdateTicksInterval(20);
  }


}

void GameScreenView::setupScreen()
{
  GameScreenViewBase::setupScreen();
  osThreadTerminate(gameTaskHandle);
  const osThreadAttr_t gameTask_attributes = {
    .name = "gameTask",
    .stack_size = 8192 * 2,
    .priority = (osPriority_t) osPriorityNormal,
  };
  gameTaskHandle = osThreadNew(gameTask, NULL, &gameTask_attributes);
  shouldEndGame = false;
  shouldStopTask = false;
  shouldStopScreen = false;
}

void GameScreenView::tearDownScreen()
{
    GameScreenViewBase::tearDownScreen();
}


// Render game objects
void GameScreenView::handleTickEvent() {
  GameScreenViewBase::handleTickEvent();

  uint16_t score = gameInstance.score;

  uint16_t s1 = score / 100;
  uint16_t s2 = (score / 10) % 10;
  uint16_t s3 = score % 10;

  score10.setVisible(false);
  score11.setVisible(false);
  score12.setVisible(false);
  score13.setVisible(false);
  score14.setVisible(false);
  score15.setVisible(false);
  score16.setVisible(false);
  score17.setVisible(false);
  score18.setVisible(false);
  score19.setVisible(false);

  score20.setVisible(false);
  score21.setVisible(false);
  score22.setVisible(false);
  score23.setVisible(false);
  score24.setVisible(false);
  score25.setVisible(false);
  score26.setVisible(false);
  score27.setVisible(false);
  score28.setVisible(false);
  score29.setVisible(false);

  score30.setVisible(false);
  score31.setVisible(false);
  score32.setVisible(false);
  score33.setVisible(false);
  score34.setVisible(false);
  score35.setVisible(false);
  score36.setVisible(false);
  score37.setVisible(false);
  score38.setVisible(false);
  score39.setVisible(false);

  if(s1 == 0) score10.setVisible(true);
  if(s1 == 1) score11.setVisible(true);
  if(s1 == 2) score12.setVisible(true);
  if(s1 == 3) score13.setVisible(true);
  if(s1 == 4) score14.setVisible(true);
  if(s1 == 5) score15.setVisible(true);
  if(s1 == 6) score16.setVisible(true);
  if(s1 == 7) score17.setVisible(true);
  if(s1 == 8) score18.setVisible(true);
  if(s1 == 9) score19.setVisible(true);

  if(s2 == 0) score20.setVisible(true);
  if(s2 == 1) score21.setVisible(true);
  if(s2 == 2) score22.setVisible(true);
  if(s2 == 3) score23.setVisible(true);
  if(s2 == 4) score24.setVisible(true);
  if(s2 == 5) score25.setVisible(true);
  if(s2 == 6) score26.setVisible(true);
  if(s2 == 7) score27.setVisible(true);
  if(s2 == 8) score28.setVisible(true);
  if(s2 == 9) score29.setVisible(true);

  if(s3 == 0) score30.setVisible(true);
  if(s3 == 1) score31.setVisible(true);
  if(s3 == 2) score32.setVisible(true);
  if(s3 == 3) score33.setVisible(true);
  if(s3 == 4) score34.setVisible(true);
  if(s3 == 5) score35.setVisible(true);
  if(s3 == 6) score36.setVisible(true);
  if(s3 == 7) score37.setVisible(true);
  if(s3 == 8) score38.setVisible(true);
  if(s3 == 9) score39.setVisible(true);

  backgroundPosition++;
  if (backgroundPosition > 430) backgroundPosition = 0;
  backgroundStar1.setY(backgroundPosition);
  backgroundStar2.setY(backgroundPosition - 430);

  if(shouldEndGame && shouldStopTask && !shouldStopScreen) {
	add(record);
	if(score > 150) {
		add(star3);
	} else if (score > 50) {
		add(star2);
	} else {
		add(star1);
	}
    add(menu_button);
    menu_button.invalidate();
    shouldStopScreen = true;
    osThreadTerminate(gameTaskHandle);
  }

  // Get input
  uint8_t res = 0;
  uint32_t count = osMessageQueueGetCount(RightKeyQueueHandle);
  if(count > 0) {
      osMessageQueueGet(RightKeyQueueHandle,&res, NULL, osWaitForever);
      if(res == 'R') {
        gameInstance.ship.updateVelocityX(gameInstance.ship.VELOCITY);
        shipImage.setBitmap(touchgfx::Bitmap(BITMAP_SHIP_RIGHT_ID));
        osMessageQueueReset(LeftKeyQueueHandle);
      } else if(res == 'N'){
        gameInstance.ship.updateVelocityX(0);
        shipImage.setBitmap(touchgfx::Bitmap(BITMAP_SHIP_MAIN_ID));
      }
  }
  uint32_t count2 = osMessageQueueGetCount(LeftKeyQueueHandle);
  if(count2 > 0) {
      osMessageQueueGet(LeftKeyQueueHandle,&res, NULL, osWaitForever);
      if(res == 'L') {
        gameInstance.ship.updateVelocityX(-gameInstance.ship.VELOCITY);
        shipImage.setBitmap(touchgfx::Bitmap(BITMAP_SHIP_LEFT_ID));
        osMessageQueueReset(RightKeyQueueHandle);
      } else if(res == 'N'){
        gameInstance.ship.updateVelocityX(0);
        shipImage.setBitmap(touchgfx::Bitmap(BITMAP_SHIP_MAIN_ID));
      }
  }

  uint32_t count3 = osMessageQueueGetCount(UpKeyQueueHandle);
  if(count3 > 0) {
      osMessageQueueGet(UpKeyQueueHandle,&res, NULL, osWaitForever);
      if(res == 'U') {
        gameInstance.ship.updateVelocityY(gameInstance.ship.VELOCITY);
        osMessageQueueReset(DownKeyQueueHandle);
      } else if(res == 'N'){
        gameInstance.ship.updateVelocityY(0);
      }
  }

  uint32_t count4 = osMessageQueueGetCount(DownKeyQueueHandle);
  if(count4 > 0) {
      osMessageQueueGet(DownKeyQueueHandle,&res, NULL, osWaitForever);
      if(res == 'D') {
        gameInstance.ship.updateVelocityY(-gameInstance.ship.VELOCITY);
        osMessageQueueReset(UpKeyQueueHandle);
      } else if(res == 'N'){
        gameInstance.ship.updateVelocityY(0);
      }
  }

  // update player position and sprite
  shipImage.moveTo(gameInstance.ship.coordinateX, gameInstance.ship.coordinateY);

  // render ship bullet
  for(int i=0; i<MAX_BULLET;i++) {
    switch(shipBullet[i].displayStatus){
    case IS_HIDDEN:
      break;
    case IS_SHOWN:
      shipBulletImage[i].moveTo(shipBullet[i].coordinateX, shipBullet[i].coordinateY);
      break;
    case SHOULD_SHOW:
      shipBulletImage[i].moveTo(shipBullet[i].coordinateX, shipBullet[i].coordinateY);
      add(shipBulletImage[i]);
      shipBullet[i].updateDisplayStatus(IS_SHOWN);
      break;
    case SHOULD_HIDE:
      remove(shipBulletImage[i]);
      shipBullet[i].updateDisplayStatus(IS_HIDDEN);
      break;
    default:
      break;
    }
  }

  // render enemy bullet
  for(int i=0; i<MAX_BULLET;i++) {
    switch(enemyBullet[i].displayStatus){
    case IS_HIDDEN:
      break;
    case IS_SHOWN:
      enemyBulletImage[i].moveTo(enemyBullet[i].coordinateX, enemyBullet[i].coordinateY);
      break;
    case SHOULD_SHOW:
      enemyBulletImage[i].moveTo(enemyBullet[i].coordinateX, enemyBullet[i].coordinateY);
      add(enemyBulletImage[i]);
      enemyBullet[i].updateDisplayStatus(IS_SHOWN);
      break;
    case SHOULD_HIDE:
      remove(enemyBulletImage[i]);
      enemyBullet[i].updateDisplayStatus(IS_HIDDEN);
      break;
    default:
      break;
    }
  }

  // render enemy
  for(int i=0; i<MAX_ENEMY;i++) {
    switch(enemy[i].displayStatus){
    case IS_SHOWN:
      enemyImage[i].moveTo(enemy[i].coordinateX, enemy[i].coordinateY);
      break;
    case SHOULD_SHOW:
      enemyImage[i].moveTo(enemy[i].coordinateX, enemy[i].coordinateY);
      enemyImage[i].startAnimation(false, true, true);
      add(enemyImage[i]);
      enemy[i].updateDisplayStatus(IS_SHOWN);
      break;
    case SHOULD_HIDE:
      enemyImage[i].stopAnimation();
      remove(enemyImage[i]);
      enemy[i].updateDisplayStatus(IS_HIDDEN);
      break;
    case IS_HIDDEN:
    default:
      break;
    }
  }

  // check if player is out of health and should end game
  if(gameInstance.ship.lives != hearts) {
    hearts = gameInstance.ship.lives;
    // reset hearts
    heart_07.setAlpha(100);
    heart_06.setAlpha(100);
    heart_05.setAlpha(100);
    heart_04.setAlpha(100);
    heart_03.setAlpha(100);
    heart_02.setAlpha(100);
    heart_01.setAlpha(100);
    if(hearts >= 1) heart_07.setAlpha(255);
    if(hearts >= 2) heart_06.setAlpha(255);
    if(hearts >= 3) heart_05.setAlpha(255);
    if(hearts >= 4) heart_04.setAlpha(255);
    if(hearts >= 5) heart_03.setAlpha(255);
    if(hearts >= 6) heart_02.setAlpha(255);
    if(hearts >= 7) heart_01.setAlpha(255);
    // If player is out of health
    if(hearts < 1) {
      shouldStopTask = true;
      invalidate();
    }
  }

  invalidate();
}
