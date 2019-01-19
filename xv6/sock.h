//
// TODO: Define an enumeration to represent socket state.
//
enum sockstate { LISTEN, CONNECT, CLOSE };


//
// TODO: Define a structure to represent a socket.
//

struct socket {
  char buffer[MX_BUF];
  int dataAvailable, ownerPID;
  int localPort, remotePort;
  enum sockstate currentState;
};