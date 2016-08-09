#include "States/StateMachine.h"

#include "States/IState.h"

StateMachine::StateMachine() :
    mResume(false),
    mRunning(false)
{
    //ctor
}

void StateMachine::run(std::unique_ptr<IState> state)
{
    mRunning = true;

    mStates.push(std::move(state));
}

void StateMachine::nextState()
{
    if (mResume)
    {
        // Cleanup the current state
        if (!mStates.empty())
        {
            mStates.pop();
        }

        // Resume previous state
        if (!mStates.empty())
        {
            mStates.top()->resume();
        }

        mResume = false;
    }

    // There needs to be a state
    if (!mStates.empty())
    {
        std::unique_ptr<IState> temp = mStates.top()->next();

        // Only change states if there's a next one existing
        if(temp != nullptr)
        {
            // Replace the running state
            if(temp->isReplacing())
                mStates.pop();
            // Pause the running state
            else
                mStates.top()->pause();

            mStates.push(std::move(temp));
        }
    }
}

void StateMachine::lastState()
{
    mResume = true;
}

void StateMachine::update()
{
    mStates.top()->update();
}

void StateMachine::draw(sf::RenderTarget& target)
{
    mStates.top()->draw(target);
}

void StateMachine::handleEvents(sf::Event& event)
{
    mStates.top()->handleEvents(event);
}
