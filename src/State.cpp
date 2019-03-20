#include "State.h"
#include "SDL.h"
#include "Face.h"
#include "Sound.h"

State::State() :
	quitRequested(false),
	music("resources/audio/stageState.ogg")
{
	auto background = new GameObject();
	background->AddComponent(new Sprite(*background, "resources/img/ocean.jpg"));
	objectArray.emplace_back(background);
	music.Play();
}

State::~State()
{
	objectArray.clear();
}

bool State::QuitRequested()
{
	return quitRequested;
}

void State::LoadAssets()
{
}

void State::Update(float dt)
{
	Input();
	for (auto& go : objectArray)
	{
		go->Update(dt);
	}
	for (int i = objectArray.size() - 1; i >= 0; i--)
	{
		if (objectArray[i]->IsDead())
		{
			objectArray.erase(objectArray.begin() + i);
		}
	}
}

void State::Render()
{
	for (auto& go : objectArray)
	{
		go->Render();
	}
}

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if (event.type == SDL_QUIT) {
			quitRequested = true;
		}

		// Se o evento for clique...
		if (event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for (int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*)objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if (go->Box.Contains({ (float)mouseX, (float)mouseY })) {
					Face* face = (Face*)go->GetComponent("face");
					if (nullptr != face) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if (event.type == SDL_KEYDOWN) {
			// Se a tecla for ESC, setar a flag de quit
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2(200.f, 0.f).Rotate((rand() % 1440) / 4.f) + Vec2((float)mouseX, (float)mouseY);
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject(int mouseX, int mouseY)
{
	auto go = new GameObject();
	go->AddComponent(new Sprite(*go, "resources/img/penguinface.png"));
	go->Box.CenterAt(mouseX, mouseY);
	go->AddComponent(new Sound(*go, "resources/audio/boom.wav"));
	go->AddComponent(new Face(*go));
	objectArray.emplace_back(go);
}
