#include "Scenes/SceneMainMenu.h"
#include "Components/UIElements/Button.h"
#include "Components/UIElements/Slider.h"
#include "Managers/AudioManager.h"
#include "Managers/AssetManager.h"
#include "Managers/WindowManager.h"
#include "Managers/CameraManager.h"
#include "Managers/LanguageManager.h"

#include "Components/SpriteRenderer.h"
#include "Engine.h"

#include "BuilderGameObject.h"

SceneMainMenu::SceneMainMenu(const std::string& _newName) : Scene(_newName)
{
}

void SceneMainMenu::Preload()
{
	AssetManager::AddAsset("BackgroundMainMenu", "Assets/Graphics/Backgrounds/bgMenu.png");
	AssetManager::AddAsset("ButtonsMenu", "Assets/Graphics/UI/Buttons/buttonsMenu.png");
	AssetManager::AddAsset("ButtonGrey", "Assets/Graphics/UI/Buttons/buttonGrey.png");

	AudioManager::AddMusic("MusicAmbiant_HOM", "Assets/Audio/Musics/MusicAmbiant_Hommage.ogg");

	AudioManager::AddSound("ConfirmSelection", "Assets/Audio/SFX/confirm_selection.ogg");
	AudioManager::AddSound("CancelSelection", "Assets/Audio/SFX/cancel_selection.ogg");
	AudioManager::AddSound("CursorSelection", "Assets/Audio/SFX/cursor_selection.ogg");
	AudioManager::AddSound("ErrorSelection", "Assets/Audio/SFX/error_selection.ogg");

	AudioManager::AddMusic("MusicAmbiant_HOM", "Assets/Audio/Musics/MusicAmbiant_Hommage.ogg");
}

void SceneMainMenu::Create()
{
	Scene::Create();

	AudioManager::PlayMusic("MusicAmbiant_HOM");
	GameObject* background1 = BuilderGameObject::CreateBackgroundGameObject("BackgroundMenu", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, 1.0f, 1.0f, AssetManager::GetAsset("BackgroundMainMenu"), 0, 0.f);
	this->CreateSceneButtonsMenu();
	this->ActiveOption(false);
	this->ActiveMenu(true);
	isFadeIn = true;
	fadeInTimeDefault = 5.0f;
}

void SceneMainMenu::Delete()
{
	Scene::Delete();
	AudioManager::StopMusic();
	AssetManager::DeleteAsset("BackgroundMainMenu");
	AssetManager::DeleteAsset("ButtonsMenu");
	AssetManager::DeleteAsset("ButtonGrey");
	AudioManager::DeleteMusic("MusicAmbiant_HOM");

	AudioManager::DeleteSound("ConfirmSelection");
	AudioManager::DeleteSound("CancelSelection");
	AudioManager::DeleteSound("CursorSelection");
	AudioManager::DeleteSound("ErrorSelection");
	Scene::Delete();
}


void SceneMainMenu::Render(sf::RenderWindow* _window)
{
	Scene::Render(_window);
}

void SceneMainMenu::CreateSceneButtonsMenu()
{
	//Size Window
	float widthScreen = WindowManager::GetFloatWindowWidth();
	float heightScreen = WindowManager::GetFloatWindowHeight();

	////Main menu buttons
	//playButton = BuilderGameObject::CreateButtonGameObject("play", widthScreen / 2, heightScreen / 2.1, 0.8f, 0.8f, 0, 0, 1, 3, AssetManager::GetAsset("ButtonsMenu"), 40);
	playButton = BuilderGameObject::CreateButtonGameObject("play", widthScreen / 2, heightScreen / 2.1f, 0.8f, 0.8f, 0, 0, 1, 3, AssetManager::GetAsset("ButtonsMenu"),40);
	//worldButton = BuilderGameObject::CreateButtonGameObject("playBoss", widthScreen / 2, heightScreen / 1.6, 0.8f, 0.8f, 0, 0, 1, 3, AssetManager::GetAsset("ButtonsMenu"),30);
	optionsButton = BuilderGameObject::CreateButtonGameObject("settings", widthScreen / 2, heightScreen / 1.6f, 0.8f, 0.8f, 0, 0, 1, 3, AssetManager::GetAsset("ButtonsMenu"),40);
	quitButton = BuilderGameObject::CreateButtonGameObject("quit", widthScreen / 2, heightScreen / 1.275f, 0.8f, 0.8f, 0, 0, 1, 3, AssetManager::GetAsset("ButtonsMenu"),40);

	//Menu Options Buttons
	backButton = BuilderGameObject::CreateButtonGameObject("back", widthScreen / 10, heightScreen / 10, 0.5f, 0.5f, 0, 0, 1, 3, AssetManager::GetAsset("ButtonsMenu"), 40);
	englishButton = BuilderGameObject::CreateButtonGameObject("englishButton", widthScreen / 2.4, heightScreen / 1.2, 0.5f, 0.5f, 0, 0, 1, 3, AssetManager::GetAsset("ButtonsMenu"), 40);
	frenchButton = BuilderGameObject::CreateButtonGameObject("frenchButton", widthScreen / 1.7, heightScreen / 1.2, 0.5f, 0.5f, 0, 0, 1, 3, AssetManager::GetAsset("ButtonsMenu"), 40);
	sliderFPS = BuilderGameObject::CreateSliderGameObject("slider Fps", widthScreen / 2, heightScreen / 2, 1200, 40, 50, 50, 20, WindowManager::GetFps(), WindowManager::GetMinFps(), WindowManager::GetMaxFps());
	sliderVolume = BuilderGameObject::CreateSliderGameObject("slider Volume", widthScreen / 2, heightScreen / 1.5, 1200, 40, 50, 50, 20, AudioManager::GetVolume(), AudioManager::GetMaxVolume());

	CameraManager::SetCenter(widthScreen / 2, heightScreen / 2);
}

