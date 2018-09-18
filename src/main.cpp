#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include <emscripten/emscripten.h>

extern "C" void invoke_callback(int callback_id, const char *text);

extern "C"
{

    EMSCRIPTEN_KEEPALIVE
    void irc_write(int sockd, std::string msg)
    {
        msg.append("\r\n");
        send(sockd, msg.c_str(), msg.size(), 0);
    }

    EMSCRIPTEN_KEEPALIVE
    void run(int callback_id)
    {
        std::string server = "irc.chat.twitch.tv";
        int port = 6667;

        struct sockaddr_in addr;
        struct hostent *host;

        host = gethostbyname(server.c_str());

        addr.sin_addr.s_addr = *(unsigned long *)host->h_addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons((unsigned short)port);
        int sockd = socket(AF_INET, SOCK_STREAM, 0);

        connect(sockd, (struct sockaddr *)&addr, sizeof(addr));

        std::cout << "connecting to twitch irc" << std::endl;

        irc_write(sockd, pass);
        irc_write(sockd, nick);
        irc_write(sockd, channel);

        irc_write(sockd, "CAP REQ :twitch.tv/membership");
        irc_write(sockd, "CAP REQ :twitch.tv/tags");
        irc_write(sockd, "CAP REQ :twitch.tv/commands");

        irc_write(sockd, "PRIVMSG #kritzware :test message PogChamp");

        char sockbuff[4096];

        while (1)
        {
            memset(&sockbuff, '\0', sizeof(sockbuff));
            recv(sockd, sockbuff, 4096, 0);
            // std::cout << "test" << sockbuff << std::endl;
            invoke_callback(callback_id, std::string(sockbuff).c_str());
        }
    }

    int main()
    {
        std::cout << "hello world" << std::endl;
        // EM_ASM(allReady());
        // run();
    }
}