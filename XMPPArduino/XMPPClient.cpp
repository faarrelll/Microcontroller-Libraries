#include "XMPPClient.h"



/****************/
/* XMPP STANZAS */
/***************/
static const char PROGMEM open_stream_template[] = "<stream:stream " 
                             "xmlns='jabber:client' " 
                             "xmlns:stream='http://etherx.jabber.org/streams' " 
                             "to='%s' " 
                             "version='1.0'>";

static const char PROGMEM plain_auth_template[] = "<auth " 
                            "xmlns='urn:ietf:params:xml:ns:xmpp-sasl' " 
                            "mechanism='PLAIN'>" 
                            "%s" 
                            "</auth>";

static const char PROGMEM bind_template[] = "<iq " 
                      "type='set' " 
                      "id='bind_1'>" 
                      "<bind " 
                      "xmlns='urn:ietf:params:xml:ns:xmpp-bind'>" 
                      "<resource>%s</resource>" 
                      "</bind>" 
                      "</iq>";

static const char PROGMEM session_request_template[] = "<iq " 
                                 "to='%s' " 
                                 "type='set' " 
                                 "id='ard_sess'>" 
                                 "<session " 
                                 "xmlns='urn:ietf:params:xml:ns:xmpp-session' />" 
                                 "</iq>";

static const char PROGMEM presence_template[] = "<presence>" 
                          "<show/>" 
                          "</presence>";
                          
static const char PROGMEM message_template[] = "<message " 
                         "to='%s' " 
                         "xmlns='jabber:client' " 
                         "type='chat' " 
                         "id='msg' " 
                         "xml:lang='en'>" 
                         "<body>%s</body>" 
                         "</message>";
static const char PROGMEM close_template[] = "<presence type='unavailable'/>"
			 "</stream:stream>";

/********************/
/* TRANSITION TABLE */
/********************/
struct XMPPTransitionTableEntry {
  XMPPState currentState;
  XMPPState nextState;
  char *keyword;
};

int connTableSize = 6;
XMPPTransitionTableEntry connTable[] = {{INIT, AUTH, "PLAIN"},
                                        {AUTH, AUTH_STREAM, "success"},
                                        {AUTH_STREAM, BIND, "bind"},
                                        {BIND, SESS, "jid"},
                                        {SESS, READY, "session"},
                                        {READY, WAIT, ""},
                                        {WAIT, WAIT, ""}};

XMPPClient::XMPPClient()  {
    ;
}

XMPPClient::XMPPClient(uint8_t *_ip, uint16_t _port)  {
	ip = _ip;
	port     = _port;
    ;
}


String XMPPClient::getData()
{
	skip = false;
	int index = 0;
	
	while(client.available()) {
		// read the bytes incoming from the client:
	    char thisChar = client.read();
	    // echo the bytes back to the client:
	  if (thisChar == '<') {
	      skip = true;
	    }
			if(!skip)
			{
		    
		
			//	Serial.print(thisChar);

			        //  fill url the buffer
			      
			          clientline[index] = thisChar;
			          index++;
				
			          //  if we run out of buffer, overwrite the end
			          if(index >= BUFSIZE)
			            index = BUFSIZE -1;
				
		
			}
			
			
			
			
	 	  if (thisChar == '>') {
		      skip = false;
		    }
	    // echo the bytes to the server as well:
	
		if(!client.available())
		{
		
			//Serial.println(clientline);
		//	String(13, 8);
				 msgString = String(clientline);
		
				  msgString = msgString.substring(0,index);
						Serial.println(msgString);
//					Serial.println(msgString2 + "aa");
				//Serial.println(msgString2);
				return msgString;
		}
	}
	return "";
}


int XMPPClient::connect(char *username, char *server, char *resource, char *password) {
    boolean connected = false, error = false;
    this->username = username;
    this->server = server;
    this->resource = resource;
    this->password = password;

    while(!client.connect(ip, port)) {
	/* Retry connection every 1s and block until we're successful */
	delay(1000);
	Serial.print(".");
    }

    while(!connected && !error) {
	/* Connect dat shit^H^H^H^Hcuss */
	if(!client.connected()) {
	    error = true;
	    continue;
			//Serial.println(".");
	}

	int ret;
	ret = stateAction();

	if(ret == -1) {
	    error = true;
	}

	if(ret == 1) {
	    connected = true;
	}

	if(ret) {
	    continue;
	}

	processInput();
    }

    if(error || !connected) {
	return 0;
    } else {
	return 1;
    }
}

int XMPPClient::connect(char *jid, char *password) {
    /* Split the JID */
    /* Call connect(char*,char*,char*,char*) */
}

int XMPPClient::openStream(char *server) {
    sendTemplate(open_stream_template, strlen(server), server);
}

