#ifndef ISTATE_H
#define ISTATE_H

#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

class StateMachine;

class IState
{
    public:
        template <typename ...Args>
        IState(StateMachine& machine, bool replace = true, Args ...args) : mMachine(machine), mReplacing(replace) {}
        virtual ~IState() = default;

        IState (const IState&) = delete;
        IState& operator= (const IState&) = delete;

        virtual void pause() = 0;
        virtual void resume() = 0;

        virtual void update() = 0;
        virtual void draw(sf::RenderTarget& target) = 0;
        virtual void handleEvents(sf::Event& event) = 0;

        std::unique_ptr<IState> next()
        {
            return std::move(mNext);
        }

        bool isReplacing()
        {
            return mReplacing;
        }

    protected:
        StateMachine& mMachine;

        bool mReplacing;

        std::unique_ptr<IState> mNext;
};

#endif // ISTATE_H