void SceneMainMenu::Update(const float& _delta)
{
	Scene::Update(_delta);
	//RunScene
	if (isFadeIn)
	{
		playButton->SetActive(false);
		//worldButton->SetActive(false);
		optionsButton->SetActive(false);
		quitButton->SetActive(false);
		if (FadeIn(_delta))
		{
			isFadeIn = false;
			playButton->SetActive(true);
			//worldButton->SetActive(true);
			optionsButton->SetActive(true);
			quitButton->SetActive(true);
		}
	} 
	else
	{
		if ((playButton->GetComponent<Button>()->IsClicked() || isFadeOut) && playButton->GetActive())
		{
			isFadeOut = true;
			if (FadeOut(_delta))
			{
				AudioManager::PlaySound("ConfirmSelection");
				SceneManager::RunScene("SceneGameSpawn");
			}

		}
	/*	else if (worldButton->GetComponent<Button>()->IsClicked())
		{
			AudioManager::PlaySound("ConfirmSelection");
			SceneManager::RunScene("SceneGameBossRoom");
		}*/
		else if (optionsButton->GetComponent<Button>()->IsClicked() && optionsButton->GetActive())
		{
			AudioManager::PlaySound("ConfirmSelection");
			this->ActiveMenu(false);
			this->ActiveOption(true);
		}
		else if (quitButton->GetComponent<Button>()->IsClicked() && quitButton->GetActive())
		{
			Engine::GetInstance()->Quit();
		}
		else if (backButton->GetComponent<Button>()->IsClicked() && backButton->GetActive())
		{
			AudioManager::PlaySound("CancelSelection");
			optionsButton->GetComponent<Button>()->SetState(Button::StateButton::Normal);
			this->ActiveOption(false);
			this->ActiveMenu(true);
		}
		else if (englishButton->GetComponent<Button>()->IsClicked() && englishButton->GetActive())
		{
			language = "English";
			LanguageManager* manager = LanguageManager::GetInstance();
			manager->SetLanguage("English");
			manager->GetButton();
			frenchButton->GetComponent<Button>()->SetState(Button::Normal);

		}
		else if (frenchButton->GetComponent<Button>()->IsClicked() && frenchButton->GetActive())
		{
			language = "Francais";
			LanguageManager* manager = LanguageManager::GetInstance();
			manager->SetLanguage("Francais");
			manager->GetButton();
			englishButton->GetComponent<Button>()->SetState(Button::Normal);
		}
		if (option) {
			if (sliderFPS && sliderFPS->GetActive()) {
				Slider* fpsSlider = sliderFPS->GetComponent<Slider>();
				float currentFPS = fpsSlider->GetDataInt();
				float previousFPS = fpsSlider->GetPreviousData();

				if (previousFPS != currentFPS) {
					WindowManager::SetFps(currentFPS);
				}
			}

			if (sliderVolume && sliderVolume->GetActive()) {
				Slider* volumeSlider = sliderVolume->GetComponent<Slider>();
				float currentVolume = volumeSlider->GetDataInt();
				float previousVolume = volumeSlider->GetPreviousData();

				if (previousVolume != currentVolume) {
					AudioManager::SetVolume(currentVolume);
				}
			}
		}
	}
	
}

void SceneMainMenu::ActiveMenu(const bool& _state)
{
	this->playButton->SetActiveAndVisible(_state);
	//this->worldButton->SetActiveAndVisible(_state);
	this->optionsButton->SetActiveAndVisible(_state);
	this->quitButton->SetActiveAndVisible(_state);
}

void SceneMainMenu::ActiveOption(const bool& _state)
{
	this->backButton->SetActiveAndVisible(_state);
	this->sliderFPS->SetActiveAndVisible(_state);
	this->sliderVolume->SetActiveAndVisible(_state);
	this->englishButton->SetActiveAndVisible(_state);
	this->frenchButton->SetActiveAndVisible(_state);
	option = _state;
	if (LanguageManager::GetInstance()->GetLanguage() == "English")
	{
		englishButton->GetComponent<Button>()->SetState(Button::Clicked);
		frenchButton->GetComponent<Button>()->SetState(Button::Normal);
	}
	if (LanguageManager::GetInstance()->GetLanguage() == "French")
	{
		frenchButton->GetComponent<Button>()->SetState(Button::Clicked);
		englishButton->GetComponent<Button>()->SetState(Button::Normal);
	}
}

SceneMainMenu::~SceneMainMenu()
{
	this->Delete();
}