#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>
#include <thread>

#define SIZE_OF_CHARS 1
#define GAMEBOARD_SIZE 1456

std::array<char, SIZE_OF_CHARS>  buffer;
std::array<char, GAMEBOARD_SIZE> messageGameBoard;

void print_status(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    std::cout << "error = (" << error << ") " << error.message()
              << "; "
                 "bytes_transferred = "
              << bytes_transferred << std::endl;
}

std::array<char, GAMEBOARD_SIZE> getData(boost::asio::ip::tcp::socket& socket)
{
    socket.async_receive(boost::asio::buffer(messageGameBoard), &print_status);

    return messageGameBoard;
}

void sendData(boost::asio::ip::tcp::socket& socket, const std::string& message)
{
    if (message.size() > 0)
    {
        boost::asio::write(socket, boost::asio::buffer(message + '\n'));
    }
}

void noop()
{
}

std::string toString(std::array<char, GAMEBOARD_SIZE> buffer)
{
    size_t      i;
    std::string s = "";
    for (i = 0; i < buffer.size(); i++)
    {
        s = s + buffer[i];
    }
    return s;
}

bool sendsQuit(const char& input)
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

void sleep()
{
    std::chrono::milliseconds duration(100);
    std::this_thread::sleep_for(duration);
}

void printGameBoard(std::array<char, GAMEBOARD_SIZE>& response, boost::asio::ip::tcp::socket& client_socket)
{
    while (true)
    {
        response[0] = 'n';
        response    = getData(client_socket);

        std::cout << "\033c";
        std::cout << toString(response) << std::endl;
        sleep();
    }
}

int main(int argc, char* argv[])
{
    boost::asio::io_service      io_service;
    boost::asio::ip::tcp::socket client_socket(io_service);

    client_socket.async_connect(
        boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 9999), boost::bind(&noop));
    io_service.run();
    io_service.reset();

    std::array<char, GAMEBOARD_SIZE> response;
    std::string                      u_name, reply;
    reply      = "d";
    char input = 'd';

    std::thread printerThread(printGameBoard, std::ref(response), std::ref(client_socket));

    while (true)
    {
        input = getchar();
        std::string builtReply(1, input);
        sendData(client_socket, builtReply);

        if (sendsQuit(reply[0]))
        {
            break;
        }

        client_socket.cancel();
        io_service.run();
    }

    printerThread.join();

    return 0;
}