int XMPPClient::authenticate(char *username, char *password) {
  int plainStringLen = strlen(username) + strlen(password) + 2;
  int encStringLen = base64_enc_len(plainStringLen);
  char plainString[plainStringLen];
  char encString[encStringLen];
  
  /* Set up our plain auth string. It's in the form:
   * "\0username\0password"
   * where \0 is the null character
   */
  memset(plainString, '\0', plainStringLen);
  memcpy(plainString + 1, username, strlen(username));
  memcpy(plainString + 2 + strlen(username), password, strlen(password));
  
  /* Encode to base64 */
  base64_encode(encString, plainString, plainStringLen);
  sendTemplate(plain_auth_template, encStringLen, encString);
}

int XMPPClient::bindResource(char *resource) {
  sendTemplate(bind_template, strlen(resource), resource);
}

int XMPPClient::openSession(char *server) {

  sendTemplate(session_request_template, strlen(server), server);
}

int XMPPClient::sendMessage(char *recipientJid, char *message) {
  sendTemplate(message_template, strlen(recipientJid) + strlen(message), recipientJid, message);
}

int XMPPClient::sendPresence() {
  sendTemplate(presence_template);
}

int XMPPClient::close() {
  sendTemplate(close_template);
}


int XMPPClient::sendTemplate(const char *temp_P ) {
  int tempLen = strlen_P(temp_P);
  char temp[tempLen];

 
 

  strcpy_P(temp, temp_P);

 
   // Serial.println(temp);
    client.write(temp);

  return 1;
}

int XMPPClient::sendTemplate(const char *temp_P, int fillLen, char *m1 ) {
  int tempLen = strlen_P(temp_P);
  char temp[tempLen];
  char buffer[tempLen + fillLen];
 
 

  strcpy_P(temp, temp_P);

 
  	sprintf(buffer, temp, m1);
   // sprintf(buffer, temp, );
 
 //   Serial.println(buffer);
    client.write(buffer);

  return 1;
}


int XMPPClient::sendTemplate(const char *temp_P, int fillLen, char *m1,char *m2 ) {
  int tempLen = strlen_P(temp_P);
  char temp[tempLen];
  char buffer[tempLen + fillLen];
 
 

  strcpy_P(temp, temp_P);

 
  	sprintf(buffer, temp, m1, m2);
   // sprintf(buffer, temp, );
 
 //   Serial.println(buffer);
    client.write(buffer);

  return 1;
}
/*
//sendTemplate(open_stream_template, strlen(server), server);
int XMPPClient::sendTemplate(const char *temp_P, int fillLen, ...) {
  int tempLen = strlen_P(temp_P);
  char temp[tempLen];
  char buffer[tempLen + fillLen];
  va_list args;
  va_start(args, fillLen);

  strcpy_P(temp, temp_P);

  
  sprintf(buffer, temp, args);
 // sprintf(buffer, temp, );
  Serial.println("xx: ");
  Serial.print(fillLen);
  Serial.println(buffer);
  client.write(buffer);

  return 1;
}
*/
int XMPPClient::stateAction() {
 
// Serial.print("State = ");
// Serial.println(state);
 
 switch(state) {
  case INIT:
    openStream(server);
    break;
  case AUTH:
    authenticate(username, password);
    break;
  case AUTH_STREAM:
    openStream(server);
    break;
  case BIND:
    bindResource(resource);
    break;
  case SESS:
    openSession(server);
    break;
  case READY:
    return 1;
    break;
  case WAIT:
    break;
  default:
    return -1;
    break;
 }
 return 0;
}

void XMPPClient::processInput() {
  int bufLen = 8;
  char buffer[bufLen];
  int i = 0;
  memset(buffer, '\0', bufLen);
  boolean stateChanged = false;

  if(!client.connected()) {
    state = WAIT;
    return;
  }

  // TODO: This process is pretty inefficient and naively implemented
  // It might be an idea to rewrite it cleverer
  while(!stateChanged) {
    if(client.available()) {
      /* Push a character from the ethernet interface into the buffer */
      for(i = 0 ; i < bufLen; i++) {
        buffer[i] = buffer[i+1];
      }
      buffer[i] = client.read();
      
	Serial.print(buffer[i]);
      /* Ignore what we've read if it's an empty string */
      if(!strlen(buffer)) {
        continue;
      } else {
         //Serial.println(buffer);
      }
      
      for(int i = 0; i < connTableSize; i++) {
        if(state == connTable[i].currentState && strstr(buffer,connTable[i].keyword)) {
          
	  /*
          Serial.println(buffer);
          Serial.println(connTable[i].keyword);
          Serial.println((int)strstr(buffer, connTable[i].keyword)); 
          
          Serial.print(connTable[i].keyword);
          Serial.println(" seen, transitioning");
	  */
          
          state = connTable[i].nextState;
          client.flush();
          stateChanged = true;
          break;
        }
      }
    } else {
      delay(10);
    }
  }
}


