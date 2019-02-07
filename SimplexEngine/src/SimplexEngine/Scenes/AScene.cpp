/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scenes/AScene.h"

SimplexEngine::Scenes::AScene::AScene(SCENE_PARAMETERS) :
	m_window(p_window),
	m_eventHandler(p_eventHandler),
	m_userInterface(p_userInterface),
	m_inputManager(p_inputManager),
	m_meshManager(p_meshManager),
	m_physicsManager(p_physicsManager)
{
}

void SimplexEngine::Scenes::AScene::Load()
{
	OnLoad();
}

void SimplexEngine::Scenes::AScene::Unload()
{
	OnUnload();
	m_actors.clear();
	m_scripts.clear();
}

void SimplexEngine::Scenes::AScene::UpdateBehaviours(float p_deltaTime)
{
	for (auto& actor : m_actors)
		actor->UpdateBehaviours(p_deltaTime);
}

void SimplexEngine::Scenes::AScene::CollectGarbages()
{
	m_actors.erase(std::remove_if(m_actors.begin(), m_actors.end(), [](std::shared_ptr<Actors::Actor> p_actor) { return p_actor->IsDestroyed(); }), m_actors.end());
}

const std::vector<std::shared_ptr<SimplexEngine::Scripts::IScript>>& SimplexEngine::Scenes::AScene::GetScripts() const
{
	return m_scripts;
}

const std::vector<std::shared_ptr<SimplexEngine::Actors::Actor>>& SimplexEngine::Scenes::AScene::GetActors() const
{
	return m_actors;
}

bool SimplexEngine::Scenes::AScene::RemoveActor(Actors::Actor& p_toRemove)
{
	size_t previousSize = m_actors.size();
	m_actors.erase(std::find_if(m_actors.begin(), m_actors.end(), [&p_toRemove](std::shared_ptr<Actors::Actor> p_element) { return &p_toRemove == p_element.get(); }));
	return m_actors.size() != previousSize;
}

bool SimplexEngine::Scenes::AScene::RemoveScript(Scripts::IScript& p_toRemove)
{
	size_t previousSize = m_scripts.size();
	m_scripts.erase(std::find_if(m_scripts.begin(), m_scripts.end(), [&p_toRemove](std::shared_ptr<Scripts::IScript> p_element) { return &p_toRemove == p_element.get(); }));
	return m_scripts.size() != previousSize;
}

void SimplexEngine::Scenes::AScene::OnComponentAdded(Components::AActorComponent& p_component)
{
	ComponentAddedEvent.Invoke(p_component);
}

void SimplexEngine::Scenes::AScene::OnComponentRemoved(Components::AActorComponent& p_component)
{
	ComponentRemovedEvent.Invoke(p_component);
}
