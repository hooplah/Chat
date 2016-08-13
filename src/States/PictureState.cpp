#include "States/PictureState.h"

#include "States/ChatState.h"
#include "States/StateMachine.h"

#include "imgui/imgui.h"

PictureState::PictureState(StateMachine& stateMachine, bool replace, Client& client) : IState(stateMachine, replace),
    mClient(client)
{
    mImage.loadFromFile("assets/pic.png");
    mTexture.loadFromImage(mImage);
    //mSprite = sf::Sprite(mTexture);
}

PictureState::~PictureState()
{
    //dtor
}

void PictureState::update()
{
    ImGui::Begin("");

    if (ImGui::Button("Send"))
    {
        sf::Packet packet;
        sf::Uint32 size = mTexture.getSize().x*mTexture.getSize().y*4; // multiply 4 for each value in RGBA
        sf::Vector2u picSize = mTexture.getSize();
        const sf::Uint8* pixelPtr = mImage.getPixelsPtr();

        packet << PacketID::PICTURE;
        packet << size;
        packet << picSize.x << picSize.y;
        packet.append(pixelPtr, size);

        mClient.getSocket().send(packet);
    }

    if (mClient.getPictureChannel().receive(mImage, false))
    {
        mTexture.loadFromImage(mImage);
        mSprite.setTexture(mTexture);
    }

    ImGui::End();
}

void PictureState::draw(sf::RenderTarget& target)
{
    target.draw(mSprite);
}

void PictureState::handleEvents(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
        {
            mNext = StateMachine::build<ChatState>(mMachine, false, std::ref(mClient));
        }
    }
}
