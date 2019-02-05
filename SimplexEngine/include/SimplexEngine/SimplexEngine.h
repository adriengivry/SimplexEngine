/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _SIMPLEXENGINE_H
#define _SIMPLEXENGINE_H

/* Actors */
#include "SimplexEngine/Actors/Actor.h"

/* Analytics */
#include "SimplexEngine/Analytics/Profiler.h"
#include "SimplexEngine/Analytics/ProfilerReport.h"
#include "SimplexEngine/Analytics/ProfilerSpy.h"

/* API */
#include "SimplexEngine/API/Export.h"

/* Buffers */
#include "SimplexEngine/Buffers/Buffer2D.h"
#include "SimplexEngine/Buffers/DepthBuffer.h"
#include "SimplexEngine/Buffers/TextureBuffer.h"

/* Components */
#include "SimplexEngine/Components/AActorComponent.h"
#include "SimplexEngine/Components/CameraComponent.h"
#include "SimplexEngine/Components/MeshComponent.h"
#include "SimplexEngine/Components/AColliderComponent.h"
#include "SimplexEngine/Components/BoxColliderComponent.h"
#include "SimplexEngine/Components/SphereColliderComponent.h"
#include "SimplexEngine/Components/CapsuleColliderComponent.h"
#include "SimplexEngine/Components/RigidbodyComponent.h"

/* Core */
#include "SimplexEngine/Core/Engine.h"

/* Data */
#include "SimplexEngine/Data/Color.h"
#include "SimplexEngine/Data/EFontSize.h"
#include "SimplexEngine/Data/ETextAlignment.h"
#include "SimplexEngine/Data/Text.h"
#include "SimplexEngine/Data/Transform.h"
#include "SimplexEngine/Data/Vertex.h"

/* Eventing */
#include "SimplexEngine/Eventing/Event.h"
#include "SimplexEngine/Eventing/EventHandler.h"

/* Inputs */
#include "SimplexEngine/Inputs/EKey.h"
#include "SimplexEngine/Inputs/InputManager.h"

/* Materials */
#include "SimplexEngine/Materials/ABaseMaterial.h"
#include "SimplexEngine/Materials/AMaterial.h"
#include "SimplexEngine/Materials/DefaultMaterial.h"

/* Maths */
#include "SimplexEngine/Maths/QuaternionFactory.h"
#include "SimplexEngine/Maths/Triangle2D.h"

/* Rendering */
#include "SimplexEngine/Rendering/ERasterizationDrawMode.h"
#include "SimplexEngine/Rendering/ERasterizationCullingMode.h"
#include "SimplexEngine/Rendering/Rasterizer.h"
#include "SimplexEngine/Rendering/Renderer.h"
#include "SimplexEngine/Rendering/UserInterface.h"

/* Resources */
#include "SimplexEngine/Resources/Managers/AResourceManager.h"
#include "SimplexEngine/Resources/Managers/MeshManager.h"
#include "SimplexEngine/Resources/Mesh.h"

/* Scenes */
#include "SimplexEngine/Scenes/AScene.h"
#include "SimplexEngine/Scenes/SceneManager.h"

/* Scripts */
#include "SimplexEngine/Scripts/IScript.h"
#include "SimplexEngine/Scripts/GlobalScripts/IGlobalScript.h"
#include "SimplexEngine/Scripts/GlobalScripts/FPSCounter.h"
#include "SimplexEngine/Scripts/GlobalScripts/ProfilerLogger.h"
#include "SimplexEngine/Scripts/GlobalScripts/ThreadCap.h"
#include "SimplexEngine/Scripts/GlobalScripts/HardwareInfo.h"
#include "SimplexEngine/Scripts/GlobalScripts/RasterizationModeSelector.h"
#include "SimplexEngine/Scripts/SceneScripts/ISceneScript.h"
#include "SimplexEngine/Scripts/SceneScripts/CameraController.h"
#include "SimplexEngine/Scripts/SceneScripts/RotateOverTime.h"
#include "SimplexEngine/Scripts/Behaviours/ABehaviour.h"
#include "SimplexEngine/Scripts/Behaviours/FPSController.h"

/* Settings */
#include "SimplexEngine/Settings/EngineSettings.h"
#include "SimplexEngine/Settings/WindowSettings.h"
#include "SimplexEngine/Settings/VideoSettings.h"
#include "SimplexEngine/Settings/UserInterfaceSettings.h"
#include "SimplexEngine/Settings/ResourcesSettings.h"

/* Shaders */
#include "SimplexEngine/Shaders/AShader.h"
#include "SimplexEngine/Shaders/LambertShader.h"
#include "SimplexEngine/Shaders/NormalShader.h"

/* Threading */
#include "SimplexEngine/Threading/ThreadManager.h"

/* Tools */
#include "SimplexEngine/Utils/EasyAssimp.h"
#include "SimplexEngine/Utils/SceneParser.h"

/* Utils */
#include "SimplexEngine/Utils/Clock.h"
#include "SimplexEngine/Utils/SettingsLoader.h"

/* Windowing */
#include "SimplexEngine/Windowing/EWindowState.h"
#include "SimplexEngine/Windowing/Window.h"

#endif // _SIMPLEXENGINE_H