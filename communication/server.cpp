#include "../entities/entities.h"
#include "../gamelogic/gamelogic.h"
#include "../snake/snake.h"
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#define SIZE_OF_CHARS 1

std::array<char, SIZE_OF_CHARS> characterArray;

void printStatus(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    std::cout << "error = (" << error << ") " << error.message()
              << "; "
                 "bytes_transferred = "
              << bytes_transferred << std::endl;
}

std::array<char, SIZE_OF_CHARS> getData(boost::asio::ip::tcp::socket& socket)
{
    socket.async_receive(boost::asio::buffer(characterArray), &printStatus);

    return characterArray;
}

void sendData(boost::asio::ip::tcp::socket& socket, const std::string& message)
{
    boost::asio::write(socket, boost::asio::buffer(message + '\n'));
}

void noop()
{
}

std::string toString(std::array<char, SIZE_OF_CHARS> characterArray)
{
    size_t      i;
    std::string builtString = "";
    for (i = 0; i < characterArray.size(); i++)
    {
        builtString = builtString + characterArray[i];
    }
    return builtString;
}

bool isValidInput(const char& input)
{
    if (input == 'w' || input == 'a' || input == 's' || input == 'd')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool receivesQuit(const char& input)
{
    if (input == 'q')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char* argv[])
{
    boost::asio::io_service        io_service;
    boost::asio::ip::tcp::acceptor acceptor_server(io_service,
                                                   boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 9999));
    boost::asio::ip::tcp::socket   server_socket(io_service);
    acceptor_server.async_accept(server_socket, boost::bind(&noop));
    io_service.run();
    io_service.reset();

    Snake     snake;
    GameBoard gameBoard;
    Apple     apple;

    snake.create();
    std::shared_ptr<tupleVector> snakeVector = snake.getPositionVector();
    gameBoard.initialize();
    tuple randomApple = apple.generateApple(snakeVector);

    char                            input = 'd';
    std::array<char, SIZE_OF_CHARS> response;
    std::string                     reply = "";

    while (snake.livesAndTeleports() && !gameBoard.playerHasWon())
    {
        snake.moves();

        response = getData(server_socket);

        if (receivesQuit(response[0]))
        {
            break;
        }

        if (isValidInput(response[0]))
        {
            input = response[0];
        }
        snake.getsUserInput(input);
        if (snake.eatsApple(randomApple))
        {
            gameBoard.updateScoreBoard();
            randomApple = apple.generateApple(snakeVector);
        }
        gameBoard.updateGameState(snakeVector, randomApple);

        reply = gameBoard.buildReply(*snakeVector.get(), randomApple);

        sendData(server_socket, reply);

        server_socket.cancel();
        io_service.run();
    }
    return 0;
}
