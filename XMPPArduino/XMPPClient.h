#ifndef _H_XMPP_CLIENT
#define _H_XMPP_CLIENT

#include <Base64.h>
#include <ESP8266WiFi.h>
#include <string.h>
#include <stdarg.h>
#include <WiFiClient.h>


enum XMPPState {
  INIT,
  AUTH,
  AUTH_STREAM,
  BIND,
  SESS,
  READY,
  WAIT
};

class XMPPClient {
    private:
		uint8_t *ip;
		uint16_t port;
	
	char *username;
	char *server;
	char *password;
	char *resource;
	

	XMPPState state;
int sendTemplate(const char *temp_P) ;
int sendTemplate(const char *temp_P, int fillLen, char *m1 ,char *m2) ;
int sendTemplate(const char *temp_P, int fillLen, char *m1 ) ;
	//int sendTemplate(const char *strTemplate, int fillLen, ...);

	int openStream(char *server);
	int authenticate(char *username, char *password);
	int bindResource(char *resource);
	int openSession(char *server);

	void processInput();
	int stateAction();


    public:
		WiFiClient client;
	XMPPClient();
	XMPPClient(uint8_t *ip, uint16_t port);


	int connect(char *username, char *server, char *resource, char *password);
	int connect(char *jid, char *password);

	int sendMessage(char *recipientJid, char *message);
	int sendPresence();

	int close();
	
	// test variables for read
	boolean skip;
		String getData();
	#define BUFSIZE 100
	char clientline[BUFSIZE];
	String msgString;
};

#endif /* _H_XMPP_CLIENT */
