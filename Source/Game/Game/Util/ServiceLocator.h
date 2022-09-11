#pragma once
#include <cassert>

namespace Editor
{
    class EditorHandler;
}
class InputManager;
class GameRenderer;
struct EnttRegistries;

namespace enki
{
    class TaskScheduler;
}

class ServiceLocator
{
public:
    static Editor::EditorHandler* GetEditorHandler()
    {
        assert(_editorHandler != nullptr);
        return _editorHandler;
    }
    static void SetEditorHandler(Editor::EditorHandler* editorHandler);

    static InputManager* GetInputManager()
    {
        assert(_inputManager != nullptr);
        return _inputManager;
    }
    static void SetInputManager(InputManager* inputManager);

    static GameRenderer* GetGameRenderer()
    {
        assert(_gameRenderer != nullptr);
        return _gameRenderer;
    }
    static void SetGameRenderer(GameRenderer* gameRenderer);

    static enki::TaskScheduler* GetTaskScheduler()
    {
        assert(_taskScheduler != nullptr);
        return _taskScheduler;
    }
    static void SetTaskScheduler(enki::TaskScheduler* taskScheduler);

    static EnttRegistries* GetEnttRegistries()
    {
        assert(_enttRegistries != nullptr);
        return _enttRegistries;
    }
    static void SetEnttRegistries(EnttRegistries* enttRegistries);

private:
    ServiceLocator() { }
    static Editor::EditorHandler* _editorHandler;
    static InputManager* _inputManager;
    static GameRenderer* _gameRenderer;
    static enki::TaskScheduler* _taskScheduler;
    static EnttRegistries* _enttRegistries;
};