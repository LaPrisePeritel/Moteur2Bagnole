#include <A4Engine/InputManager.hpp>
#include <stdexcept>

InputManager::InputManager()
{
	if (s_instance != nullptr)
		throw std::runtime_error("only one InputManager can be created");

	s_instance = this;
}

InputManager::~InputManager()
{
	s_instance = nullptr;
}

void InputManager::BindKeyPressed(SDL_KeyCode keyCode, std::string action)
{
	m_keyToAction[keyCode] = std::move(action);
}

void InputManager::BindMouseButtonPressed(MouseButton button, std::string action)
{
	// Plutôt que de traduire depuis notre enum vers les defines de la SDL à chaque événement
	// on peut le faire une seule fois au binding (plus efficace)
	int mouseButton;
	switch (button)
	{
		case MouseButton::Left:   mouseButton = SDL_BUTTON_LEFT;   break;
		case MouseButton::Right:  mouseButton = SDL_BUTTON_RIGHT;  break;
		case MouseButton::Middle: mouseButton = SDL_BUTTON_MIDDLE; break;
		case MouseButton::X1:     mouseButton = SDL_BUTTON_X1;     break;
		case MouseButton::X2:     mouseButton = SDL_BUTTON_X2;     break;
		default:
			return; //< ne devrait pas arriver
	}

	m_mouseButtonToAction[mouseButton] = std::move(action);
}

void InputManager::BindControllerButton(SDL_GameControllerButton button, std::string action)
{
	m_controllerButtonToAction[button] = std::move(action);
}

void InputManager::ClearBindings()
{
	m_controllerButtonToAction.clear();
	m_mouseButtonToAction.clear();
	m_keyToAction.clear();
}

void InputManager::HandleEvent(const SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_CONTROLLERBUTTONDOWN:
		{
			auto it = m_controllerButtonToAction.find(static_cast<SDL_GameControllerButton>(event.cbutton.button));
			if (it != m_controllerButtonToAction.end())
				TriggerAction(it->second);

			break;
		}

		case SDL_KEYDOWN:
		{
			auto it = m_keyToAction.find(event.key.keysym.sym);
			if (it != m_keyToAction.end())
				TriggerAction(it->second);

			break;
		}

		case SDL_MOUSEBUTTONDOWN:
		{
			auto it = m_mouseButtonToAction.find(event.button.button);
			if (it != m_mouseButtonToAction.end())
				TriggerAction(it->second);

			break;
		}
	}
}

void InputManager::OnAction(std::string action, std::function<void()> func)
{
	m_actionToFunc[std::move(action)] = std::move(func);
}

InputManager& InputManager::Instance()
{
	if (!s_instance)
		throw std::runtime_error("InputManager hasn't been instantied");

	return *s_instance;
}

void InputManager::TriggerAction(const std::string& action)
{
	auto it = m_actionToFunc.find(action);
	if (it != m_actionToFunc.end())
	{
		std::function<void()>& func = it->second;
		func();
	}
}

InputManager* InputManager::s_instance = nullptr;