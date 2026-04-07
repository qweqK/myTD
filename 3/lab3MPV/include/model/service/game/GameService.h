#pragma once
enum class Game{WIN, LOSE, PROCESS};///< состояние игры

/**
 * описатель логики программы
 */
class GameService {
    public:
    virtual ~GameService()=default;
    virtual void updateGame(float dt)=0;///< логика обновлениия игры
    virtual Game checkGameState()=0;///<проверка состояния игры
    virtual void removeTrash()=0;///< удалить мусор
};
