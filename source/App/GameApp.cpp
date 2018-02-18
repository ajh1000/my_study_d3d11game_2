
#include "GameApp.h"

#include "SceneTitle.h"


GameApp::GameApp()
{
}


GameApp::~GameApp()
{

}

void GameApp::init()
{
	//add Scene
	addScene("title", make_shared<SceneTitle>());


	//set Scene to render
	setScene("title");

}
